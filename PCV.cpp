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

    for(int i=0;i<N;i++) {
        printf("%d - (%f, %f)\n",i, pontos[i].first, pontos[i].second);
    }
}

PCV::~PCV() {
    f.close();
}