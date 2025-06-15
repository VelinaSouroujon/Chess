#pragma once

#include "Enums.h"

class Game;
class PiecesGameInfo;

class StringGameSerializer
{
private:
	void serializeOneSidePieces(const PiecesGameInfo& gameInfoPieces, char* buffer, int& idx) const;

public:
	static const int MAX_SERIALIZATION_LENGTH = 89;

	void serializeGame(const Game& game, char* buffer, PieceColor turnToMove) const;
};

