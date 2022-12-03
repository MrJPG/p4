#include <stdbool.h>

#define TMAX 512001

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