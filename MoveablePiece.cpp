#include "MoveablePiece.h"

void MoveablePiece::setPosition(const ChessCoordinate& value)
{
    Piece::setPosition(value);

    if (isSetDuringInit)
    {
        isSetDuringInit = false;
    }
    else
    {
        hasMoved = true;
    }
}

MoveablePiece::MoveablePiece(PieceColor color)
    : Piece(color)
{

}

bool MoveablePiece::getHasMoved() const
{
    return hasMoved;
}
