#include "CastleMove.h"
#include "Piece.h"
#include "CommonUtils.h"

bool CastleMove::execute(Game& game)
{
    ChessVariant& chessVariant = game.getChessVariant();
    Board& board = game.getChessVariant().getBoard();
    PieceColor color = game.getTurnToMove();

    const ChessCoordinate& newKingPosition = kingPosition(color);
    const ChessCoordinate& newRookPosition = rookPosition(color);

    Piece* king = board.at(chessVariant.kingInitialPos(color));
    Piece* rook = board.at(initialRookPosition(color));

    if (king == nullptr || rook == nullptr)
    {
        return false;
    }
    if (board.isPieceBetween(king->getPosition(), rook->getPosition()))
    {
        return false;
    }

    OneColorPieces& awaitingSidePieces = game.awaitingSide().getPieces();

    int row = newKingPosition.getRow();
    char startColIdx = chessVariant.kingInitialPos(color).getCol();
    char endColIdx = newKingPosition.getCol();

    if (startColIdx > endColIdx)
    {
        CommonUtils::swap(startColIdx, endColIdx);
    }

    for (char col = startColIdx; col <= endColIdx; col++)
    {
        ChessCoordinate coordinate(col, row);

        if (awaitingSidePieces.isSquareAttacked(coordinate, board))
        {
            return false;
        }
    }

    game.awaitingSide().updateAttackers(newKingPosition);

    const ChessCoordinate& oppositeKingCoord = game.awaitingSide().getKing().getPosition();
    Move move(newRookPosition, oppositeKingCoord, true);
    if (rook->isValidMove(move))
    {
        game.playingSide().indirectAttackersOnOppositeKing().add(*rook);
    }

    board.setAt(newKingPosition, king);
    board.setAt(chessVariant.kingInitialPos(color), nullptr);

    board.setAt(newRookPosition, rook);
    board.setAt(initialRookPosition(color), nullptr);

    game.sameColorPiecesInfo(color).impossibleKingSideCastle();
    game.sameColorPiecesInfo(color).impossibleQueenSideCastle();

    return true;
}
