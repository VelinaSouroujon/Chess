#include "KnightFactory.h"
#include "Knight.h"

Piece* KnightFactory::create() const
{
    return new Knight();
}
