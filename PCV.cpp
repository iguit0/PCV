#include "PCV.h"

PCV::PCV(string nomeArq): nomeArq(nomeArq)
{
	
	//abrir o arquivo
	f = ifstream(nomeArq);

	//verificar se o arquivo foi aberto
	if(!f.is_open())
		cout << "Erro ao abrir o arquivo " << nomeArq << "!" << endl;

	//ler numero de cidades
	f >> N;

	
	//coordenadas das cidades, tratadas como pares (x,y)
	vector< pair<double, double> > pontos(N);


	for(int i = 0; i < N; i++)
	{

		double x, y;

		//salta o id da cidade
		f >> x;

		//ler a coordenada x
		f >> x;

		//ler a coordenada y
		f >> y;

		//incluir no vetor de pontos
		pontos[i] = pair<double, double>(x,y);

	}

	cout << N << " cidades: " << endl;
	//imprimir os pontos lidos
	for(int i = 0; i < N; i++)
	{
		printf("%d - (%f, %f)\n", i, pontos[i].first, pontos[i].second);
	}

	
	//criar a matriz de distancias
	matriz_dist = vector< vector<double> >(N, vector<double>(N));

	
	//instanciar a matriz de distancias
	for(int i = 0; i < N; i++)
	{

		for(int j = 0; j < N; j++)
		{
			pair<double, double> pi = pontos[i];		
			pair<double, double> pj = pontos[j];

			
			matriz_dist[i][j] = sqrt( pow(pi.first - pj.first, 2) + pow(pi.second - pj.second, 2) );

		}

	}

	cout << endl << "Matriz de distancias: " << endl;

	//imprimir a matriz
	for(int i = 0; i < N; i++)
	{
		for(int j = 0; j < N; j++)
		{
			printf("%f\t", matriz_dist[i][j]);
		}		

		cout << endl;
	}











}

PCV::~PCV()
{
	f.close();
}


vector<int> PCV::geraSolAleatoria()
{
	vector<int> sol;

	for(int i = 1; i < N; i++)
		sol.push_back(i);

	random_shuffle(sol.begin(), sol.end());

	return sol;
}


vector<int> PCV::geraSolVizProx()
{
	vector<int> sol;

	int cidadeAtual = 0;

	//Lista de cidades candidatas
	vector<int> LC;
	
	for(int i = 1; i < N; i++)
		LC.push_back(i);


	//enquanto nao visitar todas as cidades, incluir mais cidades na solucao
	while(!LC.empty())
	{
		//Calcular a cidade mais proxima da cidade atual
		int pos = retornaMenorDist(cidadeAtual, LC);
	
		//Incluir na solucao a cidade mais proxima
		sol.push_back(LC[pos]);		
	
		//Atualizar a cidade atual
		cidadeAtual = LC[pos];

		//Remover a cidade incluida da lista de candidatos
		LC.erase(LC.begin() + pos);
	}
	
	return sol;
}

int PCV::retornaMenorDist(int cidadeAtual, vector<int>& LC)
{
	//Armazena a posicao que possui a menor distancia
	int menorPos = 0;
	
	//Armazena a menor distancia
	double menorDist = matriz_dist[cidadeAtual][LC[0]];

	//Busca pela cidade que possui a menor distancia
	for(int i = 1; i < int(LC.size()); i++)
	{
		if(matriz_dist[cidadeAtual][LC[i]] < menorDist)
		{
			menorDist = matriz_dist[cidadeAtual][LC[i]];
			menorPos = i;
		}
	}

	return menorPos;
}


vector<int> PCV::geraSolInsMaisBar()
{
	vector<int> sol;	
	
	//lista de candidatos
	vector<int> LC;

	for(int i = 1; i < N; i++)
		LC.push_back(i);
	
	//Incluir duas cidades aleatoriamente na solucao
	for(int i = 0; i < 2; i++)
	{
		int r = rand() % (LC.size()-1);

		sol.push_back(LC[r]);

		LC.erase(LC.begin() + r);
	}

	//enquanto nao visitar todas as cidades, incluir mais cidades
	while(!LC.empty())
	{
		//retornar as posicoes na solucao e da LC com a menor insercao
		pair<int,int> pos = retornaMenorIns(LC,sol);
		
		//Inserir na solucao a cidade com a menor custo de insercao
		sol.insert(sol.begin() + pos.first, LC[pos.second]);
		
		//Remover a cidade da lista de candidatos
		LC.erase(LC.begin() + pos.second);
	}

	return sol;
}

pair<int,int> PCV::retornaMenorIns(vector<int>& LC, vector<int>& sol)
{
	int menorPosLC = 0, menorPosSol = 0;
	
	double menorDist = 999999;

	for(int i = 0; i < int(LC.size()); i++)
	{
		if(matriz_dist[0][LC[i]] + matriz_dist[LC[i]][sol[0]] - matriz_dist[0][sol[0]] < menorDist)
		{
			menorDist = matriz_dist[0][LC[i]] + matriz_dist[LC[i]][sol[0]] - matriz_dist[0][sol[0]];
			menorPosLC = i;
			menorPosSol = 0;
		}

		for(int j = 1; j < int(sol.size()); j++)
		{
			if(matriz_dist[sol[j]][LC[i]] + matriz_dist[LC[i]][sol[j+1]] - matriz_dist[sol[j]][sol[j+1]] < menorDist)
			{
				menorDist = matriz_dist[sol[j]][LC[i]] + matriz_dist[LC[i]][sol[j+1]] - matriz_dist[sol[j]][sol[j+1]];
				menorPosLC = i;
				menorPosSol = j;
			}
		}

		if(matriz_dist[sol[sol.size()-1]][LC[i]] + matriz_dist[LC[i]][0] - matriz_dist[sol[sol.size()-1]][0] < menorDist)
		{
			menorDist = matriz_dist[sol[sol.size()-1]][LC[i]] + matriz_dist[LC[i]][0] - matriz_dist[sol[sol.size()-1]][0];
			menorPosLC = i;
			menorPosSol = sol.size()-1;
		}
	}

	return pair<int,int>(menorPosSol, menorPosLC);
}

void PCV::imprimeSol(vector<int> &sol)
{
	cout << "[ ";
	for(int i = 0; i < sol.size(); i++)
		cout << sol[i] << ", ";
	cout << "]" << endl;
}

double PCV::fo(vector<int> &sol)
{
	double soma = 0;
	
	//Somar a distancia da cidade inicial ate a primeira cidade da solucao
	soma = matriz_dist[0][sol[0]];
	
	//Somar as distancias das cidades na solucao
	for(int i = 0; i < int(sol.size()-1); i++)
		soma += matriz_dist[sol[i]][sol[i+1]];
	
	//Somar a distancia da ultima cidade na solucao ate a cidade 0
	soma += matriz_dist[sol[sol.size()-1]][0];

	return soma;
}

















