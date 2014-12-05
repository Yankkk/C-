#ifndef DSETS_H
#define DSETS_H
 
#include <vector> 
 
class DisjointSets
{
	private:
		std::vector<int> set;
		
	public:
		void addelements(int num);	 //this function add num elements to set
		
		int find(int elem);	 // this function find the elem
		
		void setunion(int a, int b);	// this function union two sets	



};
#endif
