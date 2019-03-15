#ifndef HEEJINMAZESOLVER_HPP
#define HEEJINMAZESOLVER_HPP

#include "MazeSolution.hpp"
#include "MazeSolver.hpp"
#include "Maze.hpp"
// #include "HeejinMazeGenerator.hpp"

#include <vector>

class HeejinMazeSolver : public MazeSolver
{
public:
	virtual void solveMaze(const Maze& maze, MazeSolution& mazeSolution);
	void solver(const Maze& maze, MazeSolution& mazeSolution, std::vector<std::vector<bool>>& visited, int& x, int& y, int& move, std::vector<Direction>& path);
	bool noPossibleWay(const Maze& maze, MazeSolution& mazeSolution, int x, int y, std::vector<std::vector<bool>> visited);
	Direction getDirection(const int move, int& x, int& y);
	void trackPath(int& x, int& y, std::vector<Direction>& path);

private:
	std::vector<Direction> path;
	int x = 0;
	int y = 0;
	int move = 0;
};

#endif