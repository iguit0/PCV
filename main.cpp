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
	
	vector<int> solAleatoria;

	solAleatoria = p.geraSolAleatoria();

	cout << "Solucao gerada Aleatoriamente: ";
	
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






	return 1;
}
