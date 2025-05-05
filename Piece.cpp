#include "Piece.h"

PieceColor Piece::getColor() const
{
    return color;
}

ChessCoordinate Piece::getPosition() const
{
    return position;
}

void Piece::setPosition(const ChessCoordinate& newPosition)
{
    position = newPosition;
}
