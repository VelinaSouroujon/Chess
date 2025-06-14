#pragma once

#include "UserInterface.h"

class ConsoleUserInterface : public UserInterface
{
public:
	ConsoleUserInterface(PieceRenderer& pieceRenderer);
	void drawBoard(const Board& board) const override;

	void setColor(int textColor, int bgColor) const;
};

