#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

class PCV {
    public:
    
    ifstream f; // objeto p/ leitura de arquivos
    string nomeArq; // nome do arquivo

    PCV(string nomeArq); // construtor e destrutor
    virtual ~PCV();

    int N; // numero das cidades

    vector< vector<double> > matriz_dist; // matriz de distâncias
    
    vector<int> geraSolAleatorio(); // gera solução aleatória

    void imprimeSolucao(vector<int> &solucaoAleatoria); // imprime solução aleatória

    double funcaoObjetivo(vector<int> &solucaoAleatoria);  // função de avaliação (fitness)
};