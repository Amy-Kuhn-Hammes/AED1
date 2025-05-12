#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include <string.h>
using std::vector;

int p(int *c, int pos, int in) {
    if(pos != in)
        p(c, c[pos], in);
    printf("%d ", pos);
}

int main() {
    int matrix[21][21], v[21] = {0}, c[21] = {0}, tam, in, out;
    vector<int> fifo;
    memset(v, -1, sizeof(v));

    //insira a quantidades de nodos

    scanf("%d", &tam);
    //insira uma matriz de adjacencia 
    for(int i = 0; i < tam; i++) {
        for(int j = 0; j < tam; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    //insira o começo e o fim
    scanf("%d %d", &in, &out);

    fifo.push_back(in);

    while(!fifo.empty()) {
        for(int i = 0; i < tam; i++) {
            if(matrix[fifo.front()][i] != 0) {
                if(v[i] == -1 || v[i] > v[fifo.front()] + matrix[fifo.front()][i]) {
                    v[i] =  v[fifo.front()] + matrix[fifo.front()][i];
                    c[i] = fifo.front();
                    fifo.push_back(i);
                }
            }
        }
        fifo.erase(fifo.begin());
    }

    printf("caminho mais curto: %d\n", v[out]);
    printf("caminho: ");
    p(c, out, in);
    printf("\n");

}