#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

#include "PCV.h"

using namespace std;

int main()
{
	//srand(time(NULL));
	srand(1);

	PCV p("A280.txt");	
	
	vector<int> solAleatoria, solAleatoriaAux;

	solAleatoria = p.geraSolAleatoria();

	solAleatoriaAux = solAleatoria;

	cout << "Solucao gerada Aleatoriamente: ";
	
	p.imprimeSol(solAleatoria);

	double foSolAleatoria = p.fo(solAleatoria);

	double foSolAleatoriaAux = foSolAleatoria;

	cout << "Fo: " << foSolAleatoria << endl;


	p.GRASP(solAleatoria, foSolAleatoria, 10, 0.2);


	p.imprimeSol(solAleatoria);

	cout << "Fo: " << foSolAleatoria << endl;

	/*vector<int> solVizProx;

	solVizProx = p.geraSolVizProx();

	cout << "Solucao gerada pelo Vizinho Mais Proximo: ";
	
	p.imprimeSol(solVizProx);

	cout << "Fo: " << p.fo(solVizProx) << endl;
	
	vector<int> solInsMaisBar;

	solInsMaisBar = p.geraSolInsMaisBar();

	cout << "Solucao gerada pela Insercao Mais Barata: ";
	
	p.imprimeSol(solInsMaisBar);

	cout << "Fo: " << p.fo(solInsMaisBar) << endl;

	cout << "Busca local com movimento de troca aplicada a solucao aleatoria..." << endl;

	p.descidaCompletaTroca(solAleatoria, foSolAleatoria);

	p.imprimeSol(solAleatoria);
	
	cout << "Solucao apos Busca Local com movimento de troca: " << foSolAleatoria << endl;


	cout << "Busca local com Primeira Melhora com movimento de troca aplicada a solucao aleatoria..." << endl;

	p.descidaPrimeiraTroca(solAleatoriaAux, foSolAleatoriaAux);

	p.imprimeSol(solAleatoriaAux);
	
	cout << "Solucao apos Busca Local com Primeira Melhora com movimento de troca: " << foSolAleatoriaAux << endl;*/






	return 1;
}
