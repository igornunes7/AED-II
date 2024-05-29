#include <stdio.h>
#include <stdlib.h>
#include "gfx.h"
#include <unistd.h>

struct s_no {
    int num;
    struct s_no *prox;
};

typedef struct s_no s_no;


struct s_no_duplo {
    int num;
    struct s_no_duplo *prox;
    struct s_no_duplo *ant;
};

typedef struct s_no_duplo s_no_duplo;


//função para criar um nó cabeça para lista dupla encadeada
void criarNoCabeca(s_no_duplo **ptlista) {
    if (*ptlista == NULL) {
        *ptlista = malloc(sizeof(s_no_duplo));
        if (*ptlista == NULL) {
            printf ("Erro ao alocar");
            return;
        }
        (*ptlista)->num = -1; 
        (*ptlista)->prox = NULL;
        (*ptlista)->ant = NULL;
    }
}

void opcoes() {
    printf ("1 - Lista simplesmente encadeada sem nó cabeça ordenada\n2 - Lista circular simplesmente encadeada sem nó cabeça ordenada\n3 - Lista duplamente encadeada com nó cabeça\n4 - FILA\n5 - PILHA\n");
}

void menu() {
    printf("1 - Buscar\n2 - Inserir\n3 - Remover\n0 - Sair\n");
}

void menuFila_Pilha () {
    printf("1 - Inserir\n2 - Remover\n0 - Sair\n");
}



//desenha a fila
void desenharFila(s_no *topo) {
    gfx_clear();
    gfx_paint();
    int x = 50, y = 100; 
    int nodeWidth = 50, nodeHeight = 30; 
    int spacing = 20; 
    int arrowStartX = x + nodeWidth;
    int arrowStartY = y + nodeHeight / 2;
    int arrowEndX = arrowStartX + spacing;

    //seta para o lado direito
    gfx_line(arrowStartX, arrowStartY, arrowEndX, arrowStartY);
    gfx_line(arrowEndX, arrowStartY, arrowEndX - 5, arrowStartY - 5);
    gfx_line(arrowEndX, arrowStartY, arrowEndX - 5, arrowStartY + 5);


    x += nodeWidth + spacing;
    while (topo != NULL) {
        //desenhando o retangulo do no
        gfx_rectangle(x, y, x + nodeWidth, y + nodeHeight);
        char valor[10];
        //escrevendo o valor dentro do retangulo
        sprintf(valor, "%d", topo->num);
        gfx_text(x + 20, y + 8, valor);


        if (topo->prox != NULL) {
            arrowStartX = x + nodeWidth;
            arrowStartY = y + nodeHeight / 2;
            arrowEndX = arrowStartX + spacing;
            gfx_line(arrowStartX, arrowStartY, arrowEndX, arrowStartY);
            gfx_line(arrowEndX, arrowStartY, arrowEndX - 5, arrowStartY - 5);
            gfx_line(arrowEndX, arrowStartY, arrowEndX - 5, arrowStartY + 5);
        }

       
        x += nodeWidth + spacing;
        topo = topo->prox;
    }

    gfx_paint(); 
}

//desenha a pilha
void desenharPilha(s_no *topo) {
    gfx_clear();
    gfx_paint();
    int x = 50, y = 100; 
    int nodeWidth = 50, nodeHeight = 30; 
    int spacing = 20; 
    int arrowStartX = x + nodeWidth / 2;
    int arrowStartY = y + nodeHeight;
    int arrowEndX = arrowStartX;
    int arrowEndY = arrowStartY + spacing;

    //desenhando a primeita seta para baixo (com a pilha vazia)
    gfx_line(arrowStartX, arrowStartY, arrowEndX, arrowEndY);
    gfx_line(arrowEndX, arrowEndY, arrowEndX - 5, arrowEndY - 5);
    gfx_line(arrowEndX, arrowEndY, arrowEndX + 5, arrowEndY - 5);
    y += nodeHeight + spacing;
    while (topo != NULL) {
        //desenhando o retangulo do no
        gfx_rectangle(x, y, x + nodeWidth, y + nodeHeight);
        char valor[10];
        //escrevendo o valor dentro do retangulo
        sprintf(valor, "%d", topo->num);
        gfx_text(x + 20, y + 8, valor);

        if (topo->prox != NULL) {
            //desenha seta para baixo
            arrowStartX = x + nodeWidth / 2;
            arrowStartY = y + nodeHeight;
            arrowEndX = arrowStartX;
            arrowEndY = arrowStartY + spacing;
            gfx_line(arrowStartX, arrowStartY, arrowEndX, arrowEndY);
            gfx_line(arrowEndX, arrowEndY, arrowEndX - 5, arrowEndY - 5);
            gfx_line(arrowEndX, arrowEndY, arrowEndX + 5, arrowEndY - 5);
        }

        y += nodeHeight + spacing;
        topo = topo->prox;
    }

    gfx_paint(); 
}


