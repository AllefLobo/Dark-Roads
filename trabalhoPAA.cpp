// implementação do problema dark roads
// author:  Allef Lobo, Françoes Pereira
//Data: 10/07/16

#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <vector>
#define MAXIMUM 200000

using namespace std;

int n, m; // rotas e juncoes
int pai[MAXIMUM];
vector <pair <int, pair <int,int> > > grafo ;// vector de arestas - peso primeiro segundo

 // busca pai
//Este trecho possui complexidade O(n) no pior caso, podendo amortizar para tempo constante
int find(int a) {
    if (pai[a] == a) return a;
    return pai[a] = find(pai[a]);
}

 // unir os conjuntos
//Por utilizar find mutiplas vezes, esse treho  term sua complexidade  amortizada para tempo constante
void join(int a, int b) {
  if ( pai[find(a)] > pai[find(b)] ) {
    pai[find(b)] = pai[find(a)];
  }else{
    pai[find(a)] = pai[find(b)];
  }
}

//Este trecho apresenta complexidade constante para realizar o acesso e a compraçao
bool funcaoParaSort(pair <int, pair <int,int> >  i, pair <int, pair <int,int> >  j){ // logica do sort
  return i.first < j.first;
};

//Este trecho possui complexidade O(m log n)  tendo como peso maior a ordenaçao
//As demais estrutas  dentro dessa funçao, possuem complexidade trivialmente lineares ou constantes
int kruskal(){ // kruskal
  int primeiro, segundo, peso, soma = 0;
  for (int j = 0; j < m; j++) {
    pai[j] = j;
  }
  sort(grafo.begin(), grafo.end(), funcaoParaSort); // ordenacao em ordem nao descrescente
  for (int k = 0; k < grafo.size(); k++) {
    primeiro = (grafo[k].second).first;
    segundo = (grafo[k].second).second;
    peso = grafo[k].first;
    if ( find(primeiro) != find(segundo) ) {
      join(primeiro, segundo);
      soma = soma + peso;
    }
  }
  return soma;
}

int main() { // preencho o grafo e chamo o algoritmo kruskal
  int tamGrafo = 0;
  int lucro;
  int primeiro, segundo, peso;

  scanf("%d %d", &m, &n ); // m - juncoes / n - rotas
  for (int i = 0; i < n; i++) {
    scanf("%d %d %d\n", &primeiro, &segundo, &peso);
    grafo.push_back( make_pair(peso, make_pair(primeiro, segundo) ) )  ;
    tamGrafo += peso;
  }
  printf("%d\n", tamGrafo - kruskal() );

  return 0;
}
