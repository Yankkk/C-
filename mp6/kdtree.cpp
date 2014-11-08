/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
#include <math.h> 

template<int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim> & first, const Point<Dim> & second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
     if(first[curDim] < second[curDim])
     	return true;
     else if(first[curDim] == second[curDim])
     	return first < second;
    return false;
}


template<int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim> & target, const Point<Dim> & currentBest, const Point<Dim> & potential) const
{
    /**
     * @todo Implement this function!
     */
     int p = 0;
     int c = 0;
     for(int i = 0; i < Dim ; i ++ ){
     	p += pow(target[i]-potential[i], 2);
    	c += pow(target[i]-currentBest[i], 2);
     }
     if(p < c)
     	return true;
     else if(p == c){
     	return potential < currentBest;
     
     }
     return false;
   
}

template<int Dim>
KDTree<Dim>::KDTree(const vector< Point<Dim> > & newPoints)
{
    /**
     * @todo Implement this function!
     */
     if(newPoints.size() != 0)
	{
		points.resize(newPoints.size());
		for(size_t i = 0; i < points.size(); i++)
			points[i] = newPoints[i];
		
		quickselect(points, 0, points.size()-1, 0);
	}
}

template<int Dim>
void KDTree<Dim>::quickselect(vector<Point<Dim> > & newPoints, int min, int max, int curDim)
{
	int mid = (min + max)/2;
	if(min < max){
		select(newPoints, min, max, mid, curDim);
		if(min < mid)
			quickselect(newPoints, min, mid-1, (curDim+1) % Dim);
		if(mid < max)
			quickselect(newPoints, mid+1, max, (curDim+1) % Dim);
	
	}

}
template<int Dim>
void KDTree<Dim>::select(vector<Point<Dim> > & newPoints, int left, int right, int mid, int curDim)
{
	if(left >= right)
		return;
	while(left < right)
	{

		int index = (left + right)/2;
		int newPiv = partition(newPoints, left, right, index, curDim);
		if(mid == newPiv)
			return;		
		else if(mid < newPiv)
			right = newPiv - 1;
			
		else
		{
			left = newPiv + 1;
			
		}
	}

}


template<int Dim>
int KDTree<Dim>::partition(vector<Point<Dim> > & newPoints, int left, int right, int pivot, int curDim)
{
	if(!newPoints.empty()){
		Point<Dim> pivotV = newPoints[pivot];
		Point<Dim> temp = newPoints[pivot];
		newPoints[pivot] = newPoints[right];
		newPoints[right] = temp;
		int index = left;
		
		for(int i = left; i < right; i++) 
		{
			if(smallerDimVal(newPoints[i], pivotV, curDim))
			{
				temp = newPoints[index]; 
				newPoints[index] = newPoints[i];
				newPoints[i] = temp; 
				index++; 
			}
		}

		temp = newPoints[right];
		newPoints[right] = newPoints[index];
		newPoints[index] = temp; 
	
		return index;

	}
	return 0;

}




template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & query) const
{
    /**
     * @todo Implement this function!
     */
     
   
   return findnear(query,0, points.size()-1,0);
}

template<int Dim>
Point<Dim> KDTree<Dim>::findnear(const Point<Dim> & query, int min, int max, int curDim) const
{
	int mid = (min + max)/2;
	bool inLeft = false;
	Point<Dim> currentBest = points[mid];

	if(smallerDimVal(query, points[mid], curDim))
	{
		inLeft = true;
		if(min == mid)
			currentBest = points[mid]; 
		else
			currentBest = findnear(query, min, mid - 1, (curDim + 1) % Dim);
	}

	else
	{
		if(max == mid)
			currentBest = points[mid]; 

		else
			currentBest = findnear(query, mid + 1, max, (curDim + 1) % Dim);
	}

	Point<Dim> potential = points[mid];

	if(shouldReplace(query, currentBest, potential))
			currentBest = potential;

	int distance = 0;

	for(int i = 0; i < Dim; i++)
		distance += pow(currentBest[i] - query[i], 2);
				
	int radius = 0;
	radius += pow((query[curDim] - points[mid][curDim]), 2);

	if((radius <= distance) && (inLeft) && (max > mid))
			potential = findnear(query, mid + 1, max, (curDim + 1) % Dim);

	else if((radius <= distance) && (!inLeft) && (min < mid))
			potential = findnear(query,min, mid - 1, (curDim + 1) % Dim);

	if(shouldReplace(query, currentBest, potential))
			currentBest = potential;

	return currentBest;



}
