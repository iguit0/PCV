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

    vector<int> geraSolVizProx(); // gera solução pelo vizinho mais próximo

    int retornaMenorDistancia(int cidadeAtual, vector<int> &listaCandidatos); // retorna a posição da cidade mais próxima na lista de candidatos

    vector<int> geraSolInsMaisBar(); // gera solução pela inserção mais barata

    pair<int,int> retornaMenorIns(vector<int> &listaCandidatos, vector<int> &solucoes); // retorna a posicao da cidade com a inserção mais barata na lista de candidatos
};