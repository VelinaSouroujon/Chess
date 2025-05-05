#include "Rook.h"
#include "Move.h"

bool Rook::isValidMove(const Move& move) const
{
    ChessCoordinate from = move.getFrom();
    ChessCoordinate to = move.getTo();

    return from.isSameRow(to)
        || from.isSameCol(to);
}
