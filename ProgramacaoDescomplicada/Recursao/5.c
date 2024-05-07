#include <stdio.h>

int fibonacci(int ultimo, int penultimo, int count) {
    if(count == 0) return ultimo+penultimo;
    return fibonacci(penultimo, ultimo+ penultimo, count-1);
}

int main() {
    printf("%d\n",fibonacci(0, 1, 7-3));
}