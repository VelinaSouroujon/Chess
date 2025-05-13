#include <stdexcept>
#include "UserInterface.h"

PieceRenderer* UserInterface::getPieceRenderer() const
{
    return pieceRenderer;
}

UserInterface::UserInterface(PieceRenderer* pieceRenderer)
{
    if (pieceRenderer == nullptr)
    {
        throw std::invalid_argument("Piece renderer cannot be null.");
    }

    this->pieceRenderer = pieceRenderer;
}
