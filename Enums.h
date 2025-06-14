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

enum class CheckState
{
	None,
	Check,
	DoubleCheck
};

enum class CaptureState
{
	Capture,
	NonCapture,
	DoesNotMatter
};
