#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
using std::vector;
using std::pair;
using std::sort;

// função de minimo
int min(int a, int b) {
    if(a<b) return a;
    return b;
}

//função de maximo
int max(int a, int b) {
    if(a>b) return a;
    return b;
}


int main() {
    int matrix[21][21] = {0}, tam, aux, i, j, v[21]={0}, treeCount = 0, treeOne = 0, foo;

    //A ideia é criar um sequencia de peso, nodo A e nodo B para cada arresta
    pair<int, pair<int, int>> temp;
    vector<pair<int, pair<int,int>>> edges;


    //insira a quantidades de nodos
    scanf("%d", &tam);
    //insira uma matriz de adjacencia 
    for(i = 0; i < tam; i++) {
        for(j = 0; j < tam; j++) {
            scanf("%d", &aux);
            // considera só a parte superior da matriz para não adicionar arresta repetida 
            if(j < i && aux != 0) {
                edges.push_back({aux, {i, j}});
            }
        }
    }
    // ordena por tamanho 
    sort(edges.begin(), edges.end());

    //A ideia geral é ir criando subarvores e quando todos os nodos estivem na subarvore "1" acabar
    while(treeOne < tam || edges.empty()) {

        // por praticidade de não ter que digitar edges.front(), ter salvo em 3 variaveis temporarias teria sido melhor
        temp = edges.front();

        //impede que adicione uma arresta entre nodos da mesma subarvore para não criar ciclos
        if(temp.second.first == 0 || temp.second.first != temp.second.second) {

            // salva a arresta na matriz
            matrix[temp.second.first][temp.second.second] = temp.first;
            matrix[temp.second.second][temp.second.first] = temp.first;

            // se nenhum dos nodos está em uma subarvore, cria uma e adiciona os dois   
            if(v[temp.second.first] == 0 && v[temp.second.second] == 0){
                treeCount++;
                v[temp.second.first] = treeCount;
                v[temp.second.second] = treeCount;
                if(treeCount == 1) treeOne += 2;
            // se apenas um está, adiciona oque não está nela
            } else if(v[temp.second.first] == 0) {
                v[temp.second.first] = v[temp.second.second];
                if(v[temp.second.first == 1]) treeOne++;
            } else if(v[temp.second.second] == 0) {
                v[temp.second.second] = v[temp.second.first];
                if(v[temp.second.first == 1]) treeOne++;
            // se ambos estão em subarvores, adiciona todos os nodos da subarvore de numero maior na menor
            } else {
                aux = min(temp.second.first, temp.second.second);
                foo = max(temp.second.first, temp.second.second);

                for(i = 0; i < tam; i++) {
                    if(v[i] == foo) {
                        v[i] = aux;
                        if(aux == 1) treeOne++;
                    }
                }

            }
        }
        //remove primeiro da fila
        edges.erase(edges.begin(), edges.begin()+1);
    }
    
    //printa matrix de adjacencia da msp
    for(i = 0; i < tam; i++) {
        for(j = 0; j < tam; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}