/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

/**
 * @return The height of the binary tree. Recall that the height of a binary tree
 *  is just the length of the longest path from the root to a leaf, and that the
 *  height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
	// Call recursive helper function on root
	return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node * subRoot) const
{
	// Base case
	if (subRoot == NULL)
        return -1;
	
	// Recursive definition
	return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that node
 *  itself, and everything to the right of a node will be printed out after that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
	// Call recursive helper function on the root
	printLeftToRight(root);

	// Finish the line
	cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node * subRoot) const
{
	// Base case - null node
	if (subRoot == NULL)
		return;

	// Print left subtree
	printLeftToRight(subRoot->left);

	// Print this node
	cout << subRoot->elem << ' ';

	// Print right subtree
	printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
	// your code here
	mirror(root);

}

template <typename T>
void BinaryTree<T>::mirror(Node * & subRoot) 
{
        if(subRoot == NULL)
	    return;
        Node * temp = subRoot->left;
        subRoot->left = subRoot->right;
        subRoot->right = temp;


	mirror(subRoot->left);
        mirror(subRoot->right);

}

/**
 * @return True if an in-order traversal of the tree would produce a nondecreasing list
 *  output values, and false otherwise. This is also the criterion for a binary tree to be
 *  a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrdered() const
{
    // your code here
	return isOrdered(root);
	
}


template <typename T>
bool BinaryTree<T>::isOrdered(const Node * subRoot) const
{
/**
        if(subRoot == NULL)
	    return true;
	
	if((subRoot->left != NULL) && (subRoot->left->elem) > (subRoot->elem))
	    return false;
	if((subRoot->right != NULL) && (subRoot->right->elem) < (subRoot->elem))
	    return false;

	

	return isOrdered(subRoot->left) && isOrdered(subRoot->right);
*/


        if ((subRoot->left == NULL) and (subRoot->right == NULL)) return true;
        if (subRoot->left != NULL and !isOrdered(subRoot->left)) return false;
        if (subRoot->right != NULL and !isOrdered(subRoot->right)) return false;
        if (subRoot->left != NULL and  subRoot->elem < getMax(subRoot->left)) return false;
        if (subRoot->right != NULL and  getMin(subRoot->right) < subRoot->elem) return false;
        return true;

}

template <typename T>
T BinaryTree<T>::getMax(const Node * subRoot) const
{
	T max = subRoot->elem;
	if(subRoot->left != NULL){
	    if(getMax(subRoot->left) > max)
		max = getMax(subRoot->left);
	}
	if(subRoot->right != NULL){
	    if(getMax(subRoot->right) > max)
		max = getMax(subRoot->right);
	}

	return max;
}


template <typename T>
T BinaryTree<T>::getMin(const Node * subRoot) const
{
	T min = subRoot->elem;
	if(subRoot->left != NULL){
	    if(getMin(subRoot->left) < min)
		min = getMin(subRoot->left);
	}
	if(subRoot->right != NULL){
	    if(getMin(subRoot->right) < min)
		min = getMin(subRoot->left);
	}

	return min;
}


/**
 * Prints out all the possible paths from the root of the tree to any leaf node.
 * That is, all sequences starting at the root node and continuing downwards, ending at a
 *  leaf node. Paths ending in a left node should be printed before paths ending in a node
 *  further to the right.
 */
template <typename T>
void BinaryTree<T>::printPaths() const
{
    // your code here
	T * nodesList = new T[200]; 
	int count = 0;
	printPaths(root, nodesList, count);
	delete [] nodesList;
}

template <typename T>
void BinaryTree<T>::printPaths(const Node * subRoot, T * nodeList, int count) const
{
	if(subRoot == NULL)
	    return;
	
	nodeList[count] = subRoot->elem;
	count++;
	if(subRoot->right == NULL && subRoot->left == NULL){
	    cout << "Path:";
	    for(int i = 0; i < count; i++){
		cout << " " << nodeList[i];
	    }
	    cout << "" << endl;
	}

	printPaths(subRoot->left, nodeList, count);

	printPaths(subRoot->right, nodeList, count);


}



/**
 * Each node in a tree has a distance from the root node - the depth of that node,
 *  or the number of edges along the path from that node to the root. This function returns
 *  the sum of the distances of all nodes to the root node (the sum of the depths of all
 *  the nodes). Your solution should take O(n) time, where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here

    //cout << sumDistances(root, 0) << endl;
    return sumDistances(root, -1);
}



template <typename T>
int BinaryTree<T>::sumDistances(const Node * subRoot, int count) const
{	
	if(subRoot == NULL)
	    return 0;
	
	
	count++;

	if(subRoot->left == NULL && subRoot->right == NULL)
	    return count;
	
	
	return count + sumDistances(subRoot->left, count) + sumDistances(subRoot->right, count);

}