//desenha a lista simplesmente encadeada sem nó cabeça ordenada circular
void desenharListaSimpOrdOrdCirc(s_no *ptlista) {
    gfx_clear();
    gfx_paint();
    
    if (ptlista == NULL) {
        return;
    }

    s_no *ptr = ptlista;

    gfx_clear();
    int startX = 50, startY = 100;
    int x = startX, y = startY;
    int verticalLine = 50;
    int nodeWidth = 50, nodeHeight = 30;
    int spacing = 20;
    int arrowStartX = x + 50; 
    int arrowStartY = y + 15; 
    int arrowEndX = arrowStartX + spacing;
    int firstNodeX = startX; 
    int firstNodeY = startY; 
    int arrowEndX_2 = firstNodeX - spacing;
    int arrowEndY_2 = firstNodeY + verticalLine;
    
    do {
        nodeWidth = 50;
        nodeHeight = 30;
        spacing = 20;

        gfx_rectangle(x, y, x + nodeWidth, y + nodeHeight);
        char valor[10];
        sprintf(valor, "%d", ptr->num);
        gfx_text(x + 20, y + 8, valor);
        arrowStartX = x + 50; 
        arrowStartY = y + 15; 
        arrowEndX = arrowStartX + spacing;

        
        if (ptr->prox != ptlista) {
            //desenha seta para direita
            gfx_line(arrowStartX, arrowStartY, arrowEndX, arrowStartY);
            gfx_line(arrowEndX, arrowStartY, arrowEndX - 5, arrowStartY - 5);
            gfx_line(arrowEndX, arrowStartY, arrowEndX - 5, arrowStartY + 5);
        } 

        if (ptr->prox == ptlista) {
            //seta do último No para o primeiro No
            firstNodeX = startX; 
            firstNodeY = startY; 
            arrowEndX_2 = firstNodeX - spacing;
            arrowEndY_2 = firstNodeY + verticalLine;

            //linha vertical para baixo
            gfx_line(arrowStartX, arrowStartY, arrowStartX, arrowEndY_2);
                    
            //linha horizontal para a esquerda
            gfx_line(arrowStartX, arrowEndY_2, arrowEndX_2, arrowEndY_2);

            //linha vertical para cima
            gfx_line(arrowEndX_2, arrowEndY_2, arrowEndX_2, firstNodeY + nodeHeight / 2);
                
            //linha para direita
            gfx_line(arrowEndX_2, firstNodeY + nodeHeight / 2, firstNodeX, firstNodeY + nodeHeight / 2);

            //desenha a ponta da seta encostada no primeiro no
            gfx_line(firstNodeX, firstNodeY + nodeHeight / 2, firstNodeX - 5, firstNodeY + nodeHeight / 2 - 5);
            gfx_line(firstNodeX, firstNodeY + nodeHeight / 2, firstNodeX - 5, firstNodeY + nodeHeight / 2 + 5);
        }

        x += nodeWidth + spacing;
        ptr = ptr->prox;
    } while (ptr != ptlista); 



    gfx_paint();
}

