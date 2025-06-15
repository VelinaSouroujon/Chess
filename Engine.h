#pragma once

#include <iostream>
#include "Game.h"
#include "ChessVariant.h"
#include "UserInterface.h"

class Engine
{
private:
	UserInput getMoveInput(char* buffer, int lengthBuffer, std::istream& is, std::ostream& os) const;
	InputMoveResult handleMove(Game& game, std::istream& is, std::ostream& os) const;
	void serialize(const Game& game, std::istream& is, std::ostream& os) const;

public:
	void run(Game& game, std::istream& is, std::ostream& os, ChessVariant& chessVariant, const UserInterface& userInterface) const;
};

