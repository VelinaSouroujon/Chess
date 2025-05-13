#include "Rook.h"
#include "Move.h"

Rook::Rook(PieceColor color) : Piece(color)
{

}

char Rook::getPieceNotation() const
{
    return Constants::ROOK_NOTATION;
}

bool Rook::isValidMove(const Move& move) const
{
    ChessCoordinate from = move.getFrom();
    ChessCoordinate to = move.getTo();

    return from.isSameRow(to)
        || from.isSameCol(to);
}
