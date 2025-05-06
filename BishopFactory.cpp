#include "BishopFactory.h"
#include "Bishop.h"

Piece* BishopFactory::create() const
{
    return new Bishop();
}
