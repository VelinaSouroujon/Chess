#pragma once

#include "Board.h"
#include "PieceRenderer.h"

class UserInterface
{
private:
	PieceRenderer* pieceRenderer = nullptr;

protected:
	PieceRenderer* getPieceRenderer() const;

public:
	UserInterface(PieceRenderer* pieceRenderer);
	virtual ~UserInterface() = default;

	virtual void drawBoard(const Board& board) const = 0;
};