//desenha a lista simplesmente encadeada sem nó cabeça ordenada
void desenharListaSimpOrd(s_no *ptlista) {
    gfx_clear();
    gfx_paint();
    int x = 50, y = 100; 
    int nodeWidth = 50, nodeHeight = 30; 
    int spacing = 20; 
    int arrowStartX = x + nodeWidth;
    int arrowStartY = y + nodeHeight / 2;
    int arrowEndX = arrowStartX + spacing;
    while (ptlista != NULL) {
        gfx_rectangle(x, y, x + nodeWidth, y + nodeHeight);
        char valor[10];
        sprintf(valor, "%d", ptlista->num);
        gfx_text(x + 20, y + 8, valor);


        if (ptlista->prox != NULL) {
            arrowStartX = x + nodeWidth;
            arrowStartY = y + nodeHeight / 2;
            arrowEndX = arrowStartX + spacing;
            gfx_line(arrowStartX, arrowStartY, arrowEndX, arrowStartY);
            gfx_line(arrowEndX, arrowStartY, arrowEndX - 5, arrowStartY - 5);
            gfx_line(arrowEndX, arrowStartY, arrowEndX - 5, arrowStartY + 5);
        }

       
        x += nodeWidth + spacing;
        ptlista = ptlista->prox;
    }

    gfx_paint(); 
}



//desenha a lista duplamente encadeada com nó cabeça 
void desenharListaDuplaEnc(s_no_duplo *ptlista) {
    //alocar nó cabeça
    if (ptlista == NULL) {
        ptlista = malloc(sizeof(s_no_duplo));
        (ptlista)->num = -1; 
        (ptlista)->prox = NULL;
        (ptlista)->ant = NULL;
    }

    gfx_clear();
    gfx_paint();
    int x = 50, y = 100; 
    int nodeWidth = 50, nodeHeight = 30; 
    int spacing = 20; 
    int arrowStartX = x + nodeWidth;
    int arrowStartY = y + nodeHeight / 2;
    int arrowEndX = arrowStartX + spacing;
    int prevArrowEndX = x - spacing;

    //desenha o no cabeça
    gfx_rectangle(x, y, x + nodeWidth, y + nodeHeight);
    char valor[10];
    sprintf(valor, "%d", ptlista->num);
    gfx_text(x + 20, y + 8, valor);

    //desenha a seta para frente após o no cabeça
    if (ptlista->prox != NULL) {
        arrowStartX = x + nodeWidth;    
        arrowStartY = y + nodeHeight / 2;
        arrowEndX = arrowStartX + spacing;
        gfx_line(arrowStartX, arrowStartY, arrowEndX, arrowStartY);
        gfx_line(arrowEndX, arrowStartY, arrowEndX - 5, arrowStartY - 5);
        gfx_line(arrowEndX, arrowStartY, arrowEndX - 5, arrowStartY + 5);
    }
    
    s_no_duplo *ptr = (ptlista)->prox;
    x += nodeWidth + spacing;

    while (ptr != NULL) {
        gfx_rectangle(x, y, x + nodeWidth, y + nodeHeight);
        char valor[10];
        sprintf(valor, "%d", ptr->num);
        gfx_text(x + 20, y + 8, valor);

        if (ptr->prox != NULL) {
            //seta para direita
            arrowStartX = x + nodeWidth;    
            arrowStartY = y + nodeHeight / 2;
            arrowEndX = arrowStartX + spacing;
            gfx_line(arrowStartX, arrowStartY, arrowEndX, arrowStartY);
            gfx_line(arrowEndX, arrowStartY, arrowEndX - 5, arrowStartY - 5);
            gfx_line(arrowEndX, arrowStartY, arrowEndX - 5, arrowStartY + 5);
        }

        //seta para esquerda
        prevArrowEndX = x - spacing;
        gfx_line(prevArrowEndX, arrowStartY, x, arrowStartY);
        gfx_line(prevArrowEndX, arrowStartY, prevArrowEndX + 5, arrowStartY - 5);
        gfx_line(prevArrowEndX, arrowStartY, prevArrowEndX + 5, arrowStartY + 5);


        ptr = ptr->prox;
        x += nodeWidth + spacing;
    }

    gfx_paint(); 
}



