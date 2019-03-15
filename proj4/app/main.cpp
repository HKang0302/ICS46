// main.cpp
//
// ICS 46 Winter 2019
// Project #4: Rock and Roll Stops the Traffic
//
// This is the program's main() function, which is the entry point for your
// console user interface.
#include "RoadMapReader.hpp"
#include "RoadMapWriter.hpp"
#include "TripReader.hpp"

#include <iostream>
#include <map>
#include <functional>
#include <vector>
#include <string>
#include <iomanip>

std::function<double(const RoadSegment&)> distance = [](RoadSegment rs) {return rs.miles;};
std::function<double(const RoadSegment&)> speed = [](RoadSegment rs) {return rs.miles / rs.milesPerHour;};


int main()
{
	struct Via
	{
		int vertex;
		std::string location;
		RoadSegment edge;
	};

	// get input
	InputReader in = InputReader(std::cin);
	RoadMapReader rm;
	RoadMap rmap = rm.readRoadMap(in); // locations && road segments
	TripReader tr;
	std::vector<Trip> trips = tr.readTrips(in); // info of all edges


	std::map<int,int> shortestPaths; // start to the end
	for(auto i=trips.begin(); i!=trips.end(); i++)
	{
		std::vector<Via> path;
		int start = i->startVertex;
		int end = i->endVertex;

		if(i->metric == TripMetric::Distance)
		{
			std::cout << "Shortest distance from "<< rmap.vertexInfo(start) << " to " << rmap.vertexInfo(end) <<": " << std::endl;
			shortestPaths = rmap.findShortestPaths(start, distance);
		}
		else
		{
			std::cout << "Shortest driving time from "<< rmap.vertexInfo(start) << " to " << rmap.vertexInfo(end) <<": " << std::endl;
			shortestPaths = rmap.findShortestPaths(start, speed);
		}

		std::cout << "\tBegin at " << rmap.vertexInfo(start) << std::endl;

		int next = shortestPaths.at(end);
		path.push_back(Via{end, rmap.vertexInfo(end), rmap.edgeInfo(next, end)});

		while(next != start)
		{
			int temp = next;
			next = shortestPaths.at(temp);
			path.push_back(Via{temp, rmap.vertexInfo(temp), rmap.edgeInfo(next, temp)});
		}

		if(i->metric == TripMetric::Distance)
		{
			double totalMiles = 0;
			while(!path.empty())
			{
				Via current = path.back();
				path.pop_back();
				std::cout << "\tContinue to " << current.location << " (" << current.edge.miles <<" miles)" << std::endl;;
				totalMiles += current.edge.miles;
			}
			std::cout << "Total distance: " << totalMiles << " miles" << std::endl;
		}
		else
		{
			double totalTime = 0;
			while(!path.empty())
			{
				Via current = path.back();
				path.pop_back();
				double currentTime = current.edge.miles / current.edge.milesPerHour * 3600;
				int minutes = currentTime/60;
				double seconds = currentTime - (minutes*60);
				totalTime += currentTime;

				std::cout << "\tContinue to " << current.location << " (" << current.edge.miles << " miles & "
					<< current.edge.milesPerHour << " mph = " << minutes << " minutes " << std::fixed << std::setprecision(2) << seconds << " seconds)" << std::endl;
			}

			int totalMinutes = totalTime/60;
			double totalSeconds = totalTime - (totalMinutes*60);
			std::cout << "Total time: " << totalMinutes << " minutes " << std::fixed << std::setprecision(2) << totalSeconds << " seconds" << std::endl;
		}

		std::cout << std::endl;

	}

    return 0;
}

