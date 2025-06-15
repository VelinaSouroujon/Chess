#include "StringGameSerializer.h"
#include "Game.h"

void StringGameSerializer::serializeOneSidePieces(const PiecesGameInfo& gameInfoPieces, char* buffer, int& idx) const
{
    if (buffer == nullptr || idx < 0)
    {
        return;
    }

    const Piece* const* pieces = gameInfoPieces.getPieces().getPieces();
    int countPieces = gameInfoPieces.getPieces().getSize();

    for (int i = 0; i < countPieces; i++)
    {
        const Piece* currPiece = pieces[i];
        char notation = currPiece->getPieceNotation();
        char col = currPiece->getPosition().getCol();
        int row = currPiece->getPosition().getRow();

        if (notation != Constants::PAWN_NOTATION)
        {
            buffer[idx++] = notation;
        }

        buffer[idx++] = col;
        buffer[idx++] = row;
    }

    bool kingSideCastlePossible = gameInfoPieces.getKingSideCastlePossible();
    bool queenSideCastlePossible = gameInfoPieces.getQueenSideCastlePossible();

    buffer[idx++] = kingSideCastlePossible;
    buffer[idx++] = queenSideCastlePossible;
}

void StringGameSerializer::serializeGame(const Game& game, char* buffer, PieceColor turnToMove) const
{
    if (buffer == nullptr)
    {
        return;
    }

    int idx = 0;

    serializeOneSidePieces(game.white, buffer, idx);
    serializeOneSidePieces(game.black, buffer, idx);

    int intTurnToMove = (int)turnToMove;
    buffer[idx++] = intTurnToMove;

    int enPassantState = (int)game.enPassantState;
    buffer[idx++] = enPassantState;

    if (game.enPassantState != EnPassantState::None)
    {
        char enPassantCol = game.enPassantSquare.getCol();
        int enPassantRow = game.enPassantSquare.getRow();

        buffer[idx++] = enPassantCol;
        buffer[idx++] = enPassantRow;
    }

    buffer[idx] = '\0';
}
