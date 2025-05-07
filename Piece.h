#pragma once

#include "ChessCoordinate.h"
#include "Enums.h"

class Move;

class Piece
{
private:
	PieceColor color = PieceColor::White;
	ChessCoordinate position;

public:
	virtual char getPieceNotation() const = 0;

	PieceColor getColor() const;
	virtual bool isValidMove(const Move& move) const = 0;

	ChessCoordinate getPosition() const;
	void setPosition(const ChessCoordinate& newPosition);
};

