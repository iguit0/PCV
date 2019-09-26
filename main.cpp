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

	PCV p("A5.txt");

	vector<int> solAleatoria = p.geraSolAleatoria();

	vector<int> solAleatoriaAux = solAleatoria;

	//solAleatoria = p.geraSolAleatoria();

	cout << "Solucao gerada Aleatoriamente: ";

	double foSolAleatoria = p.fo(solAleatoria);

	double foSolAleatoriaAux = foSolAleatoria;

	p.imprimeSol(solAleatoria);

	cout << "Fo: " << p.fo(solAleatoria) << endl;

	vector<int> solVizProx;

	solVizProx = p.geraSolVizProx();

	cout << "Solucao gerada pelo Vizinho Mais Proximo: ";

	p.imprimeSol(solVizProx);

	cout << "Fo: " << p.fo(solVizProx) << endl;

	vector<int> solInsMaisBar;

	solInsMaisBar = p.geraSolInsMaisBar();

	cout << "Solucao gerada pela Insercao Mais Barata: ";

	p.imprimeSol(solInsMaisBar);

	cout << "Fo: " << p.fo(solInsMaisBar) << endl;

	cout << "Busca Local com movimentos de troca aplicada a solução aleatoria: " << endl;

	p.descidaCompletaTroca(solAleatoria, foSolAleatoria);

	p.imprimeSol(solAleatoria);

	cout << "Solucao apos busca local c/ movimento de troca: " << foSolAleatoria << endl;

	cout << "Busca Local c/ primeira melhora c/ movimento de troca aplicada a solução aleatoria: " << endl;

	p.descidaPrimeiraTroca(solAleatoria, foSolAleatoria);

	p.imprimeSol(solAleatoria);

	cout << "Solucao apos busca local c/ primeira melhora c/ movimento de troca: " << foSolAleatoria << endl;

	return 1;
}
