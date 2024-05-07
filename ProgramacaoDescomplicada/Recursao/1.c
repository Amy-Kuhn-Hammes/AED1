#include <stdio.h>

int somatorio(int atual, int sum) {
    if(atual == 0) return sum;
    return somatorio(atual-1, sum+atual);
}

int main() {
    printf("%d",somatorio(10, 0));
}