#include <stdexcept>
#include "GameNotifier.h"

Game& GameNotifier::getGame()
{
	if (game == nullptr)
	{
		throw std::logic_error("Game not set.");
	}

	return *game;
}

const Game& GameNotifier::getGame() const
{
	if (game == nullptr)
	{
		throw std::logic_error("Game not set.");
	}

	return *game;
}

void GameNotifier::setGame(Game& game)
{
	this->game = &game;
}
