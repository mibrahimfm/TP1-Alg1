#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using std::string;
using std::stringstream;
using std::ifstream;
using std::ofstream;
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::getline;

int main(int argc, char** argv){
    string fileName = argv[1];

    ifstream input (fileName);

    int qtParticipants, qtRelations, qtInstructions;
    int* ages;
    string reader;

    if (input.is_open()) {
        input >> qtParticipants >> qtRelations >> qtInstructions;

        ages = new int[qtParticipants];

        for(int i = 0; i < qtParticipants; i++){
            input >> ages[i];
            cout << ages[i] << " ";
        }

        int relations[qtRelations][2];

        for(int j = 0; j < qtRelations; j++){
            input >> relations[j][0] >> relations[j][1];
            cout << relations[j][0] << " " << relations[j][1] << endl;
        }
    }
    else{
        cout << "Erro ao abrir " << fileName << endl;
    }

}