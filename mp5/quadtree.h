// **************************************************************
// *		   
// *  quadtree.h
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#ifndef QUADTREE_H
#define QUADTREE_H


#include <cstddef>
#include <vector>
#include <queue>
#include <utility>
#include <sstream>
#include <map>
#include <string>
#include <ostream>

#include "png.h"

class Quadtree
{
	public:

	Quadtree(); // a no parameter constructor
	
	Quadtree(const PNG & source, int resolution); // a two parameter constructor
	
	Quadtree(Quadtree const & other); // a copy constructor

	~Quadtree(); // a destructor

	const Quadtree & operator=(const Quadtree & rhs); // a copy constructor

	RGBAPixel getPixel(int x, int y) const; // a function to get a RGBAPixel

	void buildTree(PNG const & source, int resolution); // a function to build the Quadtree
	
	PNG decompress() const; // a function returns the underlying PNG object represented by the Quadtree

	void clockwiseRotate(); // turn the Quadtree clockwise by 90 degrees

	void prune(int tolerance); // compresses the image this Quadtree represents

	int pruneSize(int tolerance) const; // count the toal number of leaces the Quadtree would have if it were pruned as in the prune function

	int idealPrune(int numLeaves) const; // calculates and returns the minmum tolerance necessary to guarantee that upon pruning the tree


	private:

	// A simple class representing a single node of a Quadtree.
	// You may want to add to this class; in particular, it could probably
	// use a constructor or two...
	class QuadtreeNode
	{
		public:
		QuadtreeNode* nwChild;  // pointer to northwest child
		QuadtreeNode* neChild;  // pointer to northeast child
		QuadtreeNode* swChild;  // pointer to southwest child
		QuadtreeNode* seChild;  // pointer to southeast child

		RGBAPixel element;  // the pixel stored as this node's "data"

		//this is a QuadtreeNode constructor with no parameter
		QuadtreeNode() : nwChild(NULL), neChild(NULL), swChild(NULL), seChild(NULL)
		{
			element = RGBAPixel();
		}
		
		//this is a QuadtreeNode constructor with a RGBAPixel as a parameter
		QuadtreeNode(RGBAPixel elem) : nwChild(NULL), neChild(NULL), swChild(NULL), seChild(NULL)
		{
			element = RGBAPixel(elem.red, elem.green, elem.blue);
		}	

	};
	
	QuadtreeNode* root;    // pointer to root of quadtree
	
	void clear(QuadtreeNode * & current); //helper function for destructor

	void copy(const Quadtree & other); //copy helper function for Quadtree
	
	QuadtreeNode * copyNode( const QuadtreeNode * current ); //copy helper function for QuadtreeNode

	int size;

	RGBAPixel getPixel(int x, int y, int resolution, QuadtreeNode * current) const; // helper function for getPixel

	bool leaf(QuadtreeNode * current) const; // check whether is leaf node

	void buildBranch(PNG const & source, int x, int y, int resolution, QuadtreeNode * current); // helper function for buildTree
	
	void decompress(int x, int y, int resolution, QuadtreeNode * current, PNG & image) const; //helper function for decompress
	
	void clockwiseRotate(QuadtreeNode * current); // helper function for clockwiseRotate
	
	bool inTol(QuadtreeNode * current, QuadtreeNode * child, int tolerance) const; // calculate whether with tolerance
	
	void prune(int tolerance, QuadtreeNode * & current); // helper function for prune

	int pruned(QuadtreeNode * current, int tolerance) const; // helper function for pruneSize
	
	int leafCount(QuadtreeNode * current) const; // count the number of leaves in current
	
	
	
	/**** Functions added for testing/grading                ****/
	/**** Do not remove this line or copy its contents here! ****/
	#include "quadtree_given.h"
};

#endif
