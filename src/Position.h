#ifndef Position_h_INCLUDED
#define Position_h_INCLUDED

#include "Constants.h"

#include <type_traits>

namespace sudoku
{
	struct Position
	{
		unsigned column{}, row{};

		constexpr bool operator==(const Position& rhs) const { return column == rhs.column && row == rhs.row; }
		constexpr Position operator+(const Position& to_add) const { return Position{column + to_add.column, row + to_add.row}; }
		
		constexpr Position operator+=(const Position& to_add) { column += to_add.column; row += to_add.row; return *this; }

		constexpr Position() = default;
		constexpr Position(const Position&) = default;
		explicit constexpr Position(const std::size_t& board_index)
		{
			column = board_index%board_size;
			row = board_index/board_size;
		}
		template <typename T, typename L, typename = std::enable_if_t<std::is_integral<T>::value>, typename = std::enable_if_t<std::is_integral<L>::value>>
		explicit constexpr Position(T column, L row) : column(static_cast<unsigned>(column)), row(static_cast<unsigned>(row)) {}
	};

	constexpr std::size_t to_index(const Position& position)
	{
		return board_size*position.row+position.column;
	}

	constexpr Position box_position(const Position& position)
	{
		return Position{(position.column/box_size)*box_size, (position.row/box_size)*box_size};
	}
}

#endif // Position_h_INCLUDED
