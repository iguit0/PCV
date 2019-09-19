#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

#include "PCV.h"

using namespace std;

int main() {
    srand(time(NULL));
    //srand(1);
    PCV pcv("instancia.txt");
    vector<int> solucaoAleatoria;
    solucaoAleatoria = pcv.geraSolAleatorio();
    pcv.imprimeSolucao(solucaoAleatoria);
    cout << "Funcao Objetivo: " << pcv.funcaoObjetivo(solucaoAleatoria) << endl;


    vector<int> solVizProx = pcv.geraSolVizProx();
    cout << "Solucao gerada por vizinho mais proximo" << endl;
    pcv.imprimeSolucao(solVizProx);
    cout << "Solucao vizinho + prox: " << pcv.funcaoObjetivo(solVizProx) << endl;

    vector<int> solInsMaisBar = pcv.geraSolInsMaisBar();
    cout << "Solucao gerada pela insercao mais barata" << endl;
    pcv.imprimeSolucao(solInsMaisBar);
    cout << "Funcao Objetivo Insercao mais barata" << pcv.funcaoObjetivo(solInsMaisBar) << endl;


    return 1;
}