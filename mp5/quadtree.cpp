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
#include <math.h>
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
	/**
	root = NULL;
	size = other.size;
	PNG image = other.decompress();

	buildTree(image, other.size);	
	*/
	
	root = copyNode(other.root);
	size = other.size;
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

void Quadtree::clear(QuadtreeNode * & current)
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
		current->neChild = NULL;
		current->nwChild = NULL;
		current->seChild = NULL;
		current->swChild = NULL;
		current->element = *source(x, y);
		
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
	if(resolution == 1 || leaf(current))
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
		else {
			return getPixel(resolution/2, x-resolution/2, y-resolution/2, current->seChild);	
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
	
	else if(leaf(current)){
		for(int i= x; i < resolution + x; i ++){
			for(int j = y; j < resolution + y; j ++){
				*image(i, j) = current->element;
			}
		
		}
		
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
	clockwiseRotate(root);
	return;
}

/**
* this is a helper function for clockwiseRotate
*/


void Quadtree::clockwiseRotate(QuadtreeNode * current)
{
	if(leaf(current)){
		return;
	
	}
	
	else{
		QuadtreeNode * temp = current->nwChild;
		current->nwChild = current->swChild;
		current->swChild = current->seChild;
		current->seChild = current->neChild;
		current->neChild = temp;
		
		clockwiseRotate(current->nwChild);
		clockwiseRotate(current->swChild);
		clockwiseRotate(current->seChild);
		clockwiseRotate(current->neChild);
		
		
		
	
	}


}


/**
* this function compresses the image this Quadtree represents
*/
void Quadtree::prune(int tolerance)
{
	prune(tolerance, root);
	return;
}


/**
* this function is a helper function for prune
*/


void Quadtree::prune(int tolerance, QuadtreeNode * & current)
{
	if(current != NULL && !leaf(current)){
		
		bool tol = inTol(current, current->neChild, tolerance) && inTol(current, current->nwChild, tolerance) && inTol(current, current->swChild, tolerance) && inTol(current, current->seChild, tolerance);
		
		if(tol){
			clear(current->nwChild);
			clear(current->neChild);
			clear(current->swChild);
			clear(current->seChild);
			
		}
		
		else{
			prune(tolerance, current->neChild);
			prune(tolerance, current->nwChild);
			prune(tolerance, current->seChild);
			prune(tolerance, current->swChild);
		
		
		}
	}


}


/**
* this function shows whether the difference of color of two nodes is within the tolerance
*/


bool Quadtree::inTol(QuadtreeNode * current, QuadtreeNode * child, int tolerance) const
{
	if(child == NULL || current == NULL)
		return false;
		
	else{
	
		if(leaf(child)){
	
	
			int r = current->element.red - child->element.red;
			int g = current->element.green - child->element.green;
			int b = current->element.blue - child->element.blue;
	
			int tempTol = r * r + g * g + b * b;
			
	
			return tempTol <= tolerance;
			}
		
		
		else{
		
			return (inTol(current, child->neChild, tolerance) && inTol(current, child->seChild, tolerance)
				&& inTol(current, child->nwChild, tolerance) && inTol(current, child->swChild, tolerance));
		
			}
		}	
}
	



/**
* this function returns a count of the toal number of leaces the Quadtree would
* have if it were pruned as in the prune function
*/
int Quadtree::pruneSize(int tolerance) const
{
	if(root == NULL)
		return 0;
		
	int count = size * size - pruned(root, tolerance); 
	
	return count;
}

/**
* this function count the leaves need prune
*/
int Quadtree::pruned(QuadtreeNode * current, int tolerance) const
{
	if(current == NULL){
		return 0;
	}
	if(leaf(current))
		return 0;
		
	bool tol = inTol(current, current->neChild, tolerance) && inTol(current, current->nwChild, tolerance) && inTol(current, current->swChild, tolerance) && inTol(current, current->seChild, tolerance);
	if(tol){
		return leafCount(current)-1;
	}

	
	else{
		return pruned(current->neChild, tolerance) + pruned(current->nwChild, tolerance) + pruned(current->seChild, tolerance) + pruned(current->swChild, tolerance);
		}	
	
	

}

/**
* this function count the number of leaves in subtree of current
*/
int Quadtree::leafCount(QuadtreeNode * current) const
{
	if(current == NULL)
		return 0;
	if(leaf(current))
		return 1;
	else{
		return leafCount(current->nwChild) + leafCount(current->neChild) + leafCount(current->swChild) + leafCount(current->seChild);
	
	
	}


}



/**
* This function calculates and returns the minmum tolerance necessary to 
* guarantee that upon pruning the tree, no more than numLeaves leaves in the
* Quadtree
*/


int Quadtree::idealPrune(int numLeaves) const
{
	int min = 0;
	int max = 255 * 255 * 3;
	
	
	int count;
	int mid;
	
	
	while(min <= max){
		mid = (min + max)/2;
		
		count = pruneSize(mid);
		//std::cout << count << std::endl;
		if(count == numLeaves){
			while(pruneSize(mid-1) == numLeaves){
				mid--;
			}
			return mid;
		}
			
		else if(count > numLeaves)
			min = mid + 1;
		
		else
			max = mid - 1;
		
	
	}
	
	return mid;
}




