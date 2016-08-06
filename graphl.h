// Lab3
// file graphl.h
// Graph Class with Depth First Search
// Author:  Sean Lai and Sai Badey
// Date:    May 1, 2014
// Class:   CSS343 - Dr. Carol Zander

#ifndef GRAPHL_H
#define GRAPHL_H

#include "nodedata.h"

//---------------------------------------------------------------------------
// GraphL class: Contains Graph Data and traverses with depth-first search
//   Features:
//   -- allows reading of a formated text file to create the graph
//   -- uses the depth first search to traverse the graph and display
//      the graph nodes in depth first order
//   -- prints out the nodes and edges in the graph
//   -- clears the whole graph to allow for a new graph
//   -- contains struct GraphNode that stores visited, pointer to edgenode's
//      head and pointer to data
//   -- contains struct EdgeNode that points to next edgeNode and the number
//      of adjacent nodes
//
// File Format Rules:
//   -- Must have number of nodes in the first line
//   -- Then the descriptions in each line
//   -- Then in the format of "source, target" in each line
//   -- End the input by having 0 as the source (optional 0 for target node).
//   -- Example:
//       Aurora and 85th
//       Green Lake Starbucks
//       Woodland Park Zoo
//       Troll under bridge
//       PCC
//       1 5
//       1 3
//       1 2
//       2 4
//       3 4
//       0 0
// Implementation and assumptions:
//   -- the text data is assuemed to be correctly formatted
//   -- each node must contain edges and description
//   -- the text format will have size first, then description, then edges
//   -- if source node input is 0, build stops
//   -- size must be positive integer
//   -- can not have more node than the size input
//---------------------------------------------------------------------------

struct EdgeNode; // forward reference for the compiler

//an array is created of struct, edge node list is build off of this
struct GraphNode {
    bool visited; //used to mark if the node has been visted
    EdgeNode* head; // head of the list of edges
    NodeData* data;
};

//struct which contains node that the graphNode has an edge to
struct EdgeNode
{
    int adjGraphNode;  // subscript of the adjacent graph node
    EdgeNode* nextEdge;
};

class GraphL {

public:
    GraphL(); //default constructor 
    ~GraphL(); //destructor which relies of makeEmpty
    
    //creates graph from text file
    void buildGraph(istream& infile);
    
    //searches through the graph to print nodes and edges
    void displayGraph();
    
    //searches through the graph to print depth first order of nodes
    void depthFirstSearch();
    
    //stays public to allow driver to empty the graph
    //before creating a new graph
    //empties the entire graph (all edgenodes and graphnodes)
    void makeEmpty();

    
private:
    GraphNode* adjList; //list of edgenodes
    int size; //number of nodes
    
    //inserts a new edgenode at a position in the AdjList
    void insert(int position, EdgeNode* newEdgeNode);
    
    //helper function for the depth first search
    void dfs(int v);
};

#endif
