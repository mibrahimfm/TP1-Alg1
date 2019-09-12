#include <iostream>
#include <fstream>
#include <string>

using std::string;
using std::ifstream;
using std::ofstream;
using std::cin;
using std::cout;
using std::endl;
using std::getline;

int main(int argc, char** argv){
    string fileName = argv[1];

    ifstream input (fileName);

    int qtParticipants, qtRelations, qtInstructions;
    int* ages;
    int** relations;
    string reader;

    if (input.is_open()) {
        input >> qtParticipants >> qtRelations >> qtInstructions;

        ages = new int[qtParticipants];

        for(int i = 0; i < qtParticipants; i++){
            input >> ages[i];
            cout << ages[i] << " ";
        }

        relations = new int*[qtRelations];
        for(int i = 0; i < qtRelations; i++){
            relations[i] = new int[2];
        }

        for(int j = 0; j < qtRelations; j++){
            input >> relations[j][0] >> relations[j][1];
            cout << relations[j][0] << " " << relations[j][1] << endl;
        }
    }
    else{
        cout << "Erro ao abrir " << fileName << endl;
    }

}