//busca em uma lista simplesmente encadeada sem nó cabeça ordenada
void buscaListaSimpOrd(s_no *ptlista, int x) {
    s_no *ptr = ptlista;

    if (ptr == NULL) {
        printf("Lista vazia\n");
    } else {
        while (ptr != NULL) {
            if (x == ptr->num) {
                printf("Elemento encontrado\n");
                return;
            }
            ptr = ptr->prox;
        }
        printf("Elemento nao encontrado\n");
    }
}


//busca em uma lista simplesmente encadeada sem nó cabeça ordenada circular
void buscaListaSimpOrdCirc (s_no *ptlista, int x) {
    s_no *ptr = ptlista;

    if (ptr == NULL) {
        printf ("Lista Vazia\n");
    } else {
        if (ptr->num == x) {
            printf ("Elemento encontrado\n");
            return;
        } else {
            ptr = ptr->prox;

            while (ptr != ptlista) {
                if (ptr->num == x) {
                    printf ("Elemento encontrado\n");
                    return;
                }
                ptr = ptr->prox;
            }
        }
        printf ("Elemento nao encontrado\n");
    }
    
}


//busca em uma lista duplamente encadeada com nó cabeça 
void buscaListaDuplaEnc (s_no_duplo *ptlista , int x) {
    //alocar no cabeça
    if (ptlista == NULL) {
        ptlista = malloc(sizeof(s_no_duplo));
        (ptlista)->num = -1; 
        (ptlista)->prox = NULL;
        (ptlista)->ant = NULL;
    }


    s_no_duplo *ptr = (ptlista)->prox;

    //verifica se o proximo no do cabeça é nulo e se o valor a ser buscado é o valor do no cabeça
    if (ptr == NULL && x == -1) {
        printf("Elemento nao encontrado\n");
        return;
    }


    while (ptr != NULL) {
        if (x == ptr->num) {
            printf("Elemento encontrado\n");
            return;
        }
        ptr = ptr->prox;
    }
    printf("Elemento nao encontrado\n");
}



//inserção em uma pilha (inserção no inicio)
void inserirPilha (s_no **topo , int x) {
    s_no *novo = malloc(sizeof(s_no));
    novo->num = x;
    novo->prox = NULL;

    s_no *ptr = *topo;

    novo->prox = ptr;
    *topo = novo;
}


//inserção em uma fila (inserção no final)
void inserirFila (s_no **topo , int x) {
    s_no *novo = malloc(sizeof(s_no));
    novo->num = x;
    novo->prox = NULL;

    s_no *ptr = *topo;


    //verifica se a fila ta vazia
    if (ptr == NULL) {
        novo->prox = ptr;
        *topo = novo;
        return;
    }


    if (ptr != NULL) {
        while (ptr->prox != NULL) {
            ptr = ptr->prox;
        }

        novo->prox = NULL;
        ptr->prox = novo;
    }

}


//inserção em uma lista simplesmente encadeada sem nó cabeça ordenada
void inserirListaSimpOrd(s_no **ptlista, int x) {
    s_no *novo = malloc(sizeof(s_no));
    novo->num = x;
    novo->prox = NULL;

    s_no *ptr = *ptlista;
    s_no *aux = NULL; 


    //consegue colocar 2 valores iguais no inicio da lista
    if (ptr != NULL) {
        if (ptr->num == x) {
            novo->prox = ptr;
            ptr = novo;
            *ptlista = ptr;
            return;
        }
    }

    //insere na lista vazia ou no inicio dela
    if (ptr == NULL || x < ptr->num) {
        novo->prox = ptr;
        *ptlista = novo; 
        return;
    }


    while (ptr != NULL && x > ptr->num) {
        aux = ptr;
        ptr = ptr->prox;
    }

    novo->prox = ptr;
    aux->prox = novo;
}

