#pragma once

namespace Constants
{
	const int BOARD_SIZE = 8;
	const int MIN_ROW_COORDINATE = 1;
	const char MIN_COL_COORDINATE = 'a';
	const char MAX_COL_COORDINATE = MIN_COL_COORDINATE + BOARD_SIZE - 1;
	const int MAX_NOTATION_LENGTH = 3;

	const char ROOK_NOTATION = 'R';
	const char KNIGHT_NOTATION = 'N';
	const char BISHOP_NOTATION = 'B';
	const char QUEEN_NOTATION = 'Q';
	const char KING_NOTATION = 'K';
	const char PAWN_NOTATION = '\0';

	const char CAPTURE_DELIMITER = 'x';
	const char FROM_TO_DELIMITER = ' ';
}
