#include "PCV.h"

PCV::PCV(string nomeArq): nomeArq(nomeArq) {
    f = ifstream(nomeArq); // abrir arquivo

    if(!f.is_open()) cout << "ERRO AO ABRIR ARQUIVO" << nomeArq << "!\n" << endl;

    f >> N; // lendo numero de cidades

    vector<pair<double, double>> pontos(N); // coordenadas das cidades, tratadas como pares (x,y)

    for(int i=0;i<N;i++) {
        double x,y;
        f >> x; // pular (ignorar) o ID da cidade
        f >> x; // ler a coordenada x
        f >> y;

        pontos[i] = pair<double, double>(x,y); // incluir no vetor de pontos
    }

    cout << N << " cidades: " << endl; // imprimir os pontos lidos

    // verificando se a leitura do arquivo funcionou
    for(int i=0;i<N;i++) {
        printf("%d - (%f, %f)\n",i, pontos[i].first, pontos[i].second);
    }

    // criar a matriz de distância
    matriz_dist = vector<vector<double>>(N, vector<double>(N));

    // instanciar a matriz de distâncias
    for(int i=0;i<N;i++) {
        for(int j=0;j<N;j++) {
            pair<double, double> pi = pontos[i];
            pair<double, double> pj = pontos[j];
            matriz_dist[i][j] = sqrt(pow(pi.first - pj.first, 2) + pow(pi.second - pj.second,2)); // distância euclidiana
        }
    }

    cout << endl << "Matriz de Distancias: " << endl;

    // imprimir a matriz de distâncias
    for(int i=0;i<N;i++) {
    for(int j=0;j<N;j++) {
        printf("%f\t", matriz_dist[i][j]);
    }
    cout << endl;
    }
}

PCV::~PCV() {
    f.close();
}

vector<int> PCV::geraSolAleatorio() {
    vector<int> solucao;
    for(int i=1;i<N;i++) solucao.push_back(i);

    random_shuffle(solucao.begin(), solucao.end());
    return solucao;
}

int PCV::retornaMenorDistancia(int cidadeAtual, vector<int> &listaCandidatos) {
    int menorPosicao = 0; // Armazena a posição que possui a menor distância
    double menorDistancia = matriz_dist[cidadeAtual][listaCandidatos[0]]; // Armazena a menor distância

    for(int i=1;i<int(listaCandidatos.size());i++) {
        if (matriz_dist[cidadeAtual][listaCandidatos[i]] < menorDistancia) {
            menorDistancia = matriz_dist[cidadeAtual][listaCandidatos[i]];
            menorPosicao = i;
        }
    }

    return menorPosicao;
}

vector<int> PCV::geraSolVizProx() {
    vector<int> solucoes;
    int cidadeAtual = 0;

    // Lista de cidades candidatas
    vector<int> listaCandidatos;
    for(int i=1;i<N;i++) {
        listaCandidatos.push_back(i);
    }
    // enquanto não visitar todas as cidades, incluir mais cidades na solução
    while(!listaCandidatos.empty()) {
        int posicao = retornaMenorDistancia(cidadeAtual, listaCandidatos); // calcula a cidade mais proxima da cidade atual

        // incluir na solucao a cidade mais próxima
        solucoes.push_back(listaCandidatos[posicao]);

        // Atualizar Cidade Atual
        cidadeAtual = listaCandidatos[posicao];

        // Remover a cidade
        listaCandidatos.erase(listaCandidatos.begin() + posicao);
    }

    return solucoes;
}

pair<int,int> PCV::retornaMenorInst(vector<int> &listaCandidatos, vector<int> &solucoes) {
    int menorPosicaoLC = 0, menorPosicaoSolucao = 0;
    double menorDistancia = 999999999;

    for(int i=0;i<int(listaCandidatos.size());i++) {
        if(matriz_dist[0][listaCandidatos[i]] + matriz_dist[listaCandidatos[i][solucoes[0]]] - matriz_dist[0][solucoes[0]] < menorDistancia) {
            menorDistancia = matriz_dist[0][listaCandidatos[i]] + matriz_dist[listaCandidatos[i][solucoes[0]]] - matriz_dist[0][solucoes[0]];
            menorPosicaoLC = i;
            menorPosicaoSolucao = 0;
        }
    }

    for(int j=1;j<int(solucoes.size());j++) {
        if(matriz_dist[solucoes[j]][listaCandidatos[i]] + matriz_dist[listaCandidatos[i][solucoes[j+1]]] - matriz_dist[solucoes[j]][solucoes[j+1]]
        < menorDistancia) {
            menorDistancia = matriz_dist[solucoes[j]][listaCandidatos[i]] + matriz_dist[listaCandidatos[i][solucoes[j+1]]] - matriz_dist[solucoes[j]][solucoes[j+1]];
            menorPosicaoLC = i;
            menorPosicaoSolucao = j;
        }
    }

    if(matriz_dist[solucoes[solucoes.size()-1]][listaCandidatos[i]] + matriz_dist[listaCandidatos[i][0]]
        - matriz_dist[solucoes[solucoes.size()-1]][0] < menorDistancia) {
            menorDistancia = matriz_dist[solucoes[solucoes.size()=1]][listaCandidatos[i]] + matriz_dist[listaCandidatos[i][0]] - matriz_dist[solucoes[solucoes.size()=1]][0];
            menorPosicaoLC = i;
            menorPosicaoSolucao = solucoes.size()-1;
        }

    return pair<int,int>(menorPosicaoSolucao, menorPosicaoLC);
}

vector<int> PCV::geraSolInsMaisBar() {
    vector<int> solucoes;

    // Lista de cidades candidatas
    vector<int> listaCandidatos;
    for(int i=1;i<N;i++) {
        listaCandidatos.push_back(i);
    }

    for(int i=0;i<2;i++) {
        int r = rand() % (listaCandidatos.size()-1);
        solucoes.push_back(listaCandidatos[r]);
        listaCandidatos.erase(listaCandidatos.begin() + r);
    }

    // enquanto não visitar todas as cidades, incluir mais cidades
    while(!listaCandidatos.empty()) {
        pair<int,int> pos = retornaMenorInst(listaCandidatos, solucoes); // retornar as posicoes na solucao e da lista de candidatos com a menor insercao
        solucoes.insert(solucoes.begin() + pos.first, listaCandidatos[pos.second]); // inserir na solucao a cidade com menor custo de insercao
        listaCandidatos.erase(listaCandidatos.begin() + pos.second);
    }

    return solucoes;
}

void PCV::imprimeSolucao(vector<int> &solucaoAleatoria) {
    cout << "Solucao gerada aleatoriamente: ";
    cout << "[ ";
    for(int i=0;i<solucaoAleatoria.size();i++) cout << solucaoAleatoria[i] << ", ";
    cout << "]" << endl;
}

double PCV::funcaoObjetivo(vector<int> &solucaoAleatoria) {
    double soma = 0;

    // somar a distância da cidade inicial até a primeira cidade da solução
    soma = matriz_dist[0][solucaoAleatoria[0]];

    // somar as distâncias das cidades na solução
    for(int i=0;i<int(solucaoAleatoria.size()-1);i++) 
        soma += matriz_dist[solucaoAleatoria[i]][solucaoAleatoria[i+1]];
    
    // somar a distância da ultima cidade na solucao ate a cidade 0
    soma += matriz_dist[solucaoAleatoria[solucaoAleatoria.size()-1]][0];
    
    return soma;
}