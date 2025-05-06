#include "RookFactory.h"
#include "Rook.h"

Piece* RookFactory::create() const
{
    return new Rook();
}