//inserção em uma lista simplesmente encadeada sem nó cabeça ordenada circular
void inserirListaSimpOrdCirc(s_no **ptlista, int x) {
    s_no *novo = malloc(sizeof(s_no));
    novo->num = x;
    novo->prox = NULL;

    s_no *ptr = *ptlista;

    //lista vazia
    if (ptr == NULL) {
        novo->prox = novo; 
        *ptlista = novo; 
        return;
    }

    //primeiro elemento
    if (x < ptr->num) {
        while (ptr->prox != *ptlista) {
            ptr = ptr->prox;
        }
        ptr->prox = novo;
        novo->prox = *ptlista; 
        *ptlista = novo;
        return;
    }

    //primeiro elemento igual
    if (ptr->num == x) {
        while (ptr->prox != *ptlista) {
            ptr = ptr->prox;
        }
        ptr->prox = novo;
        novo->prox = *ptlista; 
        *ptlista = novo;
        return;
    }

    //varre a lista ate que chegue no inicio e o valor a ser inserido seja maior que o valor do proximo do ponteiro
    while (ptr->prox != *ptlista && x > ptr->prox->num) {
        ptr = ptr->prox;
    }
    
    novo->prox = ptr->prox; 
    ptr->prox = novo; 
}


//inserção em uma lista duplamente encadeada com nó cabeça 
void inserirListaDuplaEnc (s_no_duplo **ptlista, int x) {
    //alocar no cabeça
    if (*ptlista == NULL) {
        *ptlista = malloc(sizeof(s_no_duplo));
        (*ptlista)->num = -1; 
        (*ptlista)->prox = NULL;
        (*ptlista)->ant = NULL;
    }


    s_no_duplo *novo = malloc(sizeof(s_no_duplo));
    novo->num = x;
    novo->prox = NULL;
    novo->ant = NULL;

    s_no_duplo *ptr = *ptlista;

    //verifica se o proximo no dps do cabeça é nulo
    if (ptr->prox == NULL) {
        novo->prox = NULL;
        novo->ant = ptr;
        ptr->prox = novo;
        return;
    } else {
        while (ptr->prox != NULL) {
            ptr = ptr->prox;
        }

        novo->ant = ptr;
        ptr->prox = novo;
    }
}


//remoção em uma Pilha (remoção no inicio)
void removerPilha (s_no **topo) {
     if (*topo == NULL) {
        printf("Pilha vazia\n");
        return;
    }

    s_no *remover = NULL;
    s_no *ptr = *topo;

    *topo = ptr->prox;
    remover = ptr;
    free (remover);
}


//remoção em uma fila (remoção no inicio)
void removerFila (s_no **topo) {
    if (*topo == NULL) {
        printf("Fila vazia\n");
        return;
    }

    s_no *remover = NULL;
    s_no *ptr = *topo;

    *topo = ptr->prox;
    remover = ptr;
    free (remover);
}


//remoção em uma lista simplesmente encadeada sem nó cabeça ordenada
void removerListaSimpOrd(s_no **ptlista, int x) {
    if (*ptlista == NULL) {
        printf("Lista vazia\n");
        return;
    }

    s_no *remover, *aux = NULL;
    s_no *ptr = *ptlista;

    //varre a lista ate que chegue no final ou encontre o elemento
    while (ptr != NULL && ptr->num != x) {
        aux = ptr;
        ptr = ptr->prox;
    }

    //se nao encontrou o elemento
    if (ptr == NULL) {
		printf ("Elemento não existe na lista\n");
        return;
    }

    //verifica se o elemento a ser retirado é o primeiro da lista
    if (aux == NULL) {
        *ptlista = ptr->prox;
    } else {
        aux->prox = ptr->prox;
    }

    remover = ptr;
    free(remover);

}


