
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "maze.h"
#include <stack>
#include <algorithm>
#include <map>

/**
* This is the constructor for cell class
*/
SquareMaze::cell::cell()
{
	right = true;
	down = true;
}

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
		
		maze.push_back(c);
	}
	
	DisjointSets set;
	set.addelements(Width * Height);
	
	srand (time(NULL));
	int wallRemoved = 0;
	int ranIndex = 0;
	while(wallRemoved != Height * Width -1){
	
		int root1 = set.find(ranIndex);
		int root2;
		//std::cout << ranIndex <<std::endl;
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
		ranIndex = rand() % (Width * Height);
			//std::cout << ranIndex <<std::endl;
		
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
	vector<int> temp;
	stack<int> save;
	/**
	bool processed[Width][Height];
	for(int i = 0; i < Width; i ++){
		for(int j = 0; j < Height; j++){
			processed[i][j] = false;
		}
	}
	*/
	vector<bool> processed;
	processed.resize(Height*Width);
	for(int i = 0; i < Height*Width; i++)
		processed[i] = false;
		
	vector<pair<int, int>> track;
	track.resize(Width * Height);
	int x = 0;
	int y = 0;
	
	save.push(0);
	processed[0] = true;
	track[0] = make_pair(-1,1);
	
	while(!save.empty()){
		int value = save.top();
		x = value % Width;
		y = value / Width;
		int pos = x + y*Width;
		save.pop();
		if(canTravel(x, y, 0) && !processed[pos+1]){
			save.push(x+1+y*Width);
			processed[pos+1] = true;
			track[x+1+y*Width] = make_pair(x+y*Width,track[x+y*Width].second + 1);
		}
		if(canTravel(x, y, 1) && !processed[pos+Width]){
			save.push(x+(y+1)*Width);
			processed[pos+Width] = true;
			track[x+(y+1)*Width] = make_pair(x+y*Width,track[x+y*Width].second+1);
		}
		if(canTravel(x, y, 2) && !processed[pos-1]){
			save.push(x-1+y*Width);
			processed[pos-1] = true;
			track[x-1+y*Width] = make_pair(x+y*Width, track[x+y*Width].second+1);
		}
		if(canTravel(x, y ,3) && !processed[pos-Width]){
			save.push(x+(y-1)*Width);
			processed[pos-Width] = true;
			track[x+(y-1)*Width] = make_pair(x+y*Width, track[x+y*Width].second+1);
		
		}
	
	
	}
	
	int max = 0;
	int position = 0;
	for(int i = 0; i < Width; i++){
		if(max < track[(Height-1)*Width + i].second){
			max = track[(Height-1)*Width + i].second;
			position = (Height-1)*Width + i;
		}
	
	}
	
	while(position != -1){
		temp.push_back(position);
		position = track[position].first;
	
	
	}
	
	vector<int> result;
	reverse(temp.begin(), temp.end());
	for(size_t i = 0; i < temp.size(); i++){
		if(temp[i]-temp[i+1] == 1)
			result.push_back(2);
		else if(temp[i] - temp[i+1] == -1)
			result.push_back(0);
		else if(temp[i] - temp[i+1] == Width)
			result.push_back(3);
		else if(temp[i] - temp[i+1] == -Width)
			result.push_back(1);
	
	}
	return result;

}




/**
* this function draws ths maze without the solution
*/
PNG * SquareMaze::drawMaze()const
{
	PNG * image = new PNG();
	image->resize(Width*10+1, Height*10+1);
	for(int i = 10; i < Width*10+1; i++){
		(*image)(i,0)->red = 0;
		(*image)(i,0)->green = 0;
		(*image)(i,0)->blue = 0;
	}
	for(int j = 0; j < Height*10+1; j++){
		(*image)(0,j)->red = 0;
		(*image)(0,j)->green = 0;
		(*image)(0,j)->blue = 0;
	
	}
	
	for(int i = 0; i < Width; i++){
		for(int j = 0; j < Height; j++){
			if(maze[j*Width+i].down){
				for(int k = 0; k <= 10; k++){
					(*image)(i*10+k, (j+1)*10)->red = 0;
					(*image)(i*10+k, (j+1)*10)->green = 0;
					(*image)(i*10+k, (j+1)*10)->blue = 0;
				}
			
			}
			if(maze[j*Width+i].right){
				for(int k = 0; k <= 10; k++){
					(*image)((i+1)*10, j*10+k)->red = 0;
					(*image)((i+1)*10, j*10+k)->green = 0;
					(*image)((i+1)*10, j*10+k)->blue = 0;
				}
			
			}
		
		}
	}
	return image;
}

/**
* this function calls drawMaze, then solveMaze
* it modifies the PNG from drawMaze to show the solution vector and the exit
*/
PNG * SquareMaze::drawMazeWithSolution()
{
	PNG * image;
	image = drawMaze();
	vector<int> solution = solveMaze();
	int x = 5;
	int y = 5;
	for(size_t i = 0; i < solution.size(); i++){
		if(solution[i] == 0){
			for(int k = 0; k <= 10; k++){
				(*image)(x+k, y)->red = 255;
				(*image)(x+k, y)->green = 0;
				(*image)(x+k, y)->blue = 0;
			}
			x = x+10;
		}
		else if(solution[i] == 1){
			for(int k = 0; k <= 10; k++){
				(*image)(x, y+k)->red = 255;
				(*image)(x, y+k)->green = 0;
				(*image)(x, y+k)->blue = 0;
			}
			y = y+10;
		
		}
		else if(solution[i] == 2){
			for(int k = 0; k <= 10; k++){
				(*image)(x-k, y)->red = 255;
				(*image)(x-k, y)->green = 0;
				(*image)(x-k, y)->blue = 0;
			}
			x = x-10;
		
		}
		else if(solution[i]==3){
			for(int k = 0; k <= 10; k++){
				(*image)(x, y-k)->red = 255;
				(*image)(x, y-k)->green = 0;
				(*image)(x, y-k)->blue = 0;
			}
			y=y-10;
		
		}
	
	}
	for(int i = -4; i <= 4 ; i++){
		(*image)(x+i, y+5)->red = 255;
		(*image)(x+i, y+5)->green = 255;
		(*image)(x+i, y+5)->blue = 255;
	
	}
	return image;
}
