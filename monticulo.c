#include "monticulo.h"
#include <stdbool.h>
#include <stdio.h>

void init_monticulo (monticulo *m){
    m->tamanhoMont = 0;
}

bool esMonticuloVacio (monticulo m){
    return m.tamanhoMont == 0;
}

void intercambiar(int *a, int *b){
    int temporal = *a;
    *a = *b;
    *b = temporal;
}

void flotar (int pos, monticulo *m){
    while(pos > 0 && m->vector[(pos-1)/2] < m->vector[pos]){
        intercambiar(&m->vector[(pos-1)/2], &m->vector[pos]);
        pos = (pos-1)/2;
    }
}

void insert (int a, monticulo *m){
    if (m->tamanhoMont == TMAX) printf("ERROR, monticulo lleno");
    else{
        m->vector[m->tamanhoMont] = a;
        flotar(m->tamanhoMont, m);
        m->tamanhoMont += 1;
    }
}

void hundir (int i, monticulo *m){
    int hIzq, hDer, j;
    do {
        hIzq = 2 * (i + 1) - 1;
        hDer = 2 * (i + 1);
        j=i;
        if(hIzq <= m->tamanhoMont && m->vector[hIzq] > m->vector[i]){
            i = hIzq;
        }
        if(hDer <= m->tamanhoMont && m->vector[hDer] > m->vector[i]){
            i = hDer;
        }
        intercambiar(&m->vector[j], &m->vector[i]);
    } while (i!=j);
}

void crear_monticulo(const int v[], int nElem, monticulo *m){
    int i;
    for(i=0; i < nElem; i++){
        m->vector[i] = v[i];
    }
    m->tamanhoMont = nElem;
    for (i = m->tamanhoMont/2; i >= 1; --i) {
        hundir(i-1, m);
    }
}

int eliminar_mayor(monticulo *m){
    int x;
    if (m->tamanhoMont == 0) printf("ERROR, monticulo vacio");
    else{
        x = m->vector[0];
        m->vector[0] = m->vector[m->tamanhoMont - 1];
        m->tamanhoMont = m->tamanhoMont - 1;
        if (m->tamanhoMont >= 0) hundir(0, m);
        return x;
    }
    return -1;
}

void ord_monticulos(int v[], int n){
    monticulo mc;
    int i;
    crear_monticulo(v, n, &mc);
    for (i = n; i > 0; --i) {
        v[i-1] = eliminar_mayor(&mc);
    }
}