//remoção em uma lista simplesmente encadeada sem nó cabeça ordenada circular
void removerListaSimpOrdCirc(s_no **ptlista, int x) {
    if (*ptlista == NULL) {
        printf("Lista vazia\n");
        return;
    }


    s_no *remover, *aux = NULL;
    s_no *ptr = *ptlista;

    //so há um elemento na lista
    if (ptr->prox == ptr && ptr->num == x) {
        *ptlista = NULL;
        remover = ptr;
        free (remover);
        return;
    }

    //ira fazer o loop ate ptr ser igual ao inicio da lista
    do {

        //verifica se encontrou o numero a ser retirado
        if (ptr->num == x) {

            //verifica se o elemento a ser retirado é o primeiro da lista
            if (aux == NULL) {
                aux = ptr;

                //faz aux chegar ate o ultimo elemento da lista
                do {
                    aux = aux->prox;
                } while (aux->prox != *ptlista);


                //nao fazer o ptlista apontar para um no que nao existe e garante que o ultimo no aponte para ptlista
                *ptlista = ptr->prox;
                aux->prox = *ptlista;
                remover = ptr;
                free(remover);
                return;

            //se o elemento a ser retirado não é o primeiro da lista
            } else {
                aux->prox = ptr->prox;
            }
            remover = ptr;
            free(remover);
            return;
        }
        aux = ptr;
        ptr = ptr->prox;
    } while (ptr != *ptlista);

    printf("Elemento nao encontrado na lista\n");
}


//remoção em uma lista duplamente encadeada com nó cabeça 
void removerListaDuplaEnc(s_no_duplo **ptlista, int x) {
    //alocar no cabeça
    if (*ptlista == NULL) {
        *ptlista = malloc(sizeof(s_no_duplo));
        (*ptlista)->num = -1; 
        (*ptlista)->prox = NULL;
        (*ptlista)->ant = NULL;
    }


    s_no_duplo *ptr = (*ptlista)->prox;
    s_no_duplo *remover = NULL;

    //verifica se o prox no do no cabeça é nulo e se quer remover o valor do no cabeça
    if (ptr == NULL && x == -1) {
        printf ("Elemento não existe na lista\n");
        return;
    }

    //verifica se a lista esta ''vazia'' (nao tem como estar vazia nunca pois tem o no cabeça)
    if (ptr == NULL) {
        printf ("Elemento não existe na lista\n");
        return;
    }

    
    while (ptr != NULL && ptr->num != x) {
        ptr = ptr->prox;
    }

    //verifica se encontrou o elemento
    if (ptr == NULL) {
        printf("Elemento não existe na lista\n");
        return;
    }


    //se o nó for o primeiro da lista
    if (ptr->ant == NULL) {

        //unico da lista
        if (ptr->prox == NULL) {
            *ptlista = ptr->prox;

        //nao unico da lista
        } else {
            ptr->prox->ant = NULL;
        }

    //ultimo nó da lista
    } else {
        ptr->ant->prox = ptr->prox;
    }


    //se o nó não for o último da lista
    if (ptr->prox != NULL) {
        ptr->prox->ant = ptr->ant;
    }

    remover = ptr;
    free(remover);
}


//desalocar a lista simplesmente encadeada sem nó cabeça ordenada
void desalocarListaSimpOrd(s_no **ptlista) {
    s_no *ptr = *ptlista;
    s_no *aux;

    while (ptr != NULL) {
        aux = ptr->prox;
        free(ptr);
        ptr = aux;
    }

    *ptlista = NULL; 
}


//desalocar a lista simplesmente encadeada sem nó cabeça ordenada circular
void desalocarListaSimpOrdCirc (s_no **ptlista) {
    s_no *ptr = *ptlista;
    s_no *aux;

    while (ptr != *ptlista) {
        aux = ptr->prox;
        free (ptr);
        ptr = aux;
    }
    
    *ptlista = NULL; 
}

//desalocar a lista duplamente encadeada com nó cabeça
void desalocarListaDuplaEnc (s_no_duplo **ptlista) {
    s_no_duplo *ptr = *ptlista;
    s_no_duplo *aux;

    ptr = ptr->prox;

    while (ptr != NULL) {
        aux = ptr->prox;
        free (ptr);
        ptr = aux;
    }

    *ptlista = NULL; 
}

//desalocar a fila
void desalocarFila (s_no **topo) {
    s_no *ptr = *topo;
    s_no *aux;

    while (ptr != NULL) {
        aux = ptr->prox;
        free(ptr);
        ptr = aux;
    }

    *topo = NULL; 
}


//desalocar a pilha
void desalocarPilha (s_no **topo) {
    s_no *ptr = *topo;
    s_no *aux;

    while (ptr != NULL) {
        aux = ptr->prox;
        free(ptr);
        ptr = aux;
    }

    *topo = NULL; 
}

int main() {
    s_no_duplo *lista2 = NULL;
    s_no *lista = NULL;
    int op, val, op2;

    gfx_init(1000, 800, "AEDII");

    opcoes();
    scanf ("%d" , &op);
    system ("clear");
    switch (op)
    {
    //lista simplesmente encadeada
    case 1:
        do {
            desenharListaSimpOrd(lista);
            menu();
            scanf ("%d" , &op2);
            system ("clear");
            switch (op2)
            {
            case 1:
                printf ("Digite o valor a ser buscado: ");
                scanf ("%d" , &val);
                buscaListaSimpOrd(lista , val);
                break;
                
            case 2:
                printf ("Digite o valor a ser inserido: ");
                scanf ("%d" , &val);
                inserirListaSimpOrd(&lista, val);
                system ("clear");
                break;
            case 3:
                printf ("Digite o valor a ser removido: ");
                scanf ("%d" , &val);
                removerListaSimpOrd(&lista, val);
                break;
            }
        } while (op2 != 0);
        desalocarListaSimpOrd (&lista);
        break;

    //lista simplesmente encadeada circular
    case 2:
        do {
            desenharListaSimpOrdOrdCirc(lista);
            menu();
            scanf ("%d" , &op2);
            system ("clear");
            switch (op2) 
            {
            case 1:
                printf ("Digite o valor a ser buscado: ");
                scanf ("%d" , &val);
                buscaListaSimpOrdCirc(lista , val);
                break;
            case 2:
                printf ("Digite o valor a ser inserido: ");
                scanf ("%d" , &val);
                inserirListaSimpOrdCirc(&lista, val);
                system ("clear");
                break;
            case 3:
                printf ("Digite o valor a ser removido: ");
                scanf ("%d" , &val);
                removerListaSimpOrdCirc(&lista, val);
                break;
            }
        } while (op2 != 0);
        desalocarListaSimpOrdCirc (&lista);
        break;

    //lista duplamente encadeada 
    case 3:
        criarNoCabeca(&lista2);
        do {
            desenharListaDuplaEnc(lista2);
            menu();
            scanf ("%d" , &op2);
            system ("clear");
            switch (op2) 
            {
            case 1:
                printf ("Digite o valor a ser buscado: ");
                scanf ("%d" , &val);
                buscaListaDuplaEnc(lista2 , val);
                break;
            case 2:
                printf ("Digite o valor a ser inserido: ");
                scanf ("%d" , &val);
                inserirListaDuplaEnc(&lista2, val);
                //system ("clear");
                break;
            case 3:
                printf ("Digite o valor a ser removido: ");
                scanf ("%d" , &val);
                removerListaDuplaEnc(&lista2, val);
                break;
            }

        } while (op2 != 0);
        desalocarListaDuplaEnc (&lista2);
        break;

    //fila
    case 4:
        do {
            desenharFila(lista);
            menuFila_Pilha();
            scanf ("%d" , &op2);
            system ("clear");
            switch (op2) 
            {
            case 1:
                printf ("Digite o valor a ser inserido: ");
                scanf ("%d" , &val);
                inserirFila(&lista, val);
                break;
            case 2:
                removerFila (&lista);
                break;
            }

        } while (op2 != 0);
        desalocarFila (&lista);
        break;


    //pilha
    case 5:
        do {
            desenharPilha(lista);
            menuFila_Pilha();
            scanf ("%d" , &op2);
            system ("clear");
            switch (op2) 
            {
            case 1:
                printf ("Digite o valor a ser inserido: ");
                scanf ("%d" , &val);
                inserirPilha (&lista , val);
                break;
            case 2:
                removerPilha (&lista);
                break;
            }

        } while (op2 != 0);
        desalocarPilha(&lista);
        break;
    default:
        break;
    }

    return 0;
}
