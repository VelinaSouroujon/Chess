#include "UnicodePieceRenderer.h"

#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

wchar_t UnicodePieceRenderer::getRepresentation(const Pawn& pawn) const
{
    if (pawn.getColor() == PieceColor::White)
    {
        return L'♙';
    }

    return L'♟';
}

wchar_t UnicodePieceRenderer::getRepresentation(const Rook& rook) const
{
    if (rook.getColor() == PieceColor::White)
    {
        return L'♖';
    }

    return L'♜';
}

wchar_t UnicodePieceRenderer::getRepresentation(const Knight& knight) const
{
    if (knight.getColor() == PieceColor::White)
    {
        return L'♘';
    }

    return L'♞';
}

wchar_t UnicodePieceRenderer::getRepresentation(const Bishop& bishop) const
{
    if (bishop.getColor() == PieceColor::White)
    {
        return L'♗';
    }

    return L'♝';
}

wchar_t UnicodePieceRenderer::getRepresentation(const Queen& queen) const
{
    if (queen.getColor() == PieceColor::White)
    {
        return L'♕';
    }

    return L'♛';
}

wchar_t UnicodePieceRenderer::getRepresentation(const King& king) const
{
    if (king.getColor() == PieceColor::White)
    {
        return L'♔';
    }

    return L'♚';
}
