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

void Graph::swap(int commander, int subordinate){
    Participant p1 = this->adjList[commander][0];
    Participant p2;
    int i = 0;
    for(auto x : this->adjList[commander]){
        if(x.id == subordinate){
            p2 = x;
            this->adjList[commander].erase(this->adjList[commander].begin()+i);
            this->adjList[subordinate].push_back(p1);
            if(this->isCyclic()){
                this->adjList[subordinate].pop_back();
                this->adjList[commander].push_back(p2);
            }
            else{
                std::cout << "S T" << std::endl;
                return;
            }
        }
        i++;
    }
    std::cout << "S N" << std::endl;
}

void Graph::youngestCommander(int subordinate){
    for (unsigned int v = 1; v < this->adjList.size(); ++v){  
        for (auto x : this->adjList[v]){
           if(x.id == this->adjList[v][0].id) //ignora o primeiro elemento, uma pessoa nao pode ser o proprio chefe
                continue;
           if(x.id == subordinate){
               std::cout << "C " << this->adjList[v][0].age << std::endl;
               return;
           }
        }
    }
    std::cout << "C *" << std::endl; 
}

void Graph::meeting(){
    std::cout << "Meet Succ" << std::endl;
}

bool Graph::isCyclicUtil(int index, bool visited[], bool* recStack){
    if(visited[index] == false){
        visited[index] = true;
        recStack[index] = true;

        for(auto i : this->adjList[index]){
            if(i.id == this->adjList[index][0].id)
                continue;
            if(!visited[i.id] && isCyclicUtil(i.id, visited, recStack))
                return true;
            else if (recStack[i.id]) 
                return true; 
        }
    }
    recStack[index] = false;  // remove the vertex from recursion stack 
    return false;
}

bool Graph::isCyclic(){
    int V = (int)this->adjList.size();
    bool *visited = new bool[V]; 
    bool *recStack = new bool[V]; 
    for(int i = 0; i < V; i++) { 
        visited[i] = false;
        recStack[i] = false; 
    }
    for(int i = 0; i < V; i++){
        if (isCyclicUtil(i, visited, recStack)) 
            return true; 
    }
    return false; 
}