#include "HeejinOthelloAI.hpp"
#include "OthelloCell.hpp"
#include <ics46/factory/DynamicFactory.hpp>

#include <iostream>

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, heejink3::HeejinOthelloAI, "Heejin's class (Required)");

// use the recursive and search-tree based algorithm

std::pair<int, int> heejink3::HeejinOthelloAI::chooseMove(const OthelloGameState& state)
{
	// implementation of my AI goes here
	OthelloCell myColor;
	int bestValue = -9999;
	std::pair<int, int> finalMove;

	// get all the valid moves
	std::vector<std::pair<int, int>> moves = allValidMoves(state);

	// std::cout << "Black Score: " << state.blackScore() << std::endl;


	// check what color you are playing with
	if(state.isBlackTurn())
		myColor = OthelloCell::black;
	else
		myColor = OthelloCell::white;


	for(int i=0; i<moves.size(); i++)
	{
		std::unique_ptr<OthelloGameState> tempState = state.clone();
		std::pair<int, int> move = moves[i];

		// std::cout << "(" << move.first << " " << move.second << ") ";

		tempState->makeMove(move.first, move.second);

		// predict up to 5 states ahead, which the depth should be 4
		int value = search(*tempState, 3, myColor);

		if (myColor==OthelloCell::black)
			value += (tempState->blackScore()-tempState->whiteScore());
		else
			value += (tempState->whiteScore()-tempState->blackScore());

		// std::cout << "value: " << value << std::endl;

		if(bestValue<value)
		{
			bestValue = value;
			finalMove = std::make_pair(move.first,move.second);
		}

	}

	// std::cout << std::endl;

	return finalMove;
}

// find the best value for the move
int heejink3::HeejinOthelloAI::search(OthelloGameState& s, int depth, OthelloCell& myColor)
{
	if (depth == 0)
	{
		return evaluation(s,myColor);
	}

	else
	{
		OthelloCell currColor; // the color of the current turn
		if(s.isBlackTurn())
			currColor = OthelloCell::black;
		else
			currColor = OthelloCell::white;

		// all the valid moves in this state
		std::vector<std::pair<int, int>> tempMoves = allValidMoves(s);

		// if it's my turn to move
		if(currColor == myColor)
		{
			int max=-999;
			// for each valid move that I can make from this state
			for(int i=0; i<tempMoves.size(); i++)
			{
				// make that move on s yielding a state s'
				std::unique_ptr<OthelloGameState> newState = s.clone();
				std::pair<int, int> move = tempMoves[i];
				newState->makeMove(move.first, move.second);
				int value = search(*newState, depth-1, myColor);
				if(value>max)
					max=value;
				
			}
			// return maximum value
			return max;
		}

		// if it's opponent's turn
		else
		{
			int min=999;

			for(int i=0; i<tempMoves.size(); i++)
			{
				// make that move on s yielding a state s'
				std::unique_ptr<OthelloGameState> newState = s.clone();
				std::pair<int, int> move = tempMoves[i];
				newState->makeMove(move.first, move.second);
				int value = search(*newState, depth-1, myColor);
				if(value<min)
					min=value;
				
			}

			return min;

		}
	}

}

// evaluation beginning
// Take one of the walls as much as you can
int heejink3::HeejinOthelloAI::evaluation(OthelloGameState& state, OthelloCell myColor)
{
	OthelloCell oppColor;
	if(myColor==OthelloCell::black)
		oppColor = OthelloCell::white;
	else
		oppColor = OthelloCell::black;

	int value = 0;
	const OthelloBoard& b = state.board();

	for(int x=0; x<8; x++)
	{
		for(int y=0; y<8; y++)
		{
			// 120 point
			if((x==0 || x==7) && (y==0 || y==7))
			{
				if(b.cellAt(x,y) == myColor)
					value += 120;
				else if(b.cellAt(x,y) == oppColor)
					value -= 120;
			}

			// 20 point 
			else if(((x==0 || x==7) && (y==2 || y==5))
				|| ((x==2 || x==5) && (y==0 || y==7)))
			{
				if(b.cellAt(x,y) == myColor)
					value += 20;
				else if(b.cellAt(x,y) == oppColor)
					value -= 20;
			}

			// 5 point
			else if(((x==0||x==7)&&(y==3||y==4))|| ((x==3||x==4)&&(y==0||y==7)))
			{
				if(b.cellAt(x,y) == myColor)
					value += 5;
				else if(b.cellAt(x,y) == oppColor)
					value -= 5;
			}

			// 15 point
			else if((x==2 || x==5) && (y==2 || y==5))
			{
				if(b.cellAt(x,y) == myColor)
					value += 15;
				else if(b.cellAt(x,y) == oppColor)
					value -= 15;
			}

			// -5 point
			else if(((x==1||x==6)&&(y==2||y==3||y==4||y==5)) || ((x==2||x==3||x==4||x==5)&&(y==1||y==6)))
			{
				if(b.cellAt(x,y) == myColor)
					value -= 5;
				else if(b.cellAt(x,y) == oppColor)
					value += 5;
			}

			// -20 point
			else if(((x==0||x==7)&&(y==1||y==6)) || ((x==1||x==6)&&(y==0||y==7)))
			{
				if(b.cellAt(x,y) == myColor)
					value -= 20;
				else if(b.cellAt(x,y) == oppColor)
					value += 20;
			}

			// -40 point
			else if((x==1 || x==6) && (y==1 || y==6))
			{
				if(b.cellAt(x,y) == myColor)
					value -= 40;
				else if(b.cellAt(x,y) == oppColor)
					value += 40;
			}

			// 3 point
			else
			{
				if(b.cellAt(x,y) == myColor)
					value += 3;
				else if(b.cellAt(x,y) == oppColor)
					value -= 3;
			}
		}
	}
	
	// std::cout << value << std::endl;
	return value;
}




std::vector<std::pair<int,int>> heejink3::HeejinOthelloAI::allValidMoves(const OthelloGameState& s)
{
	const OthelloBoard& b = s.board();
	std::vector<std::pair<int,int>> moves;
	for(int i=0; i<b.width(); i++)
	{
		for(int j=0; j<b.height(); j++)
		{
			if(s.isValidMove(i,j))
			{
				std::pair<int,int> validMove = std::make_pair(i,j);
				moves.push_back(validMove);
			}
		}
	}
	return moves;
}