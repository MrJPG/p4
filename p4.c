#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include "monticulo.h"

#define VTEST 10

void inicializar_semilla();
double microsegundos();
void randVector(int v [], int n);
void vectorAsc(int v [], int n);
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

void vectorAsc(int v [], int n) {
    int i;
    for (i=0; i < n; i++)
        v[i] = i;
}

void test(){
    monticulo m1;
    int v[VTEST] = {0}, i, j;
    randVector(v, VTEST);
    printf("\nVector con el que formar el monticulo:\n\t");
    for (i = 0; i < VTEST; ++i) {
        printf("%4d", v[i]);
    }
    crear_monticulo(v, VTEST, &m1);
    printf("\nDistribucion de los elementos del monticulo:\n\t");
    for (i = 0; i < m1.tamanhoMont; ++i) {
        printf("%4d", m1.vector[i]);
    }
    for (i = VTEST; i > 0 ; --i) {
        eliminar_mayor(&m1);
        printf("\nMonticulo tras %d eliminaciones:\n\t", VTEST-i+1);
        for (j = 0; j < m1.tamanhoMont; ++j) {
            printf("%4d", m1.vector[j]);
        }
    }
    eliminar_mayor(&m1);
    printf("\n");
}