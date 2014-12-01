#ifndef MAZE_H
#define MAZE_H

#include <vector> 
#include "dsets.h"
#include "png.h"

using namespace std;

class SquareMaze
{
	public:
	
	
		void makeMaze(int width, int height); // make a new SquareMaze
		
		bool canTravel(int x, int y, int dir) const; // determine whether it is possible to travel
		
		void setWall(int x, int y, int dir, bool exists); // set wall
		
		vector<int> solveMaze(); // solve the SquareMaze
		
		PNG * drawMaze()const; // draw the maze without solution
		
		PNG * drawMazeWithSolution(); // draw the maze and show the solution
		
		
		
	private:
		class cell
		{
			public :
				bool right;
				bool down;
				cell();
			
		};
		int Width;
		int Height;
		vector<cell> maze;
		
	



};

#endif
