#include "Game.h"
#include "EnPassantNotifier.h"
const ChessCoordinate* Game::getEnPassantSquare() const
{
    if (enPassantState == EnPassantState::None)
    {
        return nullptr;
    }

    return &enPassantSquare;
}
void Game::changeTurn()
{
    turnToMove =
        turnToMove == PieceColor::White
        ? PieceColor::Black
        : PieceColor::White;

    if (enPassantState != EnPassantState::None)
    {
        int nextEnPassantState = (int) enPassantState + 1;
        nextEnPassantState %= (int) EnPassantState::Count;

        enPassantState = (EnPassantState) nextEnPassantState;
    }
}

void Game::setEnPassantSquare(const ChessCoordinate& enPassantSquare)
{
    this->enPassantSquare = enPassantSquare;
    enPassantState = EnPassantState::JustSet;
}
