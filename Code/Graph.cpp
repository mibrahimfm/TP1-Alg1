#include "Graph.hpp"

Graph::Graph(int* ages, int** relations, int qtParticipants, int qtRelations){
    this->adjList = vector<vector<Participant>>(qtParticipants+1);
    for(int i = 1; i <= qtParticipants; i++){
        Participant p;
        p.id = i; p.age = ages[i-1];
        adjList[i].push_back(p);
    }

    for(int j = 0; j < qtRelations; j++){
        Participant p1, p2;
        if(!adjList[relations[j][0]].empty()){
            p1 = adjList[relations[j][0]][0];
        }
        if(!adjList[relations[j][1]].empty()){
            p2 = adjList[relations[j][1]][0];
        }
        addEdge(p1, p2);
    }

}

void Graph::addEdge(Participant p1, Participant p2){
    this->adjList[p1.id].push_back(p2);
}

void Graph::printGraph() { 
    for (unsigned int v = 1; v < this->adjList.size(); ++v){ 
        std::cout << "\n Adjacency list of vertex "
             << v << "\n head "; 
        for (auto x : this->adjList[v]) 
           std::cout << "-> " << x.id; 
        printf("\n"); 
    } 
} 

void Graph::swap(int, int){
    std::cout << "Swap Succ" << std::endl;
}

void Graph::youngestCommander(int subordinate){
    for (unsigned int v = 1; v < this->adjList.size(); ++v){  
        for (auto x : this->adjList[v]) 
           if(x.id == subordinate){
               std::cout << "C " << this->adjList[v][0].age << std::endl;
               return;
           }
    }
}

void Graph::meeting(){
    std::cout << "Meet Succ" << std::endl;
}