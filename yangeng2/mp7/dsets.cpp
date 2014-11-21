
#include "dsets.h"

void DisjointSets::addelements(int num)
{
	for(int i = 0; i < num; i++){
		set.push_back(-1);
	}
}	
				
int DisjointSets::find(int elem)
{
	if(set[elem] < 0)
		return elem;
	else
		return set[elem] = find(set[elem]);
}

void DisjointSets::setunion	(int a, int	b)
{
	int root1 = find(a);
	int root2 = find(b);
	int newSize = set[root1] + set[root2];
	if(set[root1] <= set[root2]){
		set[root2] = root1;
		set[root1] = newSize;
	}
	else{
		set[root1] = root2;
		set[root2] = newSize;
	
	}

}
