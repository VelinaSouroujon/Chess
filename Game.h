#pragma once

#include "Piece.h"
#include "Constants.h"
#include "Board.h"

class Game
{
	ChessCoordinate enPassantSquare;
	EnPassantState enPassantState = EnPassantState::None;
public:
	Board board;
	void changeTurn();
};

