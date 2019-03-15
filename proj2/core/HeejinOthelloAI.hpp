#ifndef HEEJINOTHELLOAI_HPP
#define HEEJINOTHELLOAI_HPP

#include "OthelloAI.hpp"
#include "OthelloGameState.hpp"
#include "OthelloBoard.hpp"
#include <vector>

namespace heejink3
{
	class HeejinOthelloAI : public OthelloAI
	{
	public:
		// choose the best move based on the evaluation value
		virtual std::pair<int, int> chooseMove(const OthelloGameState& state);
		// return the evaluatation value of the state
		int search(OthelloGameState& s, int depth, OthelloCell& mycolor);
		// evaluate the current state (when only one or less wall is taken)
		int evaluation(OthelloGameState& state, OthelloCell myColor);
		
		// return the vector of all the valid moves
		std::vector<std::pair<int,int>> allValidMoves(const OthelloGameState& s);
	
	};

}


#endif