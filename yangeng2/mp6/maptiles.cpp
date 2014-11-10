/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */
	 			
#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas * mapTiles(SourceImage const & theSource, vector<TileImage> const & theTiles)
{
    /**
     * @todo Implement this function!
     */
	if(theTiles.size() == 0 || theSource.getRows() == 0 || theSource.getColumns() == 0)
    	return NULL;
    	
    	
	MosaicCanvas * image = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    
	vector< Point<3> > theNewTiles;
	for(size_t i = 0; i < theTiles.size(); i++){
    	RGBAPixel average = theTiles[i].getAverageColor();
    	Point<3> p(average.red, average.green, average.blue);
    	theNewTiles.push_back(p);
    
	}
    
	KDTree<3> imageTree(theNewTiles);
    
	std::map<Point<3>, TileImage> tile;
	for(size_t i = 0; i < theNewTiles.size(); i++){
   		tile.insert(std::pair<Point<3>, TileImage>(theNewTiles[i], theTiles[i]));
	}
	
	for(int i = 0; i < theSource.getRows(); i++){
		for(int j = 0; j < theSource.getColumns(); j++){
			RGBAPixel average = theSource.getRegionColor(i, j);
			
			Point<3> temp(average.red, average.green, average.blue); 
			Point<3> best = imageTree.findNearestNeighbor(temp);
			
			image->setTile(i, j, tile.find(best)->second);
		
		}
	}
    
    
	return image;
}
