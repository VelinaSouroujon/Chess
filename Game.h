#pragma once

#include "Piece.h"
#include "Constants.h"

class Game
{
public:
	Piece* board[Constants::BOARD_SIZE][Constants::BOARD_SIZE];
};

