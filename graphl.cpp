// Lab3
// file graphl.cpp
// Graph Class with Depth First Searching Algorithm
// Author:  Sean Lai and Sai Badey
// Date:    May 1, 2014
// Class:   CSS343 - Dr. Carol Zander

#include "graphl.h"
#include <iostream>
#include <iomanip>
// Uses getline from string class, included in nodedata.h
// Be sure to include nodedata.h which includes <string>.

//---------------------------------------------------------------------------
// GraphL
// default constructor
// initializes size to 0 and ensures adjList is pointing to NULL
GraphL::GraphL()
{
    size = 0;
    adjList = NULL;
}

//---------------------------------------------------------------------------
// ~GraphL
// destructor
// Calls helper function to deal with deleting all memory
GraphL::~GraphL()
{
    makeEmpty(); //calls upon helper function
}

//---------------------------------------------------------------------------
// buildGraph
// Takes the input ifstream as the parameter.
// Text file is assumed to have the correct format.
// Builds the graph with nodes and edges, 
// input of zero for the source node will result a end of the input.
//
// Implementation: 
// The function first clears out the graph to ensure it is empty.
// Then, a new graph is instantiated and initialized based on size.
// The input stream then pulls in the source and target nodes to construct
// the graph using the function insert.
void GraphL::buildGraph(istream& infile) {
    int fromNode, toNode;              // from and to node ends of edge
    
    makeEmpty();                       // clear the graph of memory
    
    infile >> size;                    // read the number of nodes
    if (infile.eof()) return;          // stop if no more data
    
    string s;                          // used to read through to end of line
    getline(infile, s);
    
    if (size > 0)
    {
        adjList = new GraphNode[size+1];
        
        //Assign NodeData's data to GraphNode and set to default values
        //Also initializes the the list.
        for(int i = 1; i < size+1; i++)
        {
            adjList[i].data = new NodeData;
            adjList[i].data->setData(infile);
            adjList[i].visited = false;
            adjList[i].head = NULL;
        }
    
        //read the edge data and add to the adjacency list
        bool end = false;
        while(!infile.eof() && !end)
        {
            
            infile >> fromNode >> toNode;
            if(fromNode == 0 || toNode == 0)
            {
                end = true;      //base case for termination
            }
            else
            {  //if legitimate data, create a new edgeNode and call insert
                if(fromNode > 0 && toNode > 0)
                {
                    EdgeNode* newEdgeNode = new EdgeNode();
                    newEdgeNode->adjGraphNode = toNode;
                    insert(fromNode, newEdgeNode);
                }
            }
        }
    }
}

//---------------------------------------------------------------------------
// insert
// Parameters: an int and a pointer to an edgeNode
// The int is the source node and the edgeNode is the target node (an edge)
// Inserts this edgenode at the front of the edgeNode list at int position
void GraphL::insert(int position, EdgeNode* newEdgeNode)
{
    if(adjList[position].head == NULL)
    {
        adjList[position].head = newEdgeNode;
    }
    else
    {
        newEdgeNode->nextEdge = adjList[position].head;
        adjList[position].head = newEdgeNode;
    }
}

//---------------------------------------------------------------------------
// makeEmpty
// Takes in no parameters.
// Plays role of destructor: deletes the graphNode Array and edgeNode lists
//
// Implementation:
// Loops through the entire adjList array and deletes all the
// edgeNodes. After this, the array data and array are deleted.
void GraphL::makeEmpty()
{
    if (size > 0)
    {
        //This loop traverses the adjList array
        for(int i = 1; i < size+1; i++)
        {
            //if there is an edge associated with this position
            while(adjList[i].head != NULL)
            {
                //delete the head node and replace it with next
                EdgeNode* current = adjList[i].head;
                adjList[i].head = adjList[i].head->nextEdge;
                delete current;
            }
            //while looping, delete the data for each position
            delete adjList[i].data;
        }
    }
    
    size = 0;
    delete [] adjList;
    adjList = NULL;
}

//---------------------------------------------------------------------------
// depthFirstSearch
// Takes in no parameters.
// Prints out the depth first ordering of the nodes via helper function: dfs
//
// Implementation:
// Ensures that the adjList is iinitialized to false.
// Calls the dfs function on each node.
void GraphL::depthFirstSearch()
{
    //initializer loop
    for(int i = 1; i < size; i++)
    {
        adjList[i].visited = false;
    }
    cout << "Depth-first ordering: ";
    
    //loops to pass in unvisited v to dfs helper function
    for (int v = 1; v < size; v++)
    {
        if (adjList[v].visited == false)
        {
            dfs(v);
        }
    }
    cout << endl;
}

//---------------------------------------------------------------------------
// dfs (depthFirstSearch helper function)
// Takes in node parameters
// Prints out the depth first ordering of the nodes
//
// Implementation:
// Marks each handed node as visited. A current pointer is initialized.
// Loops through to recursively call dfs on edge nodes linked to handed node
void GraphL::dfs(int v)
{
        int w; //the node that v is connected to (edge)
        adjList[v].visited = true;
        cout << v << " ";
        
        EdgeNode* currentEdge = adjList[v].head;
        
        //while loop goes through list of edges to recursively call dfs
        //on the elements of the list if not yet visited
        while(currentEdge != NULL)
        {
            w = currentEdge->adjGraphNode;
            if(adjList[w].visited == false)
            {
                dfs(w);
            }
            currentEdge = currentEdge->nextEdge;
        }
}

//---------------------------------------------------------------------------
// displayGraph
// Takes in no parameters
// Prints out the nodes and the edges originating from them
//
// Implementation:
// Prints out headers such as "Graph: " before every graph
// and "Node " in front of every node
// Loops through the adjList to print out the Nodes
void GraphL::displayGraph()
{
    cout << endl << "Graph:" << endl;
    
    //this loop traverses the adjList array
    for(int i = 1; i < size+1; i++)
    {
        cout << "Node " << i << setw(30) << *adjList[i].data << endl;
        
        if (adjList[i].head != NULL)
        {
            EdgeNode* current = adjList[i].head; //start at head
            
            //this while loop traverses edges of each node in adjList
            while (current != NULL)
            {
                cout << "   edge " << i << " " << current->adjGraphNode << endl;
                current = current->nextEdge; //go to next node
            }
        }
    }
}
