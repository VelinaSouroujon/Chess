#include <iostream>
#include <fstream>
#include "StandardChessVariant.h"
#include "ConsoleUserInterface.h"
#include "UnicodePieceRenderer.h"
#include "Game.h"
#include "Engine.h"
#include "StandardRulesEngine.h"
#include "PieceFactory.h"
#include "EnPassantNotifier.h"
#include "PawnMoveNotifier.h"
#include "CastlingNotifier.h"
#include "BinaryGameSerializer.h"
#include "StringGameSerializer.h"
#include "CommonUtils.h"

int getInputOption(std::ostream& os, std::istream& is)
{
    if (!os.good())
    {
        throw std::runtime_error("Output stream file not in good state");
    }
    if (!is.good())
    {
        throw std::runtime_error("Input stream file not in good state");
    }

    os << "Please choose one of the following options:" << std::endl;
    os << "1) Start a new game" << std::endl;
    os << "2) Continue a previous game" << std::endl;

    int inputOption = CommonUtils::getNumberInRange(os, is, 1, 2);
    return inputOption;
}

void addStartingPosition(Game& game)
{
    PositionCount initialPosition;

    StringGameSerializer serializer;
    serializer.serializeGame(game, initialPosition.position, game.getTurnToMove());

    game.getPositionsCount().add(initialPosition);
}

void deserialize(Game& game, std::istream& is, std::ostream& os,
    PieceMediator& enPassantNotifier, PieceMediator& pawnMoveNotifier, PieceMediator& castlingNotifier)
{
    if (!os.good())
    {
        throw std::runtime_error("Output stream file not in good state");
    }
    if (!is.good())
    {
        throw std::runtime_error("Input stream file not in good state");
    }

    os << "Enter file name:" << std::endl;

    const int MAX_SIZE = 1024;
    char fileName[MAX_SIZE];
    is.getline(fileName, MAX_SIZE);
    std::ifstream file;
    file.open(fileName, std::ios::binary);

    while (!file.is_open())
    {
        os << "No file with such name exists. Please try again" << std::endl;

        is.getline(fileName, MAX_SIZE);
        file.open(fileName, std::ios::binary);
    }

    BinaryGameSerializer serializer;
    serializer.deserialize(game, file, PieceFactory(enPassantNotifier, pawnMoveNotifier, castlingNotifier, castlingNotifier));
    file.close();

    const ChessCoordinate& whiteKingPosition = game.sameColorPiecesInfo(PieceColor::White).getKing().getPosition();
    game.sameColorPiecesInfo(PieceColor::Black).updateAttackers(whiteKingPosition);

    const ChessCoordinate& blackKingPosition = game.sameColorPiecesInfo(PieceColor::Black).getKing().getPosition();
    game.sameColorPiecesInfo(PieceColor::White).updateAttackers(blackKingPosition);
}

void start(std::istream& is, std::ostream& os)
{
    if (!os.good())
    {
        throw std::runtime_error("Output stream file not in good state");
    }
    if (!is.good())
    {
        throw std::runtime_error("Input stream file not in good state");
    }

    EnPassantNotifier enPassantNotifier;
    PawnMoveNotifier pawnMoveNotifier;
    CastlingNotifier castlingNotifier;

    UnicodePieceRenderer pieceRenderer;
    ConsoleUserInterface consoleUI(pieceRenderer);

    StandardRulesEngine standardRulesEngine;

    int inputOption = getInputOption(os, is);
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    PieceFactory pieceFactory(enPassantNotifier, pawnMoveNotifier, castlingNotifier, castlingNotifier);
    PieceFactory* ptrPieceFactory = &pieceFactory;

    if (inputOption == 2)
    {
        ptrPieceFactory = nullptr;
    }

    StandardChessVariant chessVariant(ptrPieceFactory);
    Game game(chessVariant, standardRulesEngine);

    enPassantNotifier.setGame(game);
    pawnMoveNotifier.setGame(game);
    castlingNotifier.setGame(game);

    if (inputOption == 2)
    {
        deserialize(game, is, os, enPassantNotifier, pawnMoveNotifier, castlingNotifier);
    }
    else
    {
        addStartingPosition(game);
    }

    Engine engine;
    engine.run(game, is, os, chessVariant, consoleUI);
}

int main()
{
    std::istream& is = std::cin;
    std::ostream& os = std::cout;

    try
    {
        start(is, os);
    }
    catch (const std::runtime_error& ex)
    {
        std::cout << ex.what();
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what();
    }
    catch (...)
    {
        std::cout << "An error occurred";
    }

    return 0;
}
