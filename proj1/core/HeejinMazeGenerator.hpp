#ifndef HEEJINMAZEGENERATOR_HPP
#define HEEJINMAZEGENERATOR_HPP

#include "MazeGenerator.hpp"
#include "Maze.hpp"
#include "Direction.hpp"

#include <vector>

class HeejinMazeGenerator : public MazeGenerator
{
public:
	
	// HeejinMazeGenerator(); // default constructor

	virtual void generateMaze(Maze& Maze);

	// connect all the cells to create a maze
	// void connectCells(Maze& maze, int x, int y, std::vector<std::vector<bool>>& visited);

	// find the possible path to another cell
	void removeRandomWalls(Maze& maze, int& x, int& y, std::vector<std::vector<bool>> visited, std::vector<Direction>& path);

	// void breakWall(Maze& maze, int x, int y, std::vector<std::vector<bool>>& visited);

	// bool possibleCell(Maze& maze, int x, int y, int move);

	// returns true if all the adjacent cells aer visited
	bool visitedAllAdjacentCells(Maze& maze, int x, int y, std::vector<std::vector<bool>> visited);

	// returns true if all the cells are visited
	bool visitedAllCells(Maze& maze, std::vector<std::vector<bool>> visited);

	Direction getDirection(int& x, int& y, int move);

	// void newXY(Maze& maze, int& x, int& y, Direction& dir, int move);

	// track the previous path
	void trackPath(int& x, int& y, std::vector<Direction>& path);



private:
	std::vector<Direction> path;
	Direction dir = Direction::right;
	int x = 0;
	int y = 0;
};

#endif