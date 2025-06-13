#include <stdexcept>
#include "UserInterface.h"

const PieceRenderer& UserInterface::getPieceRenderer() const
{
    return pieceRenderer;
}

UserInterface::UserInterface(PieceRenderer& pieceRenderer) : pieceRenderer(pieceRenderer)
{

}
