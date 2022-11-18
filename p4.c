#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "monticulo.h"


void inicializar_semilla();
double microsegundos();
void randVector(int v [], int n);
void test();


int main() {
    test();
    return 0;
}


void inicializar_semilla() {
    srand(time(NULL));
}


double microsegundos() {
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0)
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void randVector(int v [], int n) {   /* se generan números pseudoaleatorio entre -n y +n */
    int i, m=2*n+1;
    for (i=0; i < n; i++)
        v[i] = (rand() % m) - n;
}


void test(){
    monticulo m1;
    int v[15] = {8, 7, 23, 11, 0, 5, 5, 3, 9, 10, 1, 26, 9, 2, 3};
    int n = 15;
    crear_monticulo(v, n, &m1);
    for (int i = 0; i < 15; ++i) {
        printf("%4d", m1.vector[i]);
    }
    printf("\n");
    eliminar_mayor(&m1);
    for (int i = 0; i < 14; ++i) {
        printf("%4d", m1.vector[i]);
    }
    printf("\n");

}