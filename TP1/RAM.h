#ifndef RAM_H
#define RAM_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int *memoria;
    int tam;
} Ram;

Ram* criarRam (int tamanho){
    Ram *ram = (Ram*) malloc (sizeof (Ram));
    int *memo = (int*) malloc (tamanho * sizeof(int));
    ram->memoria = memo;
    ram->tam = tamanho;
    return ram;
}

Ram* criarRam_vazia (int tamanho){
    Ram *ram_vazia = criarRam (tamanho);
    for (int i=0; i < tamanho; i++){
        ram_vazia->memoria[i] = 0;
    }
    return ram_vazia;
}

Ram* criarRam_aleatoria (int tamanho){
    Ram *ram_aleatoria = criarRam (tamanho);
    for (int i=0; i < tamanho; i++){
        ram_aleatoria->memoria[i] = rand();
    }
    return ram_aleatoria;
}

void setDado (Ram *ram, int endereco, int conteudo){
    ram->memoria[endereco] = conteudo;
}

int getDado (Ram *ram, int endereco){
    return ram->memoria[endereco];
}

void printRam (Ram *ram){
    printf ("CONTEUDO DA RAM\n");
    for (int i=0; i < ram->tam; i++){
        printf ("%d\n", ram->memoria[i]);
    }
}

Ram* liberarRam (Ram *ram){
    free ((ram)->memoria);
    free (ram);
    ram = NULL;
    return ram;
}

#endif