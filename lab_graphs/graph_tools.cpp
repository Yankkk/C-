/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"
#include <map>

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph & graph, Vertex start, Vertex end)
{
	queue<Vertex> q;
	queue<Vertex> r;
	//vector<Vertex> result;
	vector<Vertex> v = graph.getVertices();
	
	for(size_t i = 0; i < v.size(); i++){
		graph.setVertexLabel(v[i], "UNEXPLORED");	
		vector<Vertex> temp = graph.getAdjacent(v[i]);
		for(size_t j = 0; j < temp.size(); j++){
			graph.setEdgeLabel(v[i], temp[j], "UNEXPLORED");
		}
	}
	
	graph.setVertexLabel(start, "VISITED");
	q.push(start);
	int min = 0;
	
	while(!q.empty()){
		Vertex x = q.front();
		q.pop();
		vector<Vertex> adj = graph.getAdjacent(x);
		for(size_t i = 0; i < adj.size(); i++){
			if(graph.getVertexLabel(adj[i]) == "UNEXPLORED"){
				graph.setEdgeLabel(x, adj[i], "DISCOVERY");
				graph.setVertexLabel(adj[i], "VISITED");
				q.push(adj[i]);
				
				}
			
			
			else if(graph.getEdgeLabel(x, adj[i]) == "UNEXPLORED"){
				graph.setEdgeLabel(x, adj[i], "CROSS");
			}
			
			
			if(adj[i] == end){
				r.push(end);
				while(!r.empty()){
					Vertex x = r.front();
					r.pop();
					vector<Vertex> a = graph.getAdjacent(x);
					for(size_t i = 0; i < a.size(); i++){
						if(graph.getEdgeLabel(x, a[i]) == "DISCOVERY"){
							graph.setEdgeLabel(x, a[i], "MINPATH");
							min ++;
							if(a[i] != start)
								r.push(a[i]);
							else
								return min;
						}
					}
				}
			}
			}
		}
				
    return min;
}

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may uase the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
int GraphTools::findMinWeight(Graph & graph)
{
	
	queue<Vertex> q;
	vector<Vertex> v = graph.getVertices();
	
	for(size_t i = 0; i < v.size(); i++){
		graph.setVertexLabel(v[i], "UNEXPLORED");	
		vector<Vertex> temp = graph.getAdjacent(v[i]);
		for(size_t j = 0; j < temp.size(); j++){
			graph.setEdgeLabel(v[i], temp[j], "UNEXPLORED");
		}
	}
	
	Vertex vertex = graph.getStartingVertex();
	graph.setVertexLabel(vertex, "VISITED");
	q.push(vertex);
	int min = -1;
	
	
	vector<Vertex> a = graph.getAdjacent(vertex);
	Vertex start = vertex;
	Vertex end = a[0];
	
	min = graph.getEdgeWeight(vertex, a[0]);
	
	while(!q.empty()){
		Vertex x = q.front();
		q.pop();
		vector<Vertex> adj = graph.getAdjacent(x);
		for(size_t i = 0; i < adj.size(); i++){
			if(graph.getVertexLabel(adj[i]) == "UNEXPLORED"){
				graph.setEdgeLabel(x, adj[i], "DISCOVERY");
				graph.setVertexLabel(adj[i], "VISITED");
				q.push(adj[i]);
				
				
			}
			else if(graph.getEdgeLabel(x, adj[i]) == "UNEXPLORED"){
				graph.setEdgeLabel(x, adj[i], "CROSS");
			}
			int temp = graph.getEdgeWeight(x, adj[i]);
			if(temp < min){
				min = temp;
				start = x;
				end = adj[i]; 
			}	
		
		}
		
	}
	
	graph.setEdgeLabel(start, end, "MIN");
    return min;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the libdsets folder.
 * @note You may call std::sort (http://www.cplusplus.com/reference/algorithm/sort/)
 *  instead of creating a priority queue.
 */
void GraphTools::findMST(Graph & graph)
{
	vector<Edge> e = graph.getEdges();
	std::sort(e.begin(), e.end());
	
	vector<Vertex> v = graph.getVertices();
	std::map<Vertex, int> vertex;
	for(size_t i = 0; i < v.size(); i++){
		vertex[v[i]] = i;
	}
	DisjointSets set;
	set.addelements(v.size());
	
	for(size_t i = 0; i < e.size(); i ++){
		if(set.find(vertex[e[i].source]) != set.find(vertex[e[i].dest])){
			set.setunion(vertex[e[i].source], vertex[e[i].dest]);
			graph.setEdgeLabel(e[i].source, e[i].dest, "MST");	
		}
	}
}
