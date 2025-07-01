#include "State.h"

#include <sstream>

using namespace sudoku;

State::State()
{       
    for(std::string line; std::getline(std::cin, line);)
    {
        std::istringstream iss{line};
        Position current_position;
        int value;
        iss>>current_position>>value;
        rows_[current_position.row][value]=true;
        columns_[current_position.column][value]=true;
        boxes_[box_index(current_position)][value]=true;
    }
}