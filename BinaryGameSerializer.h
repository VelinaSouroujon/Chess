#pragma once

#include <iostream>
#include "Game.h"
#include "PieceFactory.h"

class BinaryGameSerializer
{
private:
	bool serializePieces(const PiecesGameInfo& gameInfoPieces, std::ostream& os) const;
	bool deserializePieces(PiecesGameInfo& gameInfoPieces, Board& board, std::istream& is, const IPieceFactory& pieceFactory) const;

public:
	bool serialize(const Game& game, std::ostream& os) const;
	bool deserialize(Game& game, std::istream& is, const IPieceFactory& pieceFactory) const;
};

