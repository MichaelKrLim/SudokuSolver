#ifndef Position_h_INCLUDED
#define Position_h_INCLUDED

#include "Constants.h"

#include <cstdint>
#include <iostream>
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
			column = board_index/board_size;
			row = board_index%board_size;
		}
		template <typename T, typename L, typename = std::enable_if_t<std::is_integral<T>::value>, typename = std::enable_if_t<std::is_integral<L>::value>>
		explicit constexpr Position(T column, L row) : column(static_cast<int>(column)), row(static_cast<int>(row)) {}

		friend std::istream& operator>>(std::istream& is, Position& position)
        {
            return is>>position.column>>position.row;
        }
	};

	constexpr std::size_t to_index(const Position& position)
	{
		return board_size*position.column+position.row;
	}
    
	constexpr std::size_t box_index(const Position& position)
	{
		return (position.row/3)*3+position.column/3;
	}
}

#endif // Position_h_INCLUDED