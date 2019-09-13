#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>

using std::vector;

struct Participant{
    int id;
    int age;
};

class Graph{
private:
    void addEdge(Participant, Participant);  
public:
    vector<vector<Participant>> adjList;
    Graph(int*, int**, int, int);
    void printGraph(int);
    static void swap(int, int);
    static void youngestCommander(int);
    static void meeting();
};


#endif