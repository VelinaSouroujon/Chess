#include <stdexcept>
#include "Move.h"
#include "CommonUtils.h"
#include "Constants.h"
#include "PromotionPieceFactory.h"

void Move::assignCoordinates(const char* notation)
{
	if (notation == nullptr)
	{
		throw std::invalid_argument("Notation cannot be null");
	}

	char from[Constants::MAX_NOTATION_LENGTH + 1];
	char to[Constants::MAX_NOTATION_LENGTH + 1];

	int idx = 0;

	while (notation[idx] != '\0')
	{
		if (CommonUtils::toLower(notation[idx]) == Constants::CAPTURE_DELIMITER)
		{
			isCapture = true;
			break;
		}
		if (notation[idx] == Constants::FROM_TO_DELIMITER)
		{
			break;
		}
		if (idx >= Constants::MAX_NOTATION_LENGTH)
		{
			throw std::invalid_argument("Invalid notation");
		}

		from[idx] = notation[idx];
		idx++;
	}

	from[idx] = '\0';
	idx++;

	this->from = convertToCoordinateFrom(from, pieceNotation);

	int toIdx = 0;

	while (notation[idx] != '\0')
	{
		if (toIdx >= Constants::MAX_NOTATION_LENGTH)
		{
			throw std::invalid_argument("Invalid notation");
		}

		to[toIdx] = notation[idx];
		idx++;
		toIdx++;
	}

	to[toIdx] = '\0';

	this->to = convertToCoordinateTo(to);

	if ((pieceNotation == Constants::PAWN_NOTATION)
		&& (this->to.getRow() == Constants::MIN_ROW_COORDINATE || this->to.getRow() == Constants::BOARD_SIZE)
		&& (toIdx != Constants::MAX_NOTATION_LENGTH))
	{
		throw std::invalid_argument("You must add the promotion piece notation at the end of the notation");
	}
}

Move::Move(const char* notation)
{
	assignCoordinates(notation);
}

Move::Move(const ChessCoordinate& from, const ChessCoordinate& to, bool isCapture)
	: from(from), to(to), isCapture(isCapture)
{

}

const ChessCoordinate& Move::getFrom() const
{
	return from;
}

const ChessCoordinate& Move::getTo() const
{
	return to;
}

bool Move::isCaptureMove() const
{
	return isCapture;
}

bool Move::tryConfigureEnPassant(const ChessCoordinate* gameEnPassantSquare, const Piece& pieceToMove, Piece* pieceToBeRemoved, Board& board) const
{
	if ((gameEnPassantSquare != nullptr)
		&& to == *gameEnPassantSquare
		&& pieceToMove.getPieceNotation() == Constants::PAWN_NOTATION)
	{
		int pieceToRemoveRow = from.getRow();
		char pieceToRemoveCol = to.getCol();
		ChessCoordinate positionPieceToRemove(pieceToRemoveCol, pieceToRemoveRow);

		pieceToBeRemoved = board.at(positionPieceToRemove);
		board.setAt(positionPieceToRemove, nullptr);

		return true;
	}

	return false;
}

bool Move::isLegalMove(const Board& board, PieceColor turnToMove) const
{
	const Piece* pieceToBeRemoved = board.at(to);
	const Piece* piece = board.at(from);

	if (piece == nullptr)
	{
		return false;
	}

	if (piece->getColor() != turnToMove)
	{
		return false;
	}

	if (pieceNotation != piece->getPieceNotation())
	{
		return false;
	}

	if ((pieceToBeRemoved != nullptr) && (pieceToBeRemoved->getColor() == piece->getColor()))
	{
		return false;
	}

	if ((pieceToBeRemoved != nullptr) && (!isCapture))
	{
		return false;
	}

	if (!piece->isValidMove(*this))
	{
		return false;
	}

	if (board.isPieceBetween(from, to))
	{
		return false;
	}

	return true;
}

bool Move::execute(Game& game)
{
	Board& board = game.getChessVariant().getBoard();
	PieceColor turnToMove = game.getTurnToMove();

	if (!isLegalMove(board, turnToMove))
	{
		return false;
	}

	Piece* pieceToBeRemoved = board.at(to);
	Piece* pieceToMove = getPiece(board);

	if (pieceToBeRemoved == nullptr && isCapture)
	{
		const ChessCoordinate* enPassantSquare = game.getEnPassantSquare();

		if (!tryConfigureEnPassant(enPassantSquare, *pieceToMove, pieceToBeRemoved, board))
		{
			return false;
		}
	}

	board.simulateSetAt(from, nullptr);
	board.simulateSetAt(to, pieceToMove);

	PiecesGameInfo& playingSide = game.playingSide();
	PiecesGameInfo& awaitingSide = game.awaitingSide();

	if (pieceToMove->getPieceNotation() == Constants::KING_NOTATION)
	{
		if (awaitingSide.getPieces().isSquareAttacked(to, board, pieceToBeRemoved))
		{
			board.simulateSetAt(from, pieceToMove);
			board.simulateSetAt(to, pieceToBeRemoved);

			return false;
		}
		else
		{
			board.setAt(to, pieceToMove);
		}

		awaitingSide.updateAttackers(to);
	}
	else
	{
		OneColorPieces& attackersAwaitingSide = awaitingSide.indirectAttackersOnOppositeKing();
		const ChessCoordinate& kingCoordPlayingSide = playingSide.getKing().getPosition();

		if (attackersAwaitingSide.isSquareAttacked(kingCoordPlayingSide, board, pieceToBeRemoved))
		{
			board.simulateSetAt(from, pieceToMove);
			board.simulateSetAt(to, pieceToBeRemoved);

			return false;
		}
		else
		{
			board.setAt(to, pieceToMove);
		}
	}

	if (pieceToBeRemoved != nullptr)
	{
		awaitingSide.indirectAttackersOnOppositeKing().remove(*pieceToBeRemoved);
		awaitingSide.getPieces().remove(*pieceToBeRemoved);
		board.deletePiece(pieceToBeRemoved);
	}

	updateIndirectKingAttackers(awaitingSide.getKing().getPosition(), playingSide.indirectAttackersOnOppositeKing(), *pieceToMove, board);

	return true;
}

bool Move::canExecute(Game& game)
{
	Board& board = game.getChessVariant().getBoard();
	Piece* pieceToMove = board.at(from);
	Piece* pieceToBeRemoved = board.at(to);
	PieceColor playingSideColor = pieceToMove->getColor();

	pieceNotation = pieceToMove->getPieceNotation();

	if (!isLegalMove(board, playingSideColor))
	{
		return false;
	}

	if (pieceToBeRemoved == nullptr && isCapture)
	{
		const ChessCoordinate* enPassantSquare = game.getEnPassantSquare();

		if (!tryConfigureEnPassant(enPassantSquare, *pieceToMove, pieceToBeRemoved, board))
		{
			return false;
		}
	}

	const ChessCoordinate& kingPosition = game.sameColorPiecesInfo(playingSideColor).getKing().getPosition();

	board.simulateSetAt(from, nullptr);
	board.simulateSetAt(to, pieceToMove);

	bool isKingAttacked;
	if (from == kingPosition)
	{
		isKingAttacked = game.oppositeColorPiecesInfo(playingSideColor).getPieces().isSquareAttacked(to, board, pieceToBeRemoved);
	}
	else
	{
		isKingAttacked = game.oppositeColorPiecesInfo(playingSideColor).indirectAttackersOnOppositeKing().isSquareAttacked(kingPosition, board, pieceToBeRemoved);
	}

	board.simulateSetAt(from, pieceToMove);
	board.simulateSetAt(to, pieceToBeRemoved);

	return !isKingAttacked;
}

const ChessCoordinate& Move::convertToCoordinateFrom(const char* notation, char& pieceNotation)
{
	if (notation == nullptr)
	{
		throw std::invalid_argument("Notation cannot be null");
	}

	int notationLength = strlen(notation);

	int letterNotationIdx;
	if (notationLength == Constants::MAX_NOTATION_LENGTH)
	{
		pieceNotation = notation[0];
		letterNotationIdx = 1;
	}
	else if (notationLength == Constants::MAX_NOTATION_LENGTH - 1)
	{
		pieceNotation = Constants::PAWN_NOTATION;
		letterNotationIdx = 0;
	}
	else
	{
		throw std::invalid_argument("Invalid notation length");
	}

	pieceNotation = CommonUtils::toUpper(pieceNotation);

	return convertToCoordinate(notation, letterNotationIdx);
}

const ChessCoordinate& Move::convertToCoordinateTo(const char* notation)
{
	if (notation == nullptr)
	{
		throw std::invalid_argument("Notation cannot be null");
	}
	if (strlen(notation) > Constants::MAX_NOTATION_LENGTH)
	{
		throw std::invalid_argument("Invalid notation length");
	}

	int letterNotationIdx = 0;

	return convertToCoordinate(notation, letterNotationIdx);
}

ChessCoordinate Move::convertToCoordinate(const char* notation, int letterNotationIdx)
{
	if (notation == nullptr)
	{
		throw std::invalid_argument("Notation cannot be null");
	}

	char col = notation[letterNotationIdx];
	int row = notation[letterNotationIdx + 1] - '0';

	return ChessCoordinate(col, row);
}

void Move::updateIndirectKingAttackers(const ChessCoordinate& kingCoord, OneColorPieces& attackers, const Piece& movedPiece, const Board& board) const
{
	Move move(movedPiece.getPosition(), kingCoord, true);
	bool isKingAttacked = movedPiece.isValidMove(move);
	int pieceIdx = attackers.findIdx(movedPiece);

	if (isKingAttacked)
	{
		if (pieceIdx < 0)
		{
			attackers.add(movedPiece);
		}
	}
	else
	{
		if (pieceIdx >= 0)
		{
			attackers.removeAt(pieceIdx);
		}
	}
}

Piece* Move::getPiece(Board& board) const
{
	Piece* piece = board.at(from);

	return piece;
}
