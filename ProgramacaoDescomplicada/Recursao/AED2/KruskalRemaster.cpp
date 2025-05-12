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
    int matrix[21][21] = {0}, tam, aux, i, j, v[21]={0}, treeCount = 0, treeOne = 0, foo, tempNodeA, tempNodeB, tempWeight;

    //A ideia é criar um sequencia de peso, nodo A e nodo B para cada arresta
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

        // por praticidade de não ter que digitar edges.front().(...)
        tempNodeA = edges.front().second.first;
        tempNodeB = edges.front().second.second;
        tempWeight = edges.front().first;

        //impede que adicione uma arresta entre nodos da mesma subarvore para não criar ciclos
        if(tempNodeA == 0 || tempNodeA != tempNodeB) {

            // salva a arresta na matriz
            matrix[tempNodeA][tempNodeB] = tempWeight;
            matrix[tempNodeB][tempNodeA] = tempWeight;

            // se nenhum dos nodos está em uma subarvore, cria uma e adiciona os dois   
            if(v[tempNodeA] == 0 && v[tempNodeB] == 0){
                treeCount++;
                v[tempNodeA] = treeCount;
                v[tempNodeB] = treeCount;
                if(treeCount == 1) treeOne += 2;
            // se apenas um está, adiciona oque não está nela
            } else if(v[tempNodeA] == 0) {
                v[tempNodeA] = v[tempNodeB];
                if(v[tempNodeA == 1]) treeOne++;
            } else if(v[tempNodeB] == 0) {
                v[tempNodeB] = v[tempNodeA];
                if(v[tempNodeA == 1]) treeOne++;
            // se ambos estão em subarvores, adiciona todos os nodos da subarvore de numero maior na menor
            } else {
                aux = min(tempNodeA, tempNodeB);
                foo = max(tempNodeA, tempNodeB);

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
    printf("\n\n\n");
    //printa matrix de adjacencia da msp
    for(i = 0; i < tam; i++) {
        for(j = 0; j < tam; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}