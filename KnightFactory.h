#pragma once

#include "PieceFactory.h"

class KnightFactory : public PieceFactory
{
public:
	Piece* create() const override;
};

