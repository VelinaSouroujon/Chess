#pragma once

#include "Board.h"
#include "PieceRenderer.h"

class UserInterface
{
private:
	PieceRenderer& pieceRenderer;

protected:
	const PieceRenderer& getPieceRenderer() const;

public:
	UserInterface(PieceRenderer& pieceRenderer);
	virtual ~UserInterface() = default;

	virtual void renderGame(const Board& board) const = 0;
};

