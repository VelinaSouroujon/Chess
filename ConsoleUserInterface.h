#pragma once

#include "UserInterface.h"

class ConsoleUserInterface : public UserInterface
{
public:
	ConsoleUserInterface(PieceRenderer& pieceRenderer);

	void drawPerspective(const Board& board, bool whitePerspective) const;
	void drawBoardWhite(const Board& board) const;
	void drawBoardBlack(const Board& board) const;
	void renderGame(const Board& board) const override;

	void setColor(int textColor, int bgColor) const;
};

