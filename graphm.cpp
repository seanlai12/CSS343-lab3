// Lab3
// file graphm.cpp
// Graph Class with Dijkstra's Shortest Path Algorithm
// Author:  Sean Lai and Sai Badey
// Date:    May 1, 2014
// Class:   CSS343 - Dr. Carol Zander

#include <climits>
#include <iomanip>
#include "graphm.h"

//---------------------------------------------------------------------------
// GraphM
// default constructor
// creates an empty graph with all distance to infinite, no path, unvisited
GraphM::GraphM()
{
    size = 0; //graph with no nodes
    
    for(int i = 1; i < MAXNODES; i ++)
    {
        for(int j = 1; j < MAXNODES; j++)
        {
            T[i][j].dist = INT_MAX;
            T[i][j].path = 0;
            T[i][j].visited = 0;
            C[i][j] = INT_MAX;
        }
    }
}

//---------------------------------------------------------------------------
// buildGraph
// Takes the input ifstream as the parameter. a text file.
// Text file is assumed to have the correct format.
// Builds the graph with nodes and edges, input of zero in the source node
// will result a end of the input.
void GraphM::buildGraph(ifstream& infile)
{
    bool end = false;
    int source = 0, target = 0, cost = 0;
    
    infile >> size; // number of nodes
    string s; // used to read through to end of line
    getline(infile, s);
    
        if (size > 0)
        {
            for (int i = 1; i < size+1; i++)
            {
                data[i].setData(infile);
            }
            while (!infile.eof() && !end)
            {
                infile >> source >> target >> cost;
                if(source > 0)
                {
                    insertEdge(source, target, cost); // inserts the edge
                }
                else
                {
                    end = true;
                }
            }
        }
}

//---------------------------------------------------------------------------
// insertEdge
// Takes 3 ints. source, target and cost as parameter
// sets the cost into the C[source][target] to set a new edge with given cost
void GraphM::insertEdge(const int source, const int target, const int cost)
{
    if (source <= size && target <= size && cost <= INT_MAX)
    {
        C[source][target] = cost; //insert cost into specified index
    }
}

//---------------------------------------------------------------------------
// removeEdge
// Takes 2 ints. source and target as parameter
// sets the cost into the C[source][target] to infinity, thus removing edge.
void GraphM::removeEdge(const int source,const int target)
{
    C[source][target] = INT_MAX; //Set to infinity representation
}

//---------------------------------------------------------------------------
// findV
// Takes source int as a parameter
// Finds the next smallest unvisited v. Used int he dijkstra's algorithm
// returns int v.
int GraphM::findV(int source)
{
    int v = 1;
    int lowest = INT_MAX; // Starts with infinity
    
    for(int i = 1; i < size + 1; i++)
    {
        if( T[source][i].dist < lowest && T[source][i].visited == false)
        {
            v = i; //updates v if smaller
            lowest = T[source][i].dist; //update the lowest
        }
    }
    return v;
}

//---------------------------------------------------------------------------
// findShortestPath
// Performs Dijkstra's shortest path algorithm
// finds shortest path from node to node and sets the shortest path to T[][].
void GraphM::findShortestPath()
{
    int v = 0;
    
    //Initialize graph
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            T[i][j].dist = INT_MAX;
            T[i][j].visited = false;
            T[i][j].path = 0;
        }
    }
    
    for(int source = 1; source < size + 1; source++)
    {
        T[source][source].dist = 0; //sets source to cost 0

        for(int i = 1; i < size; i++) //loop through nodes
        {
            v = findV(source); //find the next v
            T[source][v].visited = true; // mark v
            
            for(int w = 1; w < size + 1; w++) //loop through edges
            {
                if ((T[source][w].visited == false && C[v][w] != INT_MAX)
                    && (T[source][w].dist > (T[source][v].dist + C[v][w])))
                {
                        T[source][w].dist = (T[source][v].dist + C[v][w]);
                        T[source][w].path = v; //update if shorter path found
                }
            }
        }
    }
}

//---------------------------------------------------------------------------
// displayAll
// Displays all data in the T[][]. Contains description, from node, to node,
// shortest path cost, and the shortest path
void GraphM::displayAll() const
{
    if (size > 0)
    {
        cout << "Description" << setw(23);
        cout << "From Node" << setw(10);
        cout << "To Node" << setw(15);
        cout << "Dijikstra's" << setw(10);
        cout << "Path" << endl << endl;
    }
    
    //Walk through all data and print info
    for (int i = 1;i < size + 1; i++)
    {
        cout << data[i] << endl; //50 width for description
        
        for(int j = 1; j < size + 1; j++)
        {
            if (T[i][j].dist > 0 && T[i][j].dist < INT_MAX)
            {
                cout << setw(31) << i;
                cout << setw(10) << j;
                cout << setw(15) << T[i][j].dist;
                cout << setw(10);
                getPath(i,j); //Print Path
                cout << endl;
            }
            else if (i != j) //No path and no cost
            {
                    cout << setw(31) << i;
                    cout << setw(10) << j;
                    cout << setw(15) << "----" << endl;
            }
        }
    }
    cout << endl;
}

//---------------------------------------------------------------------------
// getPath
// Takes 2 ints. from and to nodes.
// Prints the shortest path in the T[][] between two nodes.
// Uses recursion to print path
void GraphM::getPath(const int from, const int to) const
{
    if (from != to && T[from][to].path != 0)
    {
            getPath(from, T[from][to].path); //recursion to find previous
    }
    cout << to << " ";
}

//---------------------------------------------------------------------------
// display
// Takes 2 ints. from and to nodes.
// Displays the data in the between the two nodes passed in.
// shortest path cost, and the shortest path
// prints "Path Not Found" if distance is infinity
void GraphM::display(int const from, int const to) const
{
    if (from >= 0 && to >= 0)
    {
        if(T[from][to].dist != INT_MAX && T[from][to].dist >= 0) //path found
        {
            cout << from << setw(3) << to << setw(3) <<
                                T[from][to].dist << setw(3);
            getPath(from, to);
            getPathName(from, to);
            cout << data[to] << endl << endl;
        }
        else // infinity = no path
        {
            cout << from <<  setw(10) << to;
            cout << setw(25) << "Path Not Found" << endl << endl;
        }
    }
}

//---------------------------------------------------------------------------
// getPathName
// Takes 2 ints. from and to nodes.
// Displays the path description of the two ints
void GraphM::getPathName(const int from, const int to) const
{
    if (from != to && T[from][to].path != 0)
    {
            getPathName(from, T[from][to].path); //recursion to find previous
    }
    cout << data[T[from][to].path] << endl;
    
}
