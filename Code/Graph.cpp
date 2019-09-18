#include "Graph.hpp"

//Cria o grafo utilizando uma lista de adjacências
Graph::Graph(int* ages, int** relations, int qtParticipants, int qtRelations){
    this->adjList = vector<vector<Participant>>(qtParticipants+1);
    for(int i = 1; i <= qtParticipants; i++){
        Participant p;
        p.id = i; p.age = ages[i-1];
        adjList[i].push_back(p);//Colocando cada participante no início de uma lista para definir sua lista de adjacência
    }

    //Define as listas de adjacência baseado nas relações lidas pelo arquivo
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

//Função auxiliar que adiciona uma aresta ao grafo
void Graph::addEdge(Participant p1, Participant p2){
    this->adjList[p1.id].push_back(p2);
}

//Função auxiliar de teste que imprime o grafo(lista de adjacência de cada vértice)
void Graph::printGraph() { 
    for (unsigned int v = 1; v < this->adjList.size(); v++){ 
        std::cout << "\n Adjacency list of vertex "
             << v << "\n head "; 
        for (auto x : this->adjList[v]) 
           std::cout << "-> " << x.id; 
        printf("\n"); 
    } 
} 

//Função que realiza uma troca de comando entre duas pessoas
void Graph::swap(int commander, int subordinate){
    Participant p1 = this->adjList[commander][0]; 
    Participant p2;
    int i = 0;
    for(auto x : this->adjList[commander]){
        if(x.id == subordinate){ //Verifica se existe uma relação entre os dois e faz o troca
            p2 = x;
            this->adjList[commander].erase(this->adjList[commander].begin()+i);
            this->adjList[subordinate].push_back(p1);
            if(this->isCyclic()){ //Verifica se a troca criou um ciclo no grafo e cancela a operação
                this->adjList[subordinate].pop_back();
                this->adjList[commander].push_back(p2);
            }
            else{ //Se não houve problema com ciclos, acrescenta o novo subordinado a lista dos outros chefes do novo chefe
                vector<Participant> aux = this->findCommanders(p2);
                for(auto x : aux){
                    this->adjList[x.id].push_back(p1);
                }
                std::cout << "S T" << std::endl;
                return;
            }
        }
        i++;
    }
    std::cout << "S N" << std::endl;
}

//Função para encontrar o comandante mais jovem de uma pessoa
void Graph::youngestCommander(int subordinate){
    int youngest = INT32_MAX; //Define a idade como valor máximo, para não correr riscos no if mais abaixo
    bool hasCommander = false; //Variável auxiliar para verificar se possui comandante
    for (unsigned int v = 1; v < this->adjList.size(); ++v){  
        for (auto x : this->adjList[v]){
           if(x.id == this->adjList[v][0].id) //Ignora o primeiro elemento, uma pessoa não pode ser o próprio chefe
                continue;
           if(x.id == subordinate){ //Verifica se subordinado está na lista de adjacência
               hasCommander = true;
               if(this->adjList[v][0].age < youngest){
                   youngest = this->adjList[v][0].age;
               }
           }
        }
    }
    if(hasCommander)
        std::cout << "C " << youngest << std::endl;
    else
        std::cout << "C *" << std::endl; 
}

void Graph::meetingUtil(int index, bool visited[], stack<int>& Stack){
    visited[index] = true;

    for(auto i : this->adjList[index]){
        if(!visited[i.id])
            meetingUtil(i.id, visited, Stack);
    }

    if(index != 0)
        Stack.push(index);
}

void Graph::meeting(){
    stack<int> Stack;
    int V = (int)this->adjList.size();
    bool *visited = new bool[V]; 

    for(int i = 0; i < V; i++)
        visited[i] = false;

    for (int i = 0; i < V; i++){ 
      if (!visited[i]) 
        meetingUtil(i, visited, Stack); 
    }
    // Print contents of stack 
    while (!Stack.empty()) { 
        std::cout << Stack.top() << " "; 
        Stack.pop(); 
    }
    std::cout << std::endl;
}

//Função auxiliar para verificar se o grafo possui ciclo
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
    recStack[index] = false;  // remove o vértice do stack de recursão 
    return false;
}

//Função que retorna se um grafo possui ou não ciclo
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

//Função auxiliar do swap que retorna todos os comandantes de um dado participante
vector<Participant> Graph::findCommanders(Participant p){

    vector<Participant> commanders = vector<Participant>();
    
    for (unsigned int v = 1; v < this->adjList.size(); ++v){  
        for (auto x : this->adjList[v]){
           if(x.id == this->adjList[v][0].id) //Ignora o primeiro elemento, uma pessoa não pode ser o próprio chefe
                continue;
           if(x.id == p.id){
                commanders.push_back(this->adjList[v][0]);
           }
        }
    }
    return commanders;
}