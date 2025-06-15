#include <stdexcept>
#include "StandardRulesEngine.h"
#include "Game.h"
#include "Move.h"
#include "CommonUtils.h"
#include "Array.hpp"
#include "PieceDirection.h"
#include "StringGameSerializer.h"

bool StandardRulesEngine::kingHasLegalMoves(Game& game) const
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
        bool isCapture = board.at(coordinate) != nullptr;
        Move move(oppositeSideKingPosition, coordinate, isCapture);

        if (move.canExecute(game))
        {
            return true;
        }
    }

    return false;
}

bool StandardRulesEngine::canBlockCheck(Game& game, const ChessCoordinate* pathBetweenKingAndAttacker, int pathLength) const
{
    if (pathBetweenKingAndAttacker == nullptr)
    {
        throw std::invalid_argument("Path between king and checking piece cannot be null");
    }

    const OneColorPieces& awaitingSidePieces = game.awaitingSide().getPieces();
    const Piece& awaitingSideKing = game.awaitingSide().getKing();

    for (int i = 0; i < pathLength; i++)
    {
        const ChessCoordinate& squareBetweenKingAndAttacker = pathBetweenKingAndAttacker[i];

        if (canOneSideMoveToSquare(game, awaitingSidePieces.getColor(), squareBetweenKingAndAttacker, &awaitingSideKing))
        {
            return true;
        }
    }

    return false;
}

CheckState StandardRulesEngine::getCheckState(const Game& game, int& singleCheckAttackingPieceIdx) const
{
    singleCheckAttackingPieceIdx = -1;

    const Board& board = game.getChessVariant().getBoard();
    const OneColorPieces& playingSideAttackers = game.playingSide().indirectAttackersOnOppositeKing();
    int attackersCount = playingSideAttackers.getSize();
    const ChessCoordinate& oppositeSideKingPosition = game.awaitingSide().getKing().getPosition();

    CheckState checkState = CheckState::None;

    for (int i = 0; i < attackersCount; i++)
    {
        const Piece& attackingPiece = playingSideAttackers[i];
        const ChessCoordinate& attackingPiecePosition = attackingPiece.getPosition();

        Move move(attackingPiecePosition, oppositeSideKingPosition, true);

        if (attackingPiece.isValidMove(move) && (!board.isPieceBetween(attackingPiecePosition, oppositeSideKingPosition)))
        {
            int newCheckState = (int) checkState + 1;
            checkState = (CheckState) newCheckState;

            if (checkState == CheckState::DoubleCheck)
            {
                singleCheckAttackingPieceIdx = -1;
                break;
            }
            else
            {
                singleCheckAttackingPieceIdx = i;
            }
        }
    }

    return checkState;
}

bool StandardRulesEngine::canOneSideMoveToSquare(Game& game, PieceColor sideColor, const ChessCoordinate& targetSquare, const Piece* excludedPiece) const
{
    const Board& board = game.getChessVariant().getBoard();
    const OneColorPieces& pieces = game.sameColorPiecesInfo(sideColor).getPieces();
    int countPieces = pieces.getSize();
    bool isCapture = board.at(targetSquare) != nullptr;

    for (int i = 0; i < countPieces; i++)
    {
        const Piece& currPiece = pieces[i];
        if (&currPiece == excludedPiece)
        {
            continue;
        }

        const ChessCoordinate& positionCurrPiece = currPiece.getPosition();

        Move move(positionCurrPiece, targetSquare, isCapture);

        if (move.canExecute(game))
        {
            return true;
        }
    }

    return false;
}

bool StandardRulesEngine::insufficientMaterialForSide(const OneColorPieces& side) const
{
    const int MAX_PIECES_FOR_INSUFFICIENT_MATERIAL = 2;
    int countPieces = side.getSize();

    if (countPieces > MAX_PIECES_FOR_INSUFFICIENT_MATERIAL)
    {
        return false;
    }
    if (countPieces == 1)
    {
        return true;
    }

    return (!side[0].isSufficientForWin()) && (!side[1].isSufficientForWin());
}

bool StandardRulesEngine::isStalemate(Game& game) const
{
    const Board& board = game.getChessVariant().getBoard();
    const Piece *const * awaitingSidePieces = game.awaitingSide().getPieces().getPieces();
    int countAwaitingPieces = game.awaitingSide().getPieces().getSize();

    for (int i = 0; i < countAwaitingPieces; i++)
    {
        const Piece* currPiece = awaitingSidePieces[i];
        const ChessCoordinate& coordPiece = currPiece->getPosition();

        Array<PieceDirection, Constants::MAX_DIRECTIONS_COUNT> pieceDirections;
        currPiece->fillDirections(pieceDirections);

        for (int i = 0; i < pieceDirections.length(); i++)
        {
            const PieceDirection& currDirection = pieceDirections[i];

            for (int idxStep = 1; idxStep <= currDirection.getSteps(); idxStep++)
            {
                char col = coordPiece.getCol() + idxStep * currDirection.x();
                int row = coordPiece.getRow() + idxStep * currDirection.y();

                if ((!CommonUtils::isInRange(row, Constants::MIN_ROW_COORDINATE, Constants::BOARD_SIZE)) 
                    || (!CommonUtils::isInRange(col, Constants::MIN_COL_COORDINATE, Constants::MAX_COL_COORDINATE)))
                {
                    break;
                }

                ChessCoordinate newCooord(col, row);

                CaptureState captureState = currDirection.getCaptureState();
                bool isCapture;
                if (captureState == CaptureState::DoesNotMatter)
                {
                    isCapture = board.at(newCooord) != nullptr;
                }
                else
                {
                    isCapture = captureState == CaptureState::Capture;
                }

                Move move(coordPiece, newCooord, isCapture);

                if (move.canExecute(game))
                {
                    return false;
                }
                else
                {
                    break;
                }
           }
        }
    }

    return true;
}

bool StandardRulesEngine::isThreefoldRepetition(Game& game) const
{
    PositionCount currPosition;
    PieceColor turnToMove = game.getTurnToMove() == PieceColor::White
        ? PieceColor::Black
        : PieceColor::White;

    StringGameSerializer serializer;
    serializer.serializeGame(game, currPosition.position, turnToMove);

    List<PositionCount>& positionsCount = game.getPositionsCount();
    int totalPositionsCount = positionsCount.count();
    int idx = -1;

    for (int i = 0; i < totalPositionsCount; i++)
    {
        if (strcmp(currPosition.position, positionsCount[i].position) == 0)
        {
            idx = i;
            break;
        }
    }

    if (idx < 0)
    {
        positionsCount.add(currPosition);
    }
    else
    {
        positionsCount[idx].count++;

        if (positionsCount[idx].count >= REPETITION_COUNT_FOR_DRAW)
        {
            return true;
        }
    }

    return false;
}

bool StandardRulesEngine::isWin(Game& game, CheckState& checkState) const
{
    int singleCheckAttackingPieceIdx = -1;
    checkState = getCheckState(game, singleCheckAttackingPieceIdx);

    if (checkState == CheckState::None)
    {
        return false;
    }

    if (kingHasLegalMoves(game))
    {
        return false;
    }

    if (checkState == CheckState::DoubleCheck)
    {
        return true;
    }

    const Board& board = game.getChessVariant().getBoard();
    const ChessCoordinate& attackerCoord = game.playingSide().indirectAttackersOnOppositeKing()[singleCheckAttackingPieceIdx].getPosition();

    const Piece& awaitingSideKing = game.awaitingSide().getKing();
    const ChessCoordinate& coordAwaitingSideKing = awaitingSideKing.getPosition();

    const int MAX_PATH_LENGTH = Constants::BOARD_SIZE - 2;
    ChessCoordinate pathBetweenKingAndAttacker[MAX_PATH_LENGTH];
    int pathLength = 0;

    if (canOneSideMoveToSquare(game, game.getAwaitingSideColor(), attackerCoord, &awaitingSideKing))
    {
        return false;
    }

    if (!board.tryGetPathBetweenTwoSquares(attackerCoord, coordAwaitingSideKing, pathBetweenKingAndAttacker, pathLength))
    {
        return true;
    }

    return (!canBlockCheck(game, pathBetweenKingAndAttacker, pathLength));
}

bool StandardRulesEngine::isDraw(Game& game) const
{
    return (insufficientMaterialForSide(game.playingSide().getPieces())
        && insufficientMaterialForSide(game.awaitingSide().getPieces()))
        || isStalemate(game)
        || isThreefoldRepetition(game);
}

GameResult StandardRulesEngine::getResult(Game& game) const
{
    CheckState checkState;
    if (isWin(game, checkState))
    {
        return GameResult::Win;
    }

    if (checkState == CheckState::None && isDraw(game))
    {
        return GameResult::Draw;
    }

    return GameResult::None;
}
