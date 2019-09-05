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