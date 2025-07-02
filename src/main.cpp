#include <print>
#include <vector>

#include <iostream>
#include <print>

#include "Board.h"
#include "State.h"
#include "Solver.h"

using namespace	sudoku;

int	main(int argc, const char* argv[])
{
	if(argc<1)
		std::cout<<"usage <filepath>";

	State state{argv[1]};
	Board board{argv[1]};
	[[maybe_unused]] const auto output_line = [](const std::vector<Move>& line)
	{
		std::print("solution: ");
		for(const auto& move : line)
			std::cout<<' '<<move;
	};
	const auto solution	= solve(state);
	if(solution==std::nullopt)
		std::println("no solution found");
	else
	{
		for(const auto& move : solution.value())
			board.move(move);
		std::print("solution:\n{}\n", board.pretty_print());
	}
}
