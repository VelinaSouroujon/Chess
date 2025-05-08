#pragma once

#include "Board.h"
#include "ChessCoordinate.h"

class Move
{
private:
	char pieceNotation = Constants::PAWN_NOTATION;
	ChessCoordinate from;
	ChessCoordinate to;
	bool isCapture = false;

	void assignCoordinates(const char* notation);
	static ChessCoordinate convertToCoordinate(const char* notation, int letterNotationIdx);

public:
	Move(const char* notation);

	ChessCoordinate getFrom() const;
	ChessCoordinate getTo() const;
	bool isCaptureMove() const;

	virtual bool execute(Board& board) const;

	static ChessCoordinate convertToCoordinateFrom(const char* notation);
	static ChessCoordinate convertToCoordinateTo(const char* notation);
};

