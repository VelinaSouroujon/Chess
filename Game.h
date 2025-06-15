#pragma once

#include "ChessVariant.h"
#include "PiecesGameInfo.h"
#include "RulesEngine.h"
#include "StringGameSerializer.h"
#include "List.hpp"
#include "PositionCount.h"

class BinaryGameSerializer;

class Game
{
private:
	ChessVariant& chessVariant;
	RulesEngine& rulesEngine;

	PiecesGameInfo white;
	PiecesGameInfo black;

	PieceColor turnToMove = PieceColor::White;

	ChessCoordinate enPassantSquare;
	EnPassantState enPassantState = EnPassantState::None;

	List<PositionCount> positionsCount;

public:
	friend void StringGameSerializer::serializeGame(const Game& game, char* buffer, PieceColor turnToMove) const;
	friend class BinaryGameSerializer;

	Game(ChessVariant& chessVariant, RulesEngine& rulesEngine);

	const PiecesGameInfo& playingSide() const;
	const PiecesGameInfo& awaitingSide() const;
	const PiecesGameInfo& sameColorPiecesInfo(PieceColor color) const;
	const PiecesGameInfo& oppositeColorPiecesInfo(PieceColor color) const;
	const List<PositionCount>& getPositionsCount() const;

	PieceColor getTurnToMove() const;
	PieceColor getAwaitingSideColor() const;
	const ChessVariant& getChessVariant() const;
	const ChessCoordinate* getEnPassantSquare() const;
	const RulesEngine& rules() const;

	PiecesGameInfo& playingSide();
	PiecesGameInfo& awaitingSide();
	PiecesGameInfo& sameColorPiecesInfo(PieceColor color);
	PiecesGameInfo& oppositeColorPiecesInfo(PieceColor color);
	ChessVariant& getChessVariant();
	void changeTurn();
	void previousPositionsUnreachable();
	void setEnPassantSquare(const ChessCoordinate& enPassantSquare);
	List<PositionCount>& getPositionsCount();
};

