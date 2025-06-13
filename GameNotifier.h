#pragma once

#include "Game.h"

class GameNotifier
{
private:
	Game* game = nullptr;

protected:
	Game& getGame();
	const Game& getGame() const;

public:
	virtual ~GameNotifier() = default;

	void setGame(Game& game);

	virtual void notifyGame(const Piece& sender) = 0;
};

