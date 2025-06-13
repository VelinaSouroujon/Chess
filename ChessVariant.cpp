#include "ChessVariant.h"

Board& ChessVariant::getBoard()
{
	return board;
}

const IPieceFactory& ChessVariant::getPieceFactory() const
{
	return iPieceFactory;
}

ChessVariant::ChessVariant(IPieceFactory& iPieceFactory)
	: iPieceFactory(iPieceFactory)
{

}

const Board& ChessVariant::getBoard() const
{
	return board;
}
