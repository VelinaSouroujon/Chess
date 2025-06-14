#pragma once

#include "ChessCoordinate.h"
#include "Enums.h"
#include "PieceRenderer.h"

class Move;

class Piece
{
private:
	PieceColor color = PieceColor::White;
	ChessCoordinate position;

protected:
	virtual void setPosition(const ChessCoordinate& value);

public:
	Piece(PieceColor color);
	virtual ~Piece() = default;

	virtual char getPieceNotation() const = 0;
	PieceColor getColor() const;

	virtual bool isSufficientForWin() const = 0;
	virtual bool isValidMove(const Move& move) const = 0;
	virtual void fillDirections(Array<PieceDirection, Constants::MAX_DIRECTIONS_COUNT>& directions) const = 0;
	virtual wchar_t accept(const PieceRenderer& renderer) const = 0;

	ChessCoordinate getPosition() const;
	virtual Piece* clone() const = 0;
};

