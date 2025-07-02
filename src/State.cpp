#include "State.h"
#include "Constants.h"

#include <algorithm>
#include <bit>
#include <cctype>
#include <cstdint>
#include <fstream>
#include <iterator>
#include <sstream>

using namespace	sudoku;

void State::update_legal_moves(const Move& move) noexcept
{
	for(std::size_t i{0}; i<board_size; ++i)
	{
		legal_moves_[to_index(Position{i, move.position.row})].reset(move.value);
		legal_moves_[to_index(Position{move.position.column, i})].reset(move.value);
	}

	for(std::size_t column_offset{0}; column_offset<box_size; ++column_offset)
	{
		for(std::size_t row_offset{0}; row_offset<box_size; ++row_offset)
		{
			legal_moves_[to_index(box_position(move.position)+Position{column_offset, row_offset})].reset(move.value);
		}
	}

	legal_moves_[to_index(move.position)].reset();
}

State::State(const std::string& filename)
{
	std::ifstream file(filename);
	original_squares_used=0;
	for(auto& square : legal_moves_)
		square.set();
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
				++original_squares_used;
			}
		}
	}
	previous_moves_={};
}

void State::move(const Move& move) noexcept
{
	previous_moves_.push(legal_moves_);
	update_legal_moves(move);
}

void State::unmove() noexcept
{
	legal_moves_=std::move(previous_moves_.top());
	previous_moves_.pop();
}

std::generator<Move> State::lazy_move_generation() const noexcept
{
	auto& moves_range=legal_moves_;
	auto best_it=std::ranges::find_if(moves_range, [](const auto& moves){ return moves.count()==1; });
	if(best_it==moves_range.end())
	{
		best_it = std::ranges::min_element(moves_range,	[](const auto& lhs, const auto& rhs)
		{
			if (lhs.count()==0) return false;
			if (rhs.count()==0) return true;
			return lhs.count()<rhs.count();
		});
	}

	if(best_it==moves_range.end() || best_it->count()==0)
		co_return;

	const auto best_index=std::distance(moves_range.begin(), best_it);
	const Position best_position(best_index);
	for(std::uint16_t legal_moves_copy=best_it->to_ulong(); legal_moves_copy>0;)
	{
		const std::size_t value=std::countr_zero(legal_moves_copy);
		co_yield Move{best_position, value};
		legal_moves_copy&=legal_moves_copy-1;
	}
}

bool State::is_solved()	const noexcept
{
	return previous_moves_.size()==(board_size*board_size-original_squares_used);
}
