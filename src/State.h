#ifndef STATE_H
#define STATE_H

#include "Move.h"
#include "Position.h"


#include <array>
#include <cstdint>
#include <generator>
#include <string>
#include <stack>

namespace sudoku
{
    struct State
    {
        public:

        State(const std::string& file_name);

        [[nodiscard]] std::generator<Move> lazy_move_generation() const noexcept;
        [[nodiscard]] bool is_solved() const noexcept;
        void move(const Move& move) noexcept;
        void unmove() noexcept;

        private:

        std::stack<Move> previous_moves_;
        std::size_t original_squares_used{0};
        std::array<std::array<bool, board_size>, board_size> rows_{{}};
        std::array<std::array<bool, board_size>, board_size> columns_{{}};
        std::array<std::array<bool, board_size>, board_size> boxes_{{}};
        std::array<bool, board_size*board_size> filled_squares_{{}};
    };
};

#endif // STATE_H_INCLUDED