// Lab3
// file graphm.h
// Graph Class with Dijkstra's Shortest Path Algorithm
// Author:  Sean Lai and Sai Badey
// Date:    May 1, 2014
// Class:   CSS343 - Dr. Carol Zander

#ifndef GRAPHM_H
#define GRAPHM_H

#include <iostream>
#include "nodedata.h"

//---------------------------------------------------------------------------
// GraphM class: Contains Graph Data using the Dijkstra's shortest path
//   Features:
//   -- allows reading formated text file to create the graph
//   -- uses the dijkstra's shortest path algorithm to find paths
//   -- allows displaying the whole data, containing description, cost, path
//   -- contains struct TableType that stores visited, dist, and path
//   -- able to display the shortest path found from two nodes
//   -- able to add or remove edge on a node
//
// Format Rule:
//   -- Must have size in the first line
//   -- Then the descriptions in each line
//   -- Then in the format of "source, target, cost" in each line
//   -- End the input by having 0 as the source.
//   -- Example:
//      3
//      aaa
//      bbb
//      ccc
//      1 2 3
//      1 3 1
//      2 1 2
//      3 2 1
//      0 1 2
// Implementation and assumptions:
//   -- the text data is assuemed to be correctly formatted
//   -- each node must contain edges, costs, and description
//   -- the text format will have size first, then description, then edges
//   -- if source node input is 0, build stops
//   -- size must be positive integer
//   -- cost must be positive integer
//   -- maxmimum node size is 100
//   -- can not have more node than the size input
//---------------------------------------------------------------------------

const int MAXNODES = 101; //Assumed max of 100 nodes. 0 is not used.

struct TableType {
    bool visited; //True if visited, false if not
    int dist; //Current known shortest distance
    int path; //Previous node in the min dist path
};

class GraphM {

public:
    GraphM(); //default constructor
    void buildGraph(ifstream&); //creates graph, inserting nodes
    void findShortestPath(); //Dijkstra's shortest path algorithm
    void displayAll() const;  //displays all data
    void display(int, int) const; //prints path from one node to the other
    void insertEdge(const int, const int, const int); //inserts edge
    void removeEdge(const int,const int);//removes edge
    
private:
    NodeData data[MAXNODES]; //graph node information
    int C[MAXNODES][MAXNODES]; //array for cost between nodes
    int size; //number of nodes in the graph
    TableType T[MAXNODES][MAXNODES]; //table to store the struct
    
    int findV(int); //finds the next v, smallest and unvisited
    void getPath(const int, const int) const; //prints path between two nodes
    void getPathName(const int, const int) const; //prints path descriptions
    
};

#endif
