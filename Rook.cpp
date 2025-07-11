#include "Rook.h"
#include "Move.h"
#include "Directions.h"

void Rook::setPosition(const ChessCoordinate& coordinate)
{
    if ((mediator != nullptr) && (!getIsInitialization()) && (!getHasMoved()))
    {
        mediator->notifyMove(*this);
    }

    MoveablePiece::setPosition(coordinate);
}

Rook::Rook(PieceColor color, PieceMediator* mediator)
    : MoveablePiece(color),
    mediator(mediator)
{

}

char Rook::getPieceNotation() const
{
    return Constants::ROOK_NOTATION;
}

bool Rook::isSufficientForWin() const
{
    return true;
}

bool Rook::isValidMove(const Move& move) const
{
    if (!Piece::isValidMove(move))
    {
        return false;
    }

    const ChessCoordinate& from = move.getFrom();
    const ChessCoordinate& to = move.getTo();

    return from.isSameRow(to)
        || from.isSameCol(to);
}

void Rook::fillDirections(Array<PieceDirection, Constants::MAX_DIRECTIONS_COUNT>& directions) const
{
    Directions::fillRowDirections(directions);
    Directions::fillColDirections(directions);
}

wchar_t Rook::accept(const PieceRenderer& renderer) const
{
    return renderer.getRepresentation(*this);
}

Piece* Rook::clone() const
{
    return new Rook(*this);
}
