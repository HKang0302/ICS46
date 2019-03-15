#include <ics46/factory/DynamicFactory.hpp>
#include "HeejinMazeSolver.hpp"

ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, HeejinMazeSolver, "Heejin's solution (Required)");

// std::random_device device;
// std::default_random_engine engine{device()};
// std::uniform_int_distribution<int> distribution{0,3};

void HeejinMazeSolver::solveMaze(const Maze& maze, MazeSolution& mazeSolution)
{
	mazeSolution.restart();
	std::vector<std::vector<bool>> visited(maze.getWidth(), std::vector<bool>(maze.getHeight()));
	visited[0][0] = true;

	solver(maze, mazeSolution, visited, x, y, move, path);
	

}

void HeejinMazeSolver::solver(const Maze& maze, MazeSolution& mazeSolution, std::vector<std::vector<bool>>& visited, int& x, int& y, int& move, std::vector<Direction>& path)
{
	int oldX = x;
	int oldY = y;

	if(mazeSolution.isComplete())
		return;

	// if there's a possible way
	if(!noPossibleWay(maze, mazeSolution, x, y, visited))
	{
		// go down from the current cell
		Direction dir = getDirection(move, x, y);
		// if there's no wall existing
		if(!maze.wallExists(oldX, oldY, dir))
		{
			// check if it's not visited
			if(!visited[x][y])
			{
				mazeSolution.extend(dir);
				path.push_back(dir);
				visited[x][y]=true;
				move = 0;
				return solver(maze, mazeSolution, visited, x, y, move, path);	
			}
		}

		x = oldX;
		y = oldY;
		move++;
	}

	else
	{
		mazeSolution.backUp();
		trackPath(x, y, path);
	}

	return solver(maze, mazeSolution, visited, x, y, move, path);
	
}

//
bool HeejinMazeSolver::noPossibleWay(const Maze& maze, MazeSolution& mazeSolution, int x, int y, std::vector<std::vector<bool>> visited)
{
	// int walls = 0;
	int oldX = x;
	int oldY = y;

	// VISITED ALL THE OPENED CELLS
	for(int i=0; i<4;i++)
	{
		Direction dir = getDirection(i, x, y);

		// check if there's a wall in that direction
		// if there is, check other direction
		// if not, check if the cell is already visited
		if(!maze.wallExists(oldX, oldY, dir))
		{
			if(!visited[x][y])
			{
				x=oldX;
				y=oldY;
				return false;
			}
		}

		x=oldX;
		y=oldY;
	}


	return true;
}

Direction HeejinMazeSolver::getDirection(const int move, int& x, int& y)
{
	if(move==0)
	{
		y++;
		return Direction::down;
	}
	else if(move==1)
	{
		x++;
		return Direction::right;
	}
	else if(move==2)
	{
		x--;
		return Direction::left;
	}
	else
	{
		y--;
		return Direction::up;
	}
}

void HeejinMazeSolver::trackPath(int& x, int& y, std::vector<Direction>& path)
{
	Direction prevPath = path.back();
	path.pop_back();

	if(prevPath == Direction::up)
	{
		y++;
	}

	else if(prevPath == Direction::down)
	{
		y--;
	}

	else if(prevPath == Direction::left)
	{
		x++;
	}

	else
	{
		x--;
	}
}