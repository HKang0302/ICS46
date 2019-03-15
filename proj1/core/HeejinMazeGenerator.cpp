#include <ics46/factory/DynamicFactory.hpp>
#include "HeejinMazeGenerator.hpp"

#include <random>
#include <iostream>


ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, HeejinMazeGenerator, "Heejin's Algorithm (Required)");


std::random_device device;
std::default_random_engine engine{device()};
std::uniform_int_distribution<int> distribution{0,3}; // Let 0 be up, 1 be down, 2 be left, 3 be right

void HeejinMazeGenerator::generateMaze(Maze& maze)
{
	maze.addAllWalls();	// add all walls before creating a maze

	std::vector<std::vector<bool>> visited(maze.getWidth(), std::vector<bool>(maze.getHeight())); // declaring the size of the matrix
	// mark the current cell as "visited"
	visited[0][0] = true;

	// while the current cell has any adjacent cells that have not yet been visited
	
	while(!visitedAllCells(maze, visited))
	{
		while(!visitedAllAdjacentCells(maze, x, y, visited))
		{
			removeRandomWalls(maze, x, y, visited, path);
			visited[x][y] = true;
		}

		if(visitedAllAdjacentCells(maze, x, y, visited))
		{
			trackPath(x, y, path);
		}
	}	
}

void HeejinMazeGenerator::removeRandomWalls(Maze& maze, int& x, int& y, std::vector<std::vector<bool>> visited, std::vector<Direction>& path)
{
	int move = distribution(engine);
	int oldX = x;
	int oldY = y;

	dir = getDirection(x, y, move);
	if(x<0 || y<0 || x>=maze.getWidth() || y>=maze.getHeight())
	{
		x = oldX;
		y = oldY;
		return removeRandomWalls(maze, x, y, visited, path);
	}

	else
	{
		if(!maze.wallExists(oldX, oldY, dir) || (maze.wallExists(oldX, oldY, dir) && visited[x][y]))
		{
			x = oldX;
			y = oldY;
			return removeRandomWalls(maze, x, y, visited, path);
		}
			
		else
		{
			maze.removeWall(oldX, oldY, dir);
			path.push_back(dir);
		}
	}

}

bool HeejinMazeGenerator::visitedAllAdjacentCells(Maze& maze, int x, int y, std::vector<std::vector<bool>> visited)
{
	if(x==0)
	{
		if(y==0)
		{
			if(visited[x+1][y] && visited[x][y+1])
				return true;
		}
		else if(y==maze.getHeight()-1)
		{
			if(visited[x+1][y] && visited[x][y-1])
				return true;
		}
		else
		{
			if(visited[x+1][y] && visited[x][y-1] && visited[x][y+1])
				return true;
		}
	}
	else if (y==0)
	{
		if(x==maze.getWidth()-1)
		{
			if(visited[x-1][y] && visited[x][y+1])
				return true;
		}
		else
		{
			if(visited[x+1][y] && visited[x-1][y] && visited[x][y+1])
				return true;
		}
	}

	else if(x==maze.getWidth()-1)
	{
		if(y==maze.getHeight()-1)
		{
			if(visited[x-1][y] && visited[x][y-1])
				return true;
		}
		else
		{
			if(visited[x-1][y] && visited[x][y+1] && visited[x][y-1])
				return true;
		}
	}

	else if(y==maze.getHeight()-1)
	{
		if(visited[x-1][y] && visited[x+1][y] && visited[x][y-1])
			return true;
	}

	else
	{
		if(visited[x+1][y] && visited[x-1][y] && visited[x][y+1] && visited[x][y-1])
		{
			return true;
		}	
	}

	return false;
}

bool HeejinMazeGenerator::visitedAllCells(Maze& maze, std::vector<std::vector<bool>> visited)
{
	for(int i=0; i<maze.getWidth(); i++)
	{
		for(int j=0; j<maze.getHeight(); j++)
		{
			if(!visited[i][j])
				return false;
		}
	}
	
	return true;
}

Direction HeejinMazeGenerator::getDirection(int& x, int& y, int move)
{
	if(move==0)
	{
		y--;
		return Direction::up;
	}	
	else if(move==1)
	{
		y++;
		return Direction::down;
	}
	else if(move==2)
	{
		x--;
		return Direction::left;
	}
	else
	{
		x++;
		return Direction::right;
	}
}

void HeejinMazeGenerator::trackPath(int& x, int& y, std::vector<Direction>& path)
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