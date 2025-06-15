#include "BinaryGameSerializer.h"

bool BinaryGameSerializer::serializePieces(const PiecesGameInfo& gameInfoPieces, std::ostream& os) const
{
	if (!os.good())
	{
		return false;
	}

	const OneColorPieces& oneSidePieces = gameInfoPieces.getPieces();
	int countPieces = oneSidePieces.getSize();

	os.write(reinterpret_cast<const char*>(&countPieces), sizeof(countPieces));

	for (int i = 0; i < countPieces; i++)
	{
		const Piece& currPiece = oneSidePieces[i];
		const ChessCoordinate& piecePosition = currPiece.getPosition();
		char pieceNotation = currPiece.getPieceNotation();

		char col = piecePosition.getCol();
		int row = piecePosition.getRow();

		os.write(reinterpret_cast<const char*>(&pieceNotation), sizeof(pieceNotation));
		os.write(reinterpret_cast<const char*>(&col), sizeof(col));
		os.write(reinterpret_cast<const char*>(&row), sizeof(row));
	}

	bool canMakeKingSideCastle = gameInfoPieces.getKingSideCastlePossible();
	os.write(reinterpret_cast<const char*>(&canMakeKingSideCastle), sizeof(canMakeKingSideCastle));

	bool canMakeQueenSideCastle = gameInfoPieces.getQueenSideCastlePossible();
	os.write(reinterpret_cast<const char*>(&canMakeQueenSideCastle), sizeof(canMakeQueenSideCastle));

	return true;
}

bool BinaryGameSerializer::deserializePieces(PiecesGameInfo& gameInfoPieces, Board& board, std::istream& is, const IPieceFactory& pieceFactory) const
{
	if (!is.good())
	{
		return false;
	}

	OneColorPieces& oneSidePieces = gameInfoPieces.getPieces();
	PieceColor color = oneSidePieces.getColor();

	int countPieces;
	is.read(reinterpret_cast<char*>(&countPieces), sizeof(countPieces));

	for (int i = 0; i < countPieces; i++)
	{
		char pieceNotation;
		is.read(reinterpret_cast<char*>(&pieceNotation), sizeof(pieceNotation));

		Piece* piece = pieceFactory.createPiece(pieceNotation, color);
		oneSidePieces.add(*piece);

		if (pieceNotation == Constants::KING_NOTATION)
		{
			gameInfoPieces.setKing(*piece);
		}

		char col;
		is.read(reinterpret_cast<char*>(&col), sizeof(col));

		int row;
		is.read(reinterpret_cast<char*>(&row), sizeof(row));

		ChessCoordinate position(col, row);
		board.setAt(position, piece);
	}

	bool canMakeKingSideCastle;
	is.read(reinterpret_cast<char*>(&canMakeKingSideCastle), sizeof(canMakeKingSideCastle));

	bool canMakeQueenSideCastle;
	is.read(reinterpret_cast<char*>(&canMakeQueenSideCastle), sizeof(canMakeQueenSideCastle));

	if (!canMakeKingSideCastle)
	{
		gameInfoPieces.impossibleKingSideCastle();
	}
	if (!canMakeQueenSideCastle)
	{
		gameInfoPieces.impossibleQueenSideCastle();
	}

	return true;
}

bool BinaryGameSerializer::serialize(const Game& game, std::ostream& os) const
{
	if (!os.good())
	{
		return false;
	}

	if (!serializePieces(game.white, os))
	{
		return false;
	}

	if (!serializePieces(game.black, os))
	{
		return false;
	}

	int countPositions = game.positionsCount.count();
	os.write(reinterpret_cast<const char*>(&countPositions), sizeof(countPositions));

	for (int i = 0; i < countPositions; i++)
	{
		PositionCount currPosition = game.positionsCount[i];

		os.write(reinterpret_cast<const char*>(&currPosition), sizeof(currPosition));
	}

	os.write(reinterpret_cast<const char*>(&game.turnToMove), sizeof(game.turnToMove));
	os.write(reinterpret_cast<const char*>(&game.enPassantState), sizeof(game.enPassantState));

	if (game.enPassantState != EnPassantState::None)
	{
		char col = game.enPassantSquare.getCol();
		int row = game.enPassantSquare.getRow();

		os.write(reinterpret_cast<const char*>(&col), sizeof(col));
		os.write(reinterpret_cast<const char*>(&row), sizeof(row));
	}

	return true;	
}

bool BinaryGameSerializer::deserialize(Game& game, std::istream& is, const IPieceFactory& pieceFactory) const
{
	if (!is.good())
	{
		return false;
	}

	Board& board = game.chessVariant.getBoard();

	if (!deserializePieces(game.white, board, is, pieceFactory))
	{
		return false;
	}

	if (!deserializePieces(game.black, board, is, pieceFactory))
	{
		return false;
	}

	int countPositions;
	is.read(reinterpret_cast<char*>(&countPositions), sizeof(countPositions));

	for (int i = 0; i < countPositions; i++)
	{
		PositionCount position;
		is.read(reinterpret_cast<char*>(&position), sizeof(position));

		game.positionsCount.add(position);
	}

	is.read(reinterpret_cast<char*>(&game.turnToMove), sizeof(game.turnToMove));
	is.read(reinterpret_cast<char*>(&game.enPassantState), sizeof(game.enPassantState));

	if (game.enPassantState != EnPassantState::None)
	{
		char col;
		is.read(reinterpret_cast<char*>(&col), sizeof(col));

		int row;
		is.read(reinterpret_cast<char*>(&row), sizeof(row));

		game.enPassantSquare.setCol(col);
		game.enPassantSquare.setRow(row);
	}

	return true;
}
