#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <sys/time.h>
#include "monticulo.h"

#define VTEST 10
#define T 500
#define K 1000

void inicializar_semilla();
double microsegundos();
void randVector(int v [], int n);
void vectorAsc(int v [], int n);
void vectorDesc(int v [], int n);
void printHeader(void(*init)(int v[], int n));
void test();
void exeCreateMont();
void cotasCreateMont(double t, int n);
void exeOrdenacion(void(*init)(int v[], int n));


int main() {
    inicializar_semilla();
    test();
    exeCreateMont();
    exeOrdenacion(vectorAsc);
    exeOrdenacion(vectorDesc);
    exeOrdenacion(randVector);
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


void vectorDesc(int v [], int n) {
    int i;
    for (i=0; i < n; i++)
        v[i] = n-i-1;
}


void printHeader(void(*init)(int v[], int n)){
    if (init == vectorDesc){
        printf("\nAnalisis de ord_monticulos() con n elementos ordenados descendentemente:");
        printf("\n%11s%14s%14s%17s%15s","n","t(n)","t(n)/n","t(n)/n*log(n)","t(n)/n^1.4\n");
    }
    else if (init == randVector){
        printf("\nAnalisis de ord_monticulos() con n elementos aleatorios:");
        printf("\n%11s%14s%14s%17s%15s","n","t(n)","t(n)/n","t(n)/n*log(n)","t(n)/n^1.4\n");
    }
    else if (init == vectorAsc){
        printf("\nAnalisis de ord_monticulos() con n elementos ordenados ascendentemente:");
        printf("\n%11s%14s%14s%17s%15s","n","t(n)","t(n)/n","t(n)/n*log(n)","t(n)/n^1.4\n");
    }
}


void exeCreateMont(){
    monticulo m1;
    double ta, tb, t;
    int i, n, aux[TMAX]={0};
    printf("\nAnalisis de crear_monticulo() con n elementos:");
    printf("\n%11s%14s%14s%14s%15s","n","t(n)","t(n)/log(n)","t(n)/n","t(n)/n^1.2\n");
    for (n = 500; n <= TMAX; n *= 2) {
        vectorAsc(aux, n);
        ta = microsegundos();
        crear_monticulo(aux, n, &m1);
        tb = microsegundos();
        t = tb - ta;
        if(t < T){
            ta = microsegundos();
            for(i = 0; i < K; i++){
                crear_monticulo(aux, n, &m1);
            }
            tb = microsegundos();
            t = (tb - ta)/K;
            printf("  * ");
        }
        else printf("    ");
        cotasCreateMont(t, n);
    }
    printf("\n");
}


void cotasCreateMont(double t, int n) {
    double ci, ca, cs;
    ci = log(n), ca = n, cs = pow(n, 1.2);
    printf("%7d%14.3f%14.3f%14.4f%14.5f\n", n, t, t / ci, t / ca, t / cs);
}


void exeOrdenacion(void(*init)(int v[], int n)){
    double ta, tb, tc, t;
    double ci, ca, cs;
    int i, n, aux[512000]={0};
    printHeader(init);
    for (n = 500; n <= 512000; n *= 2) {
        init(aux, n);
        ta = microsegundos();
        ord_monticulos(aux, n);
        tb = microsegundos();
        t = tb - ta;
        if(t < T){
            ta = microsegundos();
            for(i = 0; i < K; i++){
                init(aux, n);
                ord_monticulos(aux, n);
            }
            tb = microsegundos();
            for(i = 0; i < K; i++){
                init(aux, n);
            }
            tc = microsegundos();
            t = ((tb-ta)-(tc-tb))/K;
            printf("  * ");
        }
        else printf("    ");
        ci = n, ca = n*log(n), cs = pow(n, 1.4);
        printf("%7d%14.3f%14.4f%17.4f%14.6f\n", n, t, t / ci, t / ca, t / cs);
    }
    printf("\n");
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
    ord_monticulos(v, VTEST);
    printf("\nOrdenacion del monticulo en un vector:\n\t");
    for (i = 0; i < m1.tamanhoMont; ++i) {
        printf("%4d", v[i]);
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