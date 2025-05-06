#include "QueenFactory.h"
#include "Queen.h"

Piece* QueenFactory::create() const
{
    return new Queen();
}
