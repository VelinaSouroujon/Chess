#include "Piece.h"
#include "Move.h"

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

bool Piece::isValidMove(const Move& move) const
{
    if (move.getFrom() == move.getTo())
    {
        return false;
    }

    return true;
}

void Piece::setPosition(const ChessCoordinate& value)
{
    position = value;
}
