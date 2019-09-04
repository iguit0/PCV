#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

class PCV{
    public:
    
    ifstream f; // objeto p/ leitura de arquivos
    string nomeArq; // nome do arquivo

    PCV(string nomeArq); // construtor e destrutor
    virtual ~PCV();

    int N; // numero das cidades

    vector< vector<double> > matriz_dist; // matriz de distâncias
    
};