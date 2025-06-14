#include "StandardRulesEngine.h"
#include "Game.h"
#include "Move.h"
#include "CommonUtils.h"
bool StandardRulesEngine::kingHasLegalMoves(const Game& game) const
{
    const OneColorPieces& pieces = game.playingSide().getPieces();
    const Board& board = game.getChessVariant().getBoard();
    const ChessCoordinate& oppositeSideKingPosition = game.awaitingSide().getKing().getPosition();
    PieceColor turnToMove = game.getTurnToMove();

    const int KING_MOVES_COUNT = 8;
    const int DIRECTION_LEN = 2;

    int kingDirections[KING_MOVES_COUNT][DIRECTION_LEN] =
    { { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 }, { -1, 1 }, { 1, -1 }, { 1, 1 }, { -1, -1 } };

    for (int i = 0; i < KING_MOVES_COUNT; i++)
    {
        char col = oppositeSideKingPosition.getCol() + kingDirections[i][1];
        int row = oppositeSideKingPosition.getRow() + kingDirections[i][0];

        if ((!CommonUtils::isInRange(row, Constants::MIN_ROW_COORDINATE, Constants::BOARD_SIZE))
            || (!CommonUtils::isInRange(col, Constants::MIN_COL_COORDINATE, Constants::MAX_COL_COORDINATE)))
        {
            continue;
        }

        ChessCoordinate coordinate(col, row);
        const Piece* pieceAtSquare = board.at(coordinate);

        if ((pieceAtSquare != nullptr) && (pieceAtSquare->getColor() != turnToMove))
        {
            continue;
        }

        if (!pieces.isSquareAttacked(coordinate, board))
        {
            return true;
        }
    }

    return false;
}
