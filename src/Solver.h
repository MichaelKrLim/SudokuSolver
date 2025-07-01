#ifndef	SOLVER_H
#define	SOLVER_H

#include "Move.h"
#include "State.h"

#include <algorithm>
#include <optional>
#include <vector>

namespace sudoku
{
	inline std::optional<std::vector<Move>>	solve(State& state)
	{
		std::vector<Move> solution;
		const auto helper =	[&](this auto&&	rec)
		{
			if(state.is_solved())
				return true;

			for(const Move&	move : state.lazy_move_generation())
			{
				state.move(move);
				if(rec())
				{
					solution.push_back(move);
					return true;
				}
				state.unmove();
			}
			return false;
		};
		
		if(!helper())
			return std::nullopt;

		std::ranges::reverse(solution);
		return solution;
	}
};

#endif // SOLVER_H_INCLUDED
