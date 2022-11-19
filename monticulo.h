#include <stdbool.h>

#ifndef P4_MONTICULO_H
#define P4_MONTICULO_H

#endif //P4_MONTICULO_H

#define TMAX 512000

typedef struct {
    int vector[TMAX];
    int tamanhoMont;
} monticulo;

void init_monticulo(monticulo *m);
bool esMonticuloVacio(monticulo m);
void insert (int a, monticulo *m);
void crear_monticulo(const int [], int, monticulo *m);
int eliminar_mayor(monticulo *m);
void ord_monticulos(int v[], int n);