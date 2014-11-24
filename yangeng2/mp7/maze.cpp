
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maze.h"



/**
* this function makes a new SquareMaze of the given height and width
*/
void SquareMaze::makeMaze(int width, int height)
{
	if(width < 2 || height < 2)
		return;
		
	Width = width;
	Height = height;
	
	if(!maze.empty()){
		maze.clear();
		
	}
	maze.resize(Width * Height);
	for(int i = 0; i < Width * Height; i++){
		cell c;
		c.right = true;
		c.down = true;
		maze.push_back(c);
	}
	
	DisjointSets set;
	set.addelements(Width * Height);
	
	srand (time(NULL));
	int wallRemoved = 0;
	while(wallRemoved < Height * Width -1){
		int ranIndex = rand() % (Width * Height);
		int root1 = set.find(ranIndex);
		int root2;
		if(ranIndex != Width * Height - 1){
			if(ranIndex >= (Height-1) * Width && ranIndex < Height * Width){
				root2 = set.find(ranIndex + 1);
				if(root1 != root2){
					set.setunion(root1, root2);
					maze[ranIndex].right = false;
					wallRemoved ++;
				}
			}
			else if((ranIndex + 1) % Width == 0){
				root2 = set.find(ranIndex + Width);
				if(root1 != root2){
					set.setunion(root1,root2);
					maze[ranIndex].down = false;
					wallRemoved ++;
				}
			}
			else{
				if(rand() % 2 == 0){
					root2 = set.find(ranIndex + 1);
					if(root1 != root2){
						set.setunion(root1, root2);
						maze[ranIndex].right = false;
						wallRemoved ++;
					}
				
				}
				else{
					root2 = set.find(ranIndex + Width);
					if(root1 != root2){
						set.setunion(root1, root2);
						maze[ranIndex].down = false;
						wallRemoved++;
					}
				
				}
			}
		
		}
		
	}

}

/**
* this function determine whether it is possible to travel in the given direnction
* from the square at coordinates(x, y)
*/
bool SquareMaze::canTravel(int x, int y, int dir) const
{
	if(x < 0 || y < 0 || x >= Width || y >= Height)
		return false;
	bool result = false;
	int index = y * Width + x;
	
	if(dir == 0 && x + 1 < Width){
		if(!maze[index].right){
			result = true;
		}
	}
	else if(dir == 1 && y + 1 < Height){
		if(!maze[index].down){
			result = true;
		}
	
	}
	else if(dir == 2 && x-1 >= 0){
		if(!maze[index-1].right){
			result = true;
		}
	}
	else if(dir == 3 && y-1 >= 0){
		if(!maze[index-Width].down){
			result = true;
		}
	}
	return result;
}

/**
* this function sets whether or not the specified wall exists
*/
void SquareMaze::setWall(int x, int y, int dir, bool exists)
{
	if(x < 0 || y < 0 || x >= Width || y >= Height)
		return;
	int index = y * Width + x;
	if(dir == 0){
		maze[index].right = exists;
	}
	else if(dir == 1){
		maze[index].down = exists;
	}

}

/**
* this function solves the SquareMaze 
*/
vector<int> SquareMaze::solveMaze()
{
	vector< vector<int> > result;
	
	distance(0, 0, result);
	
	size_t max = result[0].size();
	int index = 0;
	for(int i = 0; i < Width; i++){
		if(result[i].size() > max){
			max = result[i].size();
			index = i;
		}
	
	} 
	
	return result[index];

}

/**
* this is the helper function for solveMaze
*/
void SquareMaze::distance(int x, int y, vector< vector<int> > collection)
{	

	vector<int> result;
	if(x < 0 || y < 0 || x >= Width || y >= Height)
		return;
		 
	bool stop = (!canTravel(x, y, 0)) && (!canTravel(x, y, 1)) && (!canTravel(x, y, 2))
					&& (!canTravel(x, y, 3));
	if(stop){
		if(y == Height -1){
			collection[x] = result;
			return;
		}
	}
	else{
		if(canTravel(x, y, 0)){
			result.push_back(0);
			distance(x+1, y, collection);
			result.pop_back();
		}
		if(canTravel(x, y, 1)){
			result.push_back(1);
			distance(x, y+1, collection);
			result.pop_back();
		}
		if(canTravel(x, y, 2)){
			result.push_back(2);
			distance(x-1, y, collection);
			result.pop_back();
		}
		if(canTravel(x, y, 3)){
			result.push_back(3);
			distance(x, y-1, collection);
			result.pop_back();
		}
		else{
			return;
		}
	}
}


/**
* this function draws ths maze without the solution
*/
PNG * SquareMaze::drawMaze()const
{

	return new PNG();
}

/**
* this function calls drawMaze, then solveMaze
* it modifies the PNG from drawMaze to show the solution vector and the exit
*/
PNG * SquareMaze::drawMazeWithSolution()
{

	return new PNG();
}
