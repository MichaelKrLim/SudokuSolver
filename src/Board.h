#ifndef BOARD_H
#define BOARD_H

#include "Constants.h"
#include "Move.h"

#include <array>
#include <sstream>
#include <string>
#include <cctype>
#include <fstream>

namespace sudoku
{
    class Board
    {
        public:

        void move(const Move& move)
        {
            board_[move.position.row][move.position.column]=move.value+1;
        }

        [[nodiscard]] std::string pretty_print() const
        {
            std::string result;
            for(std::size_t r{0}; r<board_size; ++r)
            {
                for(std::size_t c{0}; c<board_size; ++c)
                {
                    if(board_[r][c])
                        result += std::to_string(board_[r][c]);
                    else
                        result += '-';
                    if(c < board_size - 1)
                        result += ',';
                }
                result += '\n';
            }
            return result;
        }

        Board(const std::string& filename)
        {   
            std::ifstream file(filename);
            for(std::size_t r{0}; r<board_size; ++r)
            {
                std::string line;
                if(!std::getline(file, line))
                    break;

                std::istringstream iss{line};
                for(std::size_t c=0; c<board_size; ++c)
                {
                    std::string	cell;
                    if(!std::getline(iss, cell, ','))
                        break;

                    if(!cell.empty())
                    {
                        std::size_t	value=std::stoi(cell)-1;
                        Position current_position{c, r};
                        move(Move{current_position, value});
                    }
                }
            }
        }

        private:

        std::array<std::array<int, board_size>, board_size> board_{{}};
    };
};

#endif // BOARD_H_INCLUDED