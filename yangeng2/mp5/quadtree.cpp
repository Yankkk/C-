// **************************************************************
// *		   
// *  quadtree.cpp
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#include <algorithm>
#include <iostream>
#include <queue>
#include <utility>
#include "quadtree.h"
using std::cout;
using std::endl;
/**
* this function is a no parameters constructor
*/

Quadtree::Quadtree()
{
	root = NULL;
	size = 0;
}


/**
* this function is a constructor takes two parameters, a source image to
* base this Quadtree and a int to be width and height of image to be represented
*/

Quadtree::Quadtree(const PNG & source, int resolution)
{
	root = NULL;
	size = resolution;
	buildTree(source, resolution);
   
}

/**
* this function is a copy constructor for Quadtree
*/

Quadtree::Quadtree(Quadtree const & other)
{
		
	copy(other);

}

/**
* this function is a assignment operator
*/

const Quadtree & Quadtree::operator=(const Quadtree & rhs)
{
	if(this != &rhs){
	    clear(root);
	    copy(rhs);
	}
	return * this;
}

/**
* this is a copy helper function for Quadtree
*/
void Quadtree::copy(const Quadtree & other)
{
	root = NULL;
	size = other.size;
	PNG image = other.decompress();

	buildTree(image, other.size);	
}

/**
* this is a copy helper function for QuadtreeNode
*/


Quadtree::QuadtreeNode * Quadtree::copyNode(const QuadtreeNode * current)
{
	if(current == NULL)
		return NULL;
	QuadtreeNode * node = new QuadtreeNode(current->element);
	node->nwChild = copyNode(current->nwChild);
	node->neChild = copyNode(current->neChild);
	node->swChild = copyNode(current->swChild);
	node->seChild = copyNode(current->seChild);
	return node;

}


/**
* this function is a destructor for Quadtree
*/
Quadtree::~Quadtree()
{
	clear(root);
}

/**
* this function is a helper function for destructor
*/

void Quadtree::clear(QuadtreeNode *  current)
{
	if(current != NULL) {
		clear(current->nwChild);
		clear(current->neChild);
		clear(current->swChild);
		clear(current->seChild);
	
		delete current;
		current = NULL;
        }
}	

/**
* this function is build a Quadtree of top left resolution*resolution
* image
*/
void Quadtree::buildTree(PNG const & source, int resolution)
{
	clear(root);
	root = new QuadtreeNode();
	size = resolution;
	buildBranch(source, 0, 0, resolution, root);

}
/**
* this is a helper function for buildTree
*/
void Quadtree::buildBranch(PNG const & source, int x, int y, int resolution, QuadtreeNode * current)
{
	if(resolution == 1){
		current->element.red = source(x, y)->red;
		current->element.green = source(x, y)->green;
		current->element.blue = source(x, y)->blue;
		//cout << "(" << x << ", " << y << ")" << endl;
	}
	else{
		current->nwChild = new QuadtreeNode();
		current->neChild = new QuadtreeNode();
		current->swChild = new QuadtreeNode();
		current->seChild = new QuadtreeNode();

		buildBranch(source, x, y, resolution/2, current->nwChild);
		buildBranch(source, x + resolution/2, y, resolution/2, current->neChild);
		buildBranch(source, x, y + resolution/2, resolution/2, current->swChild);
		buildBranch(source, x + resolution/2, y + resolution/2, resolution/2, current->seChild);

		//if(!leaf(current)){
		current->element.red = (current->nwChild->element.red + current->neChild->element.red + current->swChild->element.red + current->seChild->element.red)/4;
		current->element.green = (current->nwChild->element.green + current->neChild->element.green + current->swChild->element.green + current->seChild->element.green)/4;
		current->element.blue = (current->nwChild->element.blue + current->neChild->element.blue + current->swChild->element.blue + current->seChild->element.blue)/4;
		//}

	}


}

