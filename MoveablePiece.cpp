#include "MoveablePiece.h"

bool MoveablePiece::getIsInitialization() const
{
    return isInitialization;
}

void MoveablePiece::setPosition(const ChessCoordinate& value)
{
    Piece::setPosition(value);

    if (isInitialization)
    {
        isInitialization = false;
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
