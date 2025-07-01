#include "State.h"

#include <cctype>
#include <fstream>
#include <sstream>

using namespace sudoku;

State::State(const std::string& filename)
{
    std::ifstream file(filename);
    original_squares_used=0;
    int index{0};
    for(std::string line; std::getline(file, line);)
    {
        std::istringstream iss{line};
        std::string cell;
        while(std::getline(iss, cell, ','))
        {
            if(!cell.empty() && std::isdigit(cell[0]) && cell[0] != '0')
            {
                int value=cell[0]-'0'-1;
                Position current_position{index};
                filled_squares_[index]=true;
                rows_[current_position.row][value]=true;
                columns_[current_position.column][value]=true;
                boxes_[box_index(current_position)][value]=true;
                ++original_squares_used;
            }
            ++index;
        }
    }
}

void State::move(const Move& move) noexcept
{
    previous_moves_.push(move);
    filled_squares_[to_index(move.position)]=true;
    rows_[move.position.row][move.value]=true;
    columns_[move.position.column][move.value]=true;
    boxes_[box_index(move.position)][move.value]=true;
}

void State::unmove() noexcept
{
    const Move last_move{std::move(previous_moves_.top())};
    previous_moves_.pop();
    filled_squares_[to_index(last_move.position)]=false;
    rows_[last_move.position.row][last_move.value]=false;
    columns_[last_move.position.column][last_move.value]=false;
    boxes_[box_index(last_move.position)][last_move.value]=false;
}

std::generator<Move> State::lazy_move_generation() const noexcept
{
    for(std::size_t column{0}; column<board_size; ++column)
    {
        for(std::size_t row{0}; row<board_size; ++row) 
        {
            Position current_position{column, row};
            if(filled_squares_[to_index(current_position)])
                continue;
            const auto& row_contains = rows_[row];
            const auto& column_contains = columns_[column];
            const auto& box_contains = boxes_[box_index(current_position)];
            for(std::size_t value{0}; value<board_size; ++value)
            {
                if(row_contains[value] || column_contains[value] || box_contains[value])
                    continue;
                co_yield Move{std::move(current_position), value};
            }
        }
    }
}

bool State::is_solved() const noexcept
{
    return previous_moves_.size()==(board_size*board_size-original_squares_used);
}