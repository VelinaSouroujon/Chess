#pragma once

#include "Board.h"
#include "ChessCoordinate.h"
#include "Enums.h"
#include "PieceRenderer.h"
#include "Array.hpp"
#include "PieceDirection.h"

class Move;

class Piece
{
private:
	PieceColor color = PieceColor::White;
	ChessCoordinate position;

	friend void Board::setAt(const ChessCoordinate& coordinate, Piece* piece);
	friend void Board::setAt(char col, int row, Piece* piece);

protected:
	virtual void setPosition(const ChessCoordinate& value);

public:
	Piece(PieceColor color);
	virtual ~Piece() = default;

	virtual char getPieceNotation() const = 0;
	PieceColor getColor() const;
	const ChessCoordinate& getPosition() const;

	virtual bool isSufficientForWin() const = 0;
	virtual bool isValidMove(const Move& move) const = 0;
	virtual void fillDirections(Array<PieceDirection, Constants::MAX_DIRECTIONS_COUNT>& directions) const = 0;
	virtual wchar_t accept(const PieceRenderer& renderer) const = 0;

	virtual Piece* clone() const = 0;
};

