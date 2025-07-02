#ifndef	STATE_H
#define	STATE_H

#include "Move.h"

#include <array>
#include <bitset>
#include <generator>
#include <string>
#include <stack>

namespace sudoku
{
	struct State
	{
		public:

		State(const	std::string& file_name);

		[[nodiscard]] std::generator<Move> lazy_move_generation() const	noexcept;
		[[nodiscard]] bool is_solved() const noexcept;
		void move(const	Move& move)	noexcept;
		void unmove() noexcept;

		private:

		enum class Move_type
		{
			moving, unmoving, size
		};

		void update_legal_moves(const Move&	move) noexcept;
		using Legal_moves=std::array<std::bitset<board_size>, board_size*board_size>;
		Legal_moves legal_moves_;
		std::stack<Legal_moves> previous_moves_;
		std::size_t	original_squares_used{0};
	};
};

#endif // STATE_H_INCLUDED
