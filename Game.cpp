#include <stdexcept>
#include "Game.h"
#include "EnPassantNotifier.h"

Game::Game(ChessVariant& chessVariant, RulesEngine& rulesEngine) 
    : chessVariant(chessVariant),
    rulesEngine(rulesEngine),
    white(PieceColor::White, chessVariant.getBoard()),
    black(PieceColor::Black, chessVariant.getBoard())
{

}

const PiecesGameInfo& Game::playingSide() const
{
    return turnToMove == PieceColor::White
        ? white
        : black;
}

const PiecesGameInfo& Game::awaitingSide() const
{
    return turnToMove == PieceColor::White
        ? black
        : white;
}

const PiecesGameInfo& Game::sameColorPiecesInfo(PieceColor color) const
{
    return color == PieceColor::White
        ? white
        : black;
}

const PiecesGameInfo& Game::oppositeColorPiecesInfo(PieceColor color) const
{
    return color == PieceColor::White
        ? black
        : white;
}

const List<PositionCount>& Game::getPositionsCount() const
{
    return positionsCount;
}

const ChessVariant& Game::getChessVariant() const
{
    return chessVariant;
}

const ChessCoordinate* Game::getEnPassantSquare() const
{
    if (enPassantState == EnPassantState::None)
    {
        return nullptr;
    }

    return &enPassantSquare;
}

PiecesGameInfo& Game::playingSide()
{
    return turnToMove == PieceColor::White
        ? white
        : black;
}

PiecesGameInfo& Game::awaitingSide()
{
    return turnToMove == PieceColor::White
        ? black
        : white;
}

PiecesGameInfo& Game::sameColorPiecesInfo(PieceColor color)
{
    return color == PieceColor::White
        ? white
        : black;
}

PiecesGameInfo& Game::oppositeColorPiecesInfo(PieceColor color)
{
    return color == PieceColor::White
        ? black
        : white;
}

PieceColor Game::getTurnToMove() const
{
    return turnToMove;
}

PieceColor Game::getAwaitingSideColor() const
{
    return turnToMove == PieceColor::White
        ? PieceColor::Black
        : PieceColor::White;
}

ChessVariant& Game::getChessVariant()
{
    return chessVariant;
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

void Game::previousPositionsUnreachable()
{
    positionsCount.resetSize();
}

void Game::setEnPassantSquare(const ChessCoordinate& enPassantSquare)
{
    this->enPassantSquare = enPassantSquare;
    enPassantState = EnPassantState::JustSet;
}

List<PositionCount>& Game::getPositionsCount()
{
    return positionsCount;
}

const RulesEngine& Game::rules() const
{
    return rulesEngine;
}
