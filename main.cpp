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

    return 1;
}