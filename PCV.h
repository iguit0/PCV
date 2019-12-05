#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

class PCV {
public:

	//objeto para leitura de arquivo
	ifstream f;

	//nome do arquivo
	string nomeArq;

	//construtor e destrutor
	PCV(string nomeArq);
	virtual ~PCV();

	//Numero de cidades
	int N;

	//Matriz de distancias
	vector< vector<double> > matriz_dist;

	//Imprimir solucao
	void imprimeSol(vector<int> &sol);
	
	//Funcao de avaliacao
	double fo(vector<int> &sol);
	
	//Gera solucao aleatoria
	vector<int> geraSolAleatoria();

	//Gera solucao pelo Vizinho Mais Proximo
	vector<int> geraSolVizProx();
	
	//Retorna a posicao da cidade mais proxima na LC
	int retornaMenorDist(int cidadeAtual, vector<int>& LC);

	//Gera solucao pela Insercao Mais Barata
	vector<int> geraSolInsMaisBar();
	
	//Retorna a posicao da cidade com a insercao mais barata na LC
	pair<int,int> retornaMenorIns(vector<int>& LC, vector<int>& sol);

	//Metodo de descida completa com o movimento de troca
	void descidaCompletaTroca(vector<int>& solCorrente, double& melhorFo);
	
	//Metodo de descida com primeiro de melhora com o movimento de troca
	void descidaPrimeiraTroca(vector<int>& solCorrente, double& melhorFo);

	//Multi-Start
	void multiStart(vector<int>& sol, double& foSol, int iterMax);

	//Gera solucao pelo Vizinho Mais Proximo GRASP
	vector<int> geraSolVizProxGRASP(double alpha);

	//Retorna a posicao da cidade a partir do GRASP
	int retornaMenorDistGRASP(int cidadeAtual, vector<int>& LC, double alpha);

	//GRASP
	void GRASP(vector<int>& melhorSol, double& melhorFo, int iterMax, double alpha);











};
