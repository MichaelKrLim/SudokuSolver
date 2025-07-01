#ifndef STATE_H
#define STATE_H

#include "Position.h"

#include <array>
#include <cstdint>
#include <generator>

namespace sudoku
{
    struct State
    {
        public:

        State();

        [[nodiscard]] std::generator<Position> lazy_move_generation() const noexcept;

        private:

        std::array<std::array<bool, board_size>, board_size> rows_;
        std::array<std::array<bool, board_size>, board_size> columns_;
        std::array<std::array<bool, board_size>, box_size> boxes_;
    };
};

#endif // STATE_H_INCLUDED