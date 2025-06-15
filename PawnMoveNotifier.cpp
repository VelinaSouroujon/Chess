#include "PawnMoveNotifier.h"

void PawnMoveNotifier::notifyGame(const Piece& sender)
{
	getGame().previousPositionsUnreachable();
}

void PawnMoveNotifier::notifyMove(const Piece& piece)
{
	notifyGame(piece);
}
