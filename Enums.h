#pragma once

enum class PieceColor
{
	White = 1,
	Black = -1
};

enum class EnPassantState
{
	None,
	JustSet,
	ToBeResetAfterOneMove,
	Count
};