/**
void Quadtree::buildTree(PNG const & source, int resolution)
{
	
	clear(root);
	
	std::queue<QuadtreeNode *> longQueue;
	//queue<QuadtreeNode *> neQueue;
	//queue<QuadtreeNode *> swQueue;
	//queue<QuadtreeNode *> seQueue;

	for(int i = 0; i < resolution; i=i+2){
	    for(int j = 0; j < resolution; j=j+2){
		QuadtreeNode * nwTemp = new QuadtreeNode(*source(i, j));
		QuadtreeNode * neTemp = new QuadtreeNode(*source(i+1, j));
		QuadtreeNode * swTemp = new QuadtreeNode(*source(i, j+1));
		QuadtreeNode * seTemp = new QuadtreeNode(*source(i+1, j+1));
		longQueue.push(nwTemp);
		longQueue.push(neTemp);
		longQueue.push(swTemp);
		longQueue.push(seTemp);
	    }
	}

	while(longQueue.size() > 1){
		QuadtreeNode * internal = new QuadtreeNode();
		internal->nwChild = longQueue.front();
		longQueue.pop();
		internal->neChild = longQueue.front();
		longQueue.pop();
		internal->swChild = longQueue.front();
		longQueue.pop();
		internal->seChild = longQueue.front();
		longQueue.pop();

		internal->element.red = (internal->nwChild->element.red + internal->neChild->element.red + internal->swChild->element.red + internal->seChild->element.red)/4;
		internal->element.green = (internal->nwChild->element.green + internal->neChild->element.green + internal->swChild->element.green + internal->seChild->element.green)/4;
		internal->element.blue = (internal->nwChild->element.blue + internal->neChild->element.blue + internal->swChild->element.blue + internal->seChild->element.blue)/4;
		longQueue.push(internal);
	}

	root = longQueue.front();
	longQueue.pop();
	size = resolution;


}

*/


/**
* this function will gets the RGBAPixel of (x,y) in the bitmap image
*/

RGBAPixel Quadtree::getPixel(int x, int y) const
{
	
	if(x >= size || y >= size || x<0 || y<0)
		return RGBAPixel();
	else if(root == NULL)
		return RGBAPixel();
	else{
		return getPixel(size, x, y, root);
	}

}

/**
* this is helper function for getPixel
*/
RGBAPixel Quadtree::getPixel(int resolution, int x, int y, QuadtreeNode * current) const
{
	if(resolution == 1)
		return current->element;

	else{
		if(x < resolution/2 && y < resolution/2){
			return getPixel(resolution/2, x, y, current->nwChild);
		}
		else if(x < resolution/2 && y >= resolution/2){
			return getPixel(resolution/2, x, y-resolution/2, current-> swChild);
		}
		else if(x >= resolution/2 && y < resolution/2){
			return getPixel(resolution/2, x-resolution/2, y, current->neChild);
		}
		else if(x >= resolution/2 && y >= resolution/2){
			return getPixel(resolution/2, x-resolution/2, y-resolution/2, current->seChild);	
		}
		else{
			return current->element;
		}


	}


}

/**
* this function check whether a QuadtreeNode is a leaf node
*/
bool Quadtree::leaf(QuadtreeNode * current) const
{
	bool nw, ne, sw, se;
	nw = current->nwChild == NULL;
	ne = current->neChild == NULL;
	sw = current->swChild == NULL;
	se = current->seChild == NULL;
	
	return nw && ne && sw && se;
}


/**
* this function transfer the Quadtree to PNG
*/

PNG Quadtree::decompress() const
{
	if(root == NULL)
		return PNG();

	else{
		PNG image(size, size);
		/**
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
				*image(i, j) = getPixel(i, j);
			}
		}
		*/
		decompress(0, 0, size, root, image);
		return image;
	}

}

/**
* this is a helper function for decompress
*/

void Quadtree::decompress(int x, int y, int resolution, QuadtreeNode * current, PNG & image) const
{
	if(resolution == 1){
		*image(x, y) = current->element;
	}
	
	else{
		decompress(x, y, resolution/2, current->nwChild, image);
		decompress(x + resolution/2, y, resolution/2, current->neChild, image);
		decompress(x, y + resolution/2, resolution/2, current->swChild, image);
		decompress(x + resolution/2, y + resolution/2, resolution/2, current->seChild, image);
	
	}

}

/**
* this function return the Quadtree clockwise by 90 degrees
*/
void Quadtree::clockwiseRotate()
{
	return;
}


/**
* this function compresses the image this Quadtree represents
*/
void Quadtree::prune(int tolerance)
{
	return;
}

/**
* this function returns a count of the toal number of leaces the Quadtree would
* have if it were pruned as in the prune function
*/
int Quadtree::pruneSize(int tolerance) const
{
	return 0;

}

/**
* This function calculates and returns the minmum tolerance necessary to 
* guarantee that upon pruning the tree, no more than numLeaves leaves in the
* Quadtree
*/
int Quadtree::idealPrune(int numLeaves) const
{
	return 0;
}
