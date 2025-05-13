#pragma once

#include "ChessVariant.h"

class StandardChessVariant : public ChessVariant
{
private:
	void initPiecesOnBoard() override;

public:
	StandardChessVariant();
};

