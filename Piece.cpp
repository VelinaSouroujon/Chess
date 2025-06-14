#include "Piece.h"

Piece::Piece(PieceColor color) : color(color)
{

}

PieceColor Piece::getColor() const
{
    return color;
}

const ChessCoordinate& Piece::getPosition() const
{
    return position;
}

void Piece::setPosition(const ChessCoordinate& newPosition)
{
    position = newPosition;
}
