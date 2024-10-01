#ifndef DINAMICLIB_H
#define DINAMICLIB_H

#define CAPACIDAD_INICIAL 4

typedef struct vectorDinamico {
    int capacidad;
    int totalElementos;
    void **elementos;
} vectorDinamico;

void vectorInicio(vectorDinamico *V);
int totalVector(vectorDinamico *V);
void resizeVector(vectorDinamico *V, int capacidad);
void addVector(vectorDinamico *V, void *elemento);
void freeVector(vectorDinamico *V);
void *getVector(vectorDinamico *V, int indice);
void setVector(vectorDinamico *V, int indice, void *elemento);
void borrarVector(vectorDinamico *V, int indice);

#endif // DINAMICLIB_H
