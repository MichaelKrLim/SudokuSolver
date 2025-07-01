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

        void update_legal_moves(const Move& move) noexcept;

        std::stack<Move> previous_moves_;
        std::size_t original_squares_used{0};
        std::array<std::bitset<board_size>, board_size*board_size> legal_moves_{{}};
    };
};

#endif // STATE_H_INCLUDED