#include <stdio.h>

int somatorio(int atual, int fat) {
    if(atual == 1) return fat;
    return somatorio(atual-1, fat*atual);
}

int main() {
    printf("%d",somatorio(5, 1));
}