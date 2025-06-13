#include <stdexcept>
#include "OneColorPieces.h"
#include "Move.h"
#include "CommonUtils.h"

OneColorPieces::OneColorPieces(PieceColor color) : color(color)
{

}

OneColorPieces::OneColorPieces(PieceColor color, const Board& board, const Piece*& king) : OneColorPieces(color)
{
    int start = color == PieceColor::White
        ? Constants::MIN_ROW_COORDINATE
        : Constants::BOARD_SIZE;

    int step = (int) color;
    const int COUNT = 2;

    int row = start;
    int currCount = 0;

    while (currCount < COUNT)
    {
        for (int col = Constants::MIN_COL_COORDINATE; col <= Constants::MAX_COL_COORDINATE; col++)
        {
            const Piece* pieceToAdd = board.at(col, row);
            if (pieceToAdd == nullptr)
            {
                continue;
            }

            add(*pieceToAdd);

            if (pieceToAdd->getPieceNotation() == Constants::KING_NOTATION)
            {
                king = pieceToAdd;
            }
        }

        row += step;
        currCount++;
    }
}

bool OneColorPieces::add(const Piece& pieceToAdd)
{
    if (size >= Constants::PIECES_COUNT_PER_SIDE)
    {
        return false;
    }

    pieces[size] = &pieceToAdd;
    size++;

    return true;
}

bool OneColorPieces::remove(const Piece& pieceToRemove)
{
    int idxToRemove = findIdx(pieceToRemove);

    if (idxToRemove < 0)
    {
        return false;
    }

    removeAt(idxToRemove);

    return true;
}

void OneColorPieces::removeAt(int idx)
{
    const int MIN_IDX = 0;
    if (!CommonUtils::isInRange(idx, MIN_IDX, size - 1))
    {
        throw std::invalid_argument("Index out of range.");
    }

    for (int i = idx; i < size - 1; i++)
    {
        pieces[i] = pieces[i + 1];
    }

    size--;
}

bool OneColorPieces::replace(const Piece& oldPiece, const Piece& newPiece)
{
    int idx = findIdx(oldPiece);

    if (idx < 0)
    {
        return false;
    }

    pieces[idx] = &newPiece;

    return true;
}

void OneColorPieces::clear()
{
    size = 0;
}

bool OneColorPieces::isSquareAttacked(const ChessCoordinate& targetSquare, const Board& board, const Piece* excludedPiece) const
{
    for (int i = 0; i < size; i++)
    {
        const Piece* currPiece = pieces[i];
        if (currPiece == excludedPiece)
        {
            continue;
        }

        const ChessCoordinate& positionCurrPiece = currPiece->getPosition();

        Move move(positionCurrPiece, targetSquare, true);

        if ((currPiece->isValidMove(move)) && (!board.isPieceBetween(positionCurrPiece, targetSquare)))
        {
            return true;
        }
    }

    return false;
}

const Piece& OneColorPieces::operator[](int index) const
{
    const int MIN_INDEX = 0;
    if (!CommonUtils::isInRange(index, MIN_INDEX, size - 1))
    {
        throw std::out_of_range("Index out of range.");
    }

    return *pieces[index];
}

int OneColorPieces::getSize() const
{
    return size;
}

PieceColor OneColorPieces::getColor() const
{
    return color;
}

const Piece* const* OneColorPieces::getPieces() const
{
    return pieces;
}

int OneColorPieces::findIdx(const Piece& piece) const
{
    for (int idx = 0; idx < size; idx++)
    {
        if (pieces[idx] == &piece)
        {
            return idx;
        }
    }

    return -1;
}
