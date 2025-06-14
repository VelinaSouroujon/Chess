#include "QueenSideCastleMove.h"

QueenSideCastleMove::QueenSideCastleMove()
    : whiteKingPosition('c', 1),
    blackKingPosition('c', 8),
    whiteRookPosition('d', 1),
    blackRookPosition('d', 8),
    whiteInitialRookPosition('a', 1),
    blackInitialRookPosition('a', 8)
{

}

const ChessCoordinate& QueenSideCastleMove::kingPosition(PieceColor color) const
{
    return color == PieceColor::White
        ? whiteKingPosition
        : blackKingPosition;
}

const ChessCoordinate& QueenSideCastleMove::rookPosition(PieceColor color) const
{
    return color == PieceColor::White
        ? whiteRookPosition
        : blackRookPosition;
}

const ChessCoordinate& QueenSideCastleMove::initialRookPosition(PieceColor color) const
{
    return color == PieceColor::White
        ? whiteInitialRookPosition
        : blackInitialRookPosition;
}

bool QueenSideCastleMove::execute(Game& game)
{
    if (!game.playingSide().getQueenSideCastlePossible())
    {
        return false;
    }

    return CastleMove::execute(game);
}
