#include <iostream>
#include <fstream>
#include <string>

using std::string;
using std::ifstream;
using std::ofstream;
using std::cerr;
using std::cout;

int main(int argc, char** argv){
    string fileName = argv[1];

    ifstream input;
    input.open(fileName);

    int x;

    if (!input) {
        cerr << "Unable to open file " << fileName;
        exit(1);   // call system to stop
    }

    input >> x;

    cout << x;
}