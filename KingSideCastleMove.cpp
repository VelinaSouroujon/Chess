#include "KingSideCastleMove.h"

KingSideCastleMove::KingSideCastleMove()
    : whiteKingPosition('g', 1),
    blackKingPosition('g', 8),
    whiteRookPosition('f', 1),
    blackRookPosition('f', 8),
    whiteInitialRookPosition('h', 1),
    blackInitialRookPosition('h', 8)
{

}

const ChessCoordinate& KingSideCastleMove::kingPosition(PieceColor color) const
{
    return color == PieceColor::White
        ? whiteKingPosition
        : blackKingPosition;
}

const ChessCoordinate& KingSideCastleMove::rookPosition(PieceColor color) const
{
    return color == PieceColor::White
        ? whiteRookPosition
        : blackRookPosition;
}

const ChessCoordinate& KingSideCastleMove::initialRookPosition(PieceColor color) const
{
    return color == PieceColor::White
        ? whiteInitialRookPosition
        : blackInitialRookPosition;
}

bool KingSideCastleMove::execute(Game& game)
{
    if (!game.playingSide().getKingSideCastlePossible())
    {
        return false;
    }

    return CastleMove::execute(game);
}
