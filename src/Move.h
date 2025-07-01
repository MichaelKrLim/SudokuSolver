#ifndef MOVE_H
#define MOVE_H

#include <ostream>

#include "Position.h"

namespace sudoku
{
    struct Move
    {
        Move(const Position& position, const std::size_t value) noexcept : position(position), value(value) {}

        Position position;
        std::size_t value;
    };

    inline std::ostream& operator<<(std::ostream& os, const Move& move)
    {
        return os << "(" << move.position.column << ' ' << move.position.row << ")=" << move.value;
    }
};

#endif // MOVE_H_INCLUDED
