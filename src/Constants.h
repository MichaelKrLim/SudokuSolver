#ifndef	CONSTANTS_H
#define	CONSTANTS_H

#include <cmath>

namespace sudoku
{
	constexpr int board_size=36,
	box_size=std::sqrt(board_size);
};

#endif // CONSTANTS_H_INCLUDED