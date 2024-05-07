#include <stdio.h>

int somatorio(int count, int atual, int base) {
    if(count == 0) return atual;
    return somatorio(count-1, atual*base, base);
}

int main() {
    printf("%d",somatorio(5, 1, 2));
}