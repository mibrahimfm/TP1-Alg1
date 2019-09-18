#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>
#include <stack>

using std::vector;
using std::stack;

struct Participant{
    int id;
    int age;
};

class Graph{
private:
    void addEdge(Participant, Participant);
    bool isCyclicUtil(int, bool[], bool*);
    vector<Participant> findCommanders(Participant);
    void meetingUtil(int, bool[], stack<int>&);
    vector<vector<Participant>> adjList;
    bool isCyclic();
    public:
    Graph(int*, int**, int, int);
    void PrintGraph();
    void Swap(int, int);
    void YoungestCommander(int);
    void Meeting();
};


#endif