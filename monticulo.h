//
// Created by alex on 17/11/22.
//

#ifndef P4_MONTICULO_H
#define P4_MONTICULO_H

#endif //P4_MONTICULO_H

#define TAM 512000
typedef struct {
    int vector[TAM];
    int ultimo;
} monticulo;
void crear_monticulo(int [], int, monticulo *);
int eliminar_mayor(monticulo *);