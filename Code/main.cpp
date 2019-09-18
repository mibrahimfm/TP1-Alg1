#include <iostream>
#include <fstream>
#include <string>
#include "Graph.hpp"

using std::string;
using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;
using std::getline;

int main(int argc, char** argv){
    //Recebe o nome do arquivo passado como parâmetro para o programa
    string fileName = argv[1];

    ifstream input(fileName);

    //Declarando variáveis para armazenar os valores lidos no arquivo
    int qtParticipants, qtRelations, qtInstructions, swap1, swap2, ageCom;
    int* ages;
    int** relations;
    char func;

    //Verifica se o arquivo está aberto para ler as entradas
    if (input.is_open()) {
        input >> qtParticipants >> qtRelations >> qtInstructions;

        //Definindo arrays para armazenar temporariamente as idades e as relações de comando
        ages = new int[qtParticipants]; 
        relations = new int*[qtRelations];
        for(int i = 0; i < qtRelations; i++){
            relations[i] = new int[2];
        }

        //Os dois laços a seguir leem as idades e as relações de comando, respectivamente
        for(int i = 0; i < qtParticipants; i++)
            input >> ages[i];
        for(int j = 0; j < qtRelations; j++)
            input >> relations[j][0] >> relations[j][1];

        //Criando o grafo
        Graph g(ages, relations, qtParticipants, qtRelations);

        //Percorrendo o resto do arquivo e verificado qual instrução está sendo passada
        for(int k = 0; k < qtInstructions; k++){
            input >> func;
            if(func == 'S'){
                input >> swap1 >> swap2;
                g.Swap(swap1, swap2);
            }
            else if(func == 'C'){
                input >> ageCom;
                g.YoungestCommander(ageCom);
            }
            else{
                g.Meeting();
            }
        }
    }
    //Verificando se houve falha ao abrir o arquivo
    else
        cout << "Erro ao abrir " << fileName << endl;

}