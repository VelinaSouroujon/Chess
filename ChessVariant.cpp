#include "ChessVariant.h"

Board& ChessVariant::getBoardRef()
{
	return board;
}

Board ChessVariant::getBoard() const
{
	return board;
}
