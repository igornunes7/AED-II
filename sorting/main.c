#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>

void CheckFileStatus(FILE *file)
{
    if (!file) {
        printf("ERRO %s!\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
}

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

void mergeSort(int32_t *L, int32_t *Tmp, int esq, int dir){

    if(esq < dir){
        int centro = (esq + dir) / 2;
        mergeSort(L, Tmp, esq, centro);
        mergeSort(L, Tmp, centro + 1, dir);

        intercalar(L, Tmp, esq, centro + 1, dir);
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

void randomElementQuickSort(int32_t *L, int ini, int fim){
    int i, j, key;

    if(fim - ini < 2){
        if(fim - ini == 1){
            if(L[ini]>L[fim])
                auxSwap(&L[ini], &L[fim]);
        }
    }
    else{
        srand(time(NULL));
        int random = ini + rand() % (fim-ini); 
        
        auxSwap(&L[random], &L[fim]);
        i = ini;
        j = fim-1;
        key = L[fim];

        while(j>=i){
            while(L[i] < key)
                i = i + 1;
            while(j >= ini && L[j] >= key) 
                j = j - 1;

            if(j>=i) {
                auxSwap(&L[i], &L[j]);
                i = i + 1;
                j = j - 1;
            }
        }
        auxSwap(&L[i], &L[fim]);
        
        if(ini < i-1) {
            randomElementQuickSort(L, ini, i - 1);
        }
        if(i+1 < fim) {
            randomElementQuickSort(L, i + 1, fim);
        }
            
    }
}

//função para obter o pivô do array por mediana
void pivo(int32_t *L, int ini, int fim, int *mediana){
    int mid = floor((ini+fim)/2);

    if((L[ini] > L[mid]) ^ (L[ini] > L[fim])) {
        *mediana = ini;
    }
    else if((L[mid] < L[ini]) ^ (L[mid] < L[fim])) {
        *mediana = mid;
    }
    else {
        *mediana = fim; 
    }
    
}

void medianQuickSort(int32_t *L, int ini, int fim){
    int i, j, key;

    if(fim - ini < 2){
        if(fim - ini == 1){
            if(L[ini]>L[fim])
                auxSwap(&L[ini], &L[fim]);
        }
    }
    else{
        int mediana;

        pivo(L, ini, fim, &mediana);
        auxSwap(&L[mediana], &L[fim]);
        i = ini;
        j = fim-1;
        key = L[fim];

        while(j>=i){
            while(L[i] < key)
                i++;
            while(L[j] > key)
                j--;

            if(j>i){
                auxSwap(&L[i], &L[j]);
                i++;
                j--;
            }
            else
                break;
        }
        auxSwap(&L[i], &L[fim]);

        medianQuickSort(L, ini, i-1);
        medianQuickSort(L, i+1, fim); 
    }
}


void descer(int32_t *L, int i, int n){
    int j = 2 * i;

    if(j <= n){
        if(j < n){
            if(L[j+1] > L[j])
                j = j + 1;
        }
        if(L[i] < L[j]){
            auxSwap(&L[i], &L[j]);
            descer(L, j, n);
        }
    }
}

void arranjar(int32_t *L, int n){
    for(int i = n/2; i >= 0; i--)
        descer(L, i, n-1);
}


void heapSort(int32_t *L, int n){
    arranjar(L, n);
    int m = n - 1;

    while(m >= 0){
        auxSwap(&L[0], &L[m]);
        m = m - 1;
        descer(L, 0, m);
    }
}


int main(int argc, char *argv[]){
    if(argc == 4){
        unsigned short op = atoi(argv[1]);
        char *inArchName, *outArchive;

        inArchName = argv[2];
        outArchive = argv[3];

        int i = 0, sizeOfArray;

        clock_t begin, end;

        FILE *inputFile = fopen(inArchName, "rb");

        CheckFileStatus(inputFile);

        sizeOfArray = getArraySize(inputFile);
        int32_t *array = (int32_t*) malloc(sizeOfArray * sizeof(int32_t)); 
        int32_t *temp = (int32_t*) malloc(sizeOfArray * sizeof(int32_t)); 

            
        int32_t n;
        int index = 0;
        while (fread(&n, sizeof(int32_t), 1, inputFile)) {
            array[index++] = n;
        }  
           
        fclose(inputFile);

        srand(time(NULL));

        printf("SORTING_PROCESSING\n");
        switch(op){
            case 1:
                printf("1.Bubble-sort original\n");

                begin = clock();
                originalBubbleSort(array, sizeOfArray);
                end = clock();

                break;
            case 2:
                printf("2.Bubble-sort melhorado\n");

                begin = clock();
                betterBubbleSort(array, sizeOfArray);
                end = clock();

                break;
            case 3:
                printf("3.Insertion-sort\n");

                begin = clock();
                insertionSort(array, sizeOfArray);
                end = clock();

                break;
            case 4:
                printf("4.Mergesort\n");

                begin = clock();
                mergeSort(array, temp, 0, sizeOfArray-1);
                end = clock();

                break;
            case 5:
                printf("5.Quicksort com pivô sendo o último elemento\n");

                begin = clock();
                lastElementQuickSort(array, 0, sizeOfArray-1);
                end = clock();

                break;
            case 6:
                printf("6.Quicksort com pivô sendo um elemento aleatório\n");

                begin = clock();
                randomElementQuickSort(array, 0, sizeOfArray-1);
                end = clock();

                break;
            case 7:
                printf("7.Quicksort com pivô sendo a mediana de três\n");

                begin = clock();
                medianQuickSort(array, 0, sizeOfArray-1);
                end = clock();

                break;
            case 8:
                printf("8.Heapsort\n");

                begin = clock();
                heapSort(array, sizeOfArray);
                end = clock();

                break;
            default:
                printf("Algoritmo inválido!\n");
                return 0;
        }

        FILE *outputFile = fopen(outArchive, "wb");
        CheckFileStatus(outputFile);

        fwrite(array, sizeof(int32_t), sizeOfArray, outputFile);
        fclose(outputFile);

        free(array);

        double timeSpent = 0.0;
        timeSpent += (double)(end-begin) / CLOCKS_PER_SEC;
        
        printf("Array ordenado!\n");
        printf("O tempo de execução do algoritmo [%hu] foi de %.3f segundos.\n", op, timeSpent);
    }
    else
        printf ("usage: ./<file name> <numero alg> <nome arq> <nome arq saida>\n");

    return 0;
}
