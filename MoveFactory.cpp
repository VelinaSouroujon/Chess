#include <cstring>
#include "MoveFactory.h"
#include "KingSideCastleMove.h"
#include "QueenSideCastleMove.h"
#include "PromotionMove.h"
#include "CommonUtils.h"

Move* MoveFactory::createMove(const char* notation)
{
	if (CommonUtils::strCompareCaseInsensitive(Constants::KING_SIDE_CASTLE, notation) == 0
		|| CommonUtils::strCompareCaseInsensitive(Constants::KING_SIDE_CASTLE_ALTERNATIVE, notation) == 0)
	{
		return new KingSideCastleMove();
	}

	if (CommonUtils::strCompareCaseInsensitive(Constants::QUEEN_SIDE_CASTLE, notation) == 0
		|| CommonUtils::strCompareCaseInsensitive(Constants::QUEEN_SIDE_CASTLE_ALTERNATIVE, notation) == 0)
	{
		return new QueenSideCastleMove();
	}

	if (CommonUtils::isLetter(notation[strlen(notation) - 1]))
	{
		return new PromotionMove(notation);
	}

	return new Move(notation);
}
