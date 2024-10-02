#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>


int getArraySize(FILE *arq) {
    struct stat statbuf;
    
    if (fstat(fileno(arq), &statbuf) == -1) {
        perror("Erro ao obter tamanho do arquivo");
        exit(EXIT_FAILURE);
    }

    int tam = statbuf.st_size / sizeof(int32_t);
    return tam;
}


void auxSwap(int32_t *a, int32_t *b){
    int32_t aux;
    aux = *a;
    *a = *b;
    *b = aux; 
}


void originalBubbleSort (int32_t *L, int n) {
    for (int i = 0; i < n; i++) {
        for(int j = 0; j < n - 1; j++) {
            if (L[j] > L[j + 1]) {
                auxSwap (&L[j] , &L[j + 1]);
            }
        }
    }
}


//reparar esse aqui
void betterBubbleSort (int32_t *L, int n) {
    bool mudou = true; 
    int auxN = n - 1, guarda = n;
    int j;

    while (mudou) {
        j = 0;
        mudou = false;

        while (j < auxN) {
            if (L[j] > L[j + 1]) {
                auxSwap(&L[j] , &L[j + 1]);
                mudou = true;
                guarda = j;
            }
            j = j + 1;
        }

        auxN = guarda;
    }
}

void insertionSort (int32_t *L, int n) {
    int32_t prov, valor;
    int j;
    for (int i = 1; i < n; i++) {
        prov = L[i];
        valor = L[i];
        j = i - 1;

        while (j >= 0 && valor < L[j]) {
            L[j + 1] = L[j];
            j = j - 1;
        }

        L[j + 1] = prov;
    }
}




void mergeSort(int32_t *L, int32_t *Tmp, int esq, int dir){

    if(esq < dir){
        int centro = (esq + dir) / 2;
        mergeSort(L, Tmp, esq, centro);
        mergeSort(L, Tmp, centro + 1, dir);

        intercalar(L, Tmp, esq, centro + 1, dir);
    }
}


void intercalar (int32_t *L, int32_t *Tmp, int ini1, int ini2, int fim2) {
    int fim1 = ini2 - 1;
    int nro = 0;
    int ind = ini1;
    int auxIni1 = ini1;

    while (ini1 <= fim1 && ini2 <= fim2) {
        if (L[ini1] < L[ini2]) {
            Tmp[ind] = L[ini1];
            ini1 = ini1 +1;
        } else {
            Tmp[ind] = L[ini2];
            ini2 = ini2 + 1;
        }

        ind = ind + 1;
        nro = nro + 1;
    }

    while (ini1 <= fim1) {
        Tmp[ind] = L[ini1];
        ini1 = ini1 + 1;
        ind = ind + 1;
        nro = nro + 1;
    }

    while (ini2 <= fim2) {
        Tmp[ind] = L[ini2];
        ini2 = ini2 + 1;
        ind = ind + 1;
        nro = nro + 1;
    }

    for (int i = 0; i < nro; i++) {
        L[i + auxIni1] = Tmp[i + auxIni1];
    }
}

void lastElementQuickSort(int32_t *L, int ini, int fim){
    int i, j, key;

    if(fim - ini < 2){
        if(fim - ini == 1){
            if(L[ini] > L[fim]) {
                auxSwap(&L[ini], &L[fim]);
            }
        }
    }
    else {
        i = ini, j = fim - 1;
        key = fim;

        while(j >= i){
            while(L[i] < L[key])
                i = i + 1;
            while(j >= ini && L[j] >= L[key])
                j = j - 1;

            if(j >= i){
                auxSwap(&L[i], &L[j]);
                i = i + 1;
                j = j + 1;
            }
        }
        auxSwap(&L[i], &L[key]);

        if(ini < i-1) {
            lastElementQuickSort(L, ini, i - 1);
        }
        if(i + 1 < fim) {
            lastElementQuickSort(L, i + 1, fim);
        }
    }
}   



int main() {

}
