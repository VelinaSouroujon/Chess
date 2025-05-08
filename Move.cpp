#include <stdexcept>
#include "Move.h"
#include "CommonUtils.h"
#include "Constants.h"
#include "PieceFactory.h"

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
		if (notation[idx] == Constants::CAPTURE_DELIMITER)
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

	this->from = convertToCoordinateFrom(from);

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
}

Move::Move(const char* notation)
{
	assignCoordinates(notation);
}

ChessCoordinate Move::getFrom() const
{
	return from;
}

ChessCoordinate Move::getTo() const
{
	return to;
}

bool Move::isCaptureMove() const
{
	return isCapture;
}

bool Move::execute(Board& board) const
{
	Piece* pieceToMove = board.at(from);
	if (pieceToMove == nullptr)
	{
		return false;
	}

	if (pieceNotation != pieceToMove->getPieceNotation())
	{
		return false;
	}

	if (!pieceToMove->isValidMove(*this))
	{
		return false;
	}

	board.at(from) = nullptr;
	board.at(to) = pieceToMove;

	return true;
}

ChessCoordinate Move::convertToCoordinateFrom(const char* notation)
{
	if (notation == nullptr)
	{
		throw std::invalid_argument("Notation cannot be null");
	}

	int notationLength = strlen(notation);

	int letterNotationIdx;
	if (notationLength == Constants::MAX_NOTATION_LENGTH)
	{
		letterNotationIdx = 1;
	}
	else if (notationLength == Constants::MAX_NOTATION_LENGTH - 1)
	{
		letterNotationIdx = 0;
	}
	else
	{
		throw std::invalid_argument("Invalid notation length");
	}

	return convertToCoordinate(notation, letterNotationIdx);
}

ChessCoordinate Move::convertToCoordinateTo(const char* notation)
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
