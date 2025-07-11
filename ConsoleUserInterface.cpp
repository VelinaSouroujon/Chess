#include <iostream>
#define NOMINMAX
#include <Windows.h>
#include <algorithm>
#include <io.h>
#include <fcntl.h>
#include "Piece.h"
#include "ConsoleUserInterface.h"
#include "Constants.h"

ConsoleUserInterface::ConsoleUserInterface(PieceRenderer& pieceRenderer)
    : UserInterface(pieceRenderer)
{

}

void ConsoleUserInterface::drawBoardWhite(const Board& board) const
{
    drawPerspective(board, true);
}

void ConsoleUserInterface::drawBoardBlack(const Board& board) const
{
    drawPerspective(board, false);
}

void ConsoleUserInterface::renderGame(const Board& board) const
{
    drawBoardWhite(board);

    std::wcout << std::endl;

    drawBoardBlack(board);
}

void ConsoleUserInterface::drawPerspective(const Board& board, bool whitePerspective) const
{
    int originalMode = _setmode(_fileno(stdout), _O_U16TEXT);

    const int cellWidth = 4;
    const int cellHeight = 1;
    const int middleLine = cellHeight / 2;

    int rowStart = whitePerspective ? Constants::BOARD_SIZE : Constants::MIN_ROW_COORDINATE;
    int rowEnd = whitePerspective ? Constants::MIN_ROW_COORDINATE - 1 : Constants::BOARD_SIZE + 1;
    int rowStep = whitePerspective ? -1 : 1;

    int colStart = whitePerspective ? Constants::MIN_COL_COORDINATE : Constants::MAX_COL_COORDINATE;
    int colEnd = whitePerspective ? Constants::MAX_COL_COORDINATE + 1 : Constants::MIN_COL_COORDINATE - 1;
    int colStep = whitePerspective ? 1 : -1;

    for (int row = rowStart; row != rowEnd; row += rowStep)
    {
        for (int line = 0; line < cellHeight; ++line)
        {
            if (line == middleLine)
            {
                std::wcout << row << L" ";
            }
            else
            {
                std::wcout << L"  ";
            }

            for (char col = colStart; col != colEnd; col += colStep)
            {
                bool isWhiteSquare = ((row + col) % 2 == 0);
                int bgColor = isWhiteSquare ? 8 : 4;

                const Piece* piece = board.at(col, row);
                int textColor = piece
                    ? (piece->getColor() == PieceColor::White ? 15 : 0)
                    : 7;

                setColor(textColor, bgColor);

                if (line == middleLine)
                {
                    wchar_t symbol = piece ? piece->accept(getPieceRenderer()) : L' ';
                    int padLeft = (cellWidth - 1) / 2;
                    int padRight = cellWidth - 1 - padLeft;
                    std::wcout
                        << std::wstring(padLeft, L' ')
                        << symbol
                        << std::wstring(padRight, L' ');
                }
                else
                {
                    std::wcout << std::wstring(cellWidth, L' ');
                }

                setColor(15, 0);
            }

            std::wcout << std::endl;
        }
    }

    std::wcout << L"   ";
    for (char col = colStart; col != colEnd; col += colStep)
    {
        std::wcout << col << std::wstring(cellWidth - 1, L' ');
    }

    std::wcout << std::endl;

    _setmode(_fileno(stdout), originalMode);
}

void ConsoleUserInterface::setColor(int textColor, int bgColor) const
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, textColor + (bgColor << 4));
}
