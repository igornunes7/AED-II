#include "gfx.h"
#include <stdio.h>
#include <unistd.h>


#define TAM 600


//Função para print
void printRec () {
    printf ("Escolha o nivel de recursao (0 - 10): \n");
}


//Função para fazer o circulo recursivo
void draw_circle(int centerX, int centerY, int radiusX, int radiusY, int levels) {

    gfx_ellipse(centerX, centerY, radiusX, radiusY);


    //condição de parada
    if (levels == 0) {
        return;
    }


    //coloca o centro X para círculo à direita
    int x2 = centerX + (radiusX/2 * 0.7); 

    //coloca o centro X para círculo à esquerda
    int x1 = x2 + (centerX - x2) * 2;  

    //leva o entro Y para baixo
    int y1 = centerY + (radiusY/2 * 0.7); 

    //leva o centro Y para cima
    int y2 = y1 + (centerY - y1) * 2;      


    //divide o raio de x e y por 2 para ir diminuindo
    int smaller_radiusX = radiusX / 2;
    int smaller_radiusY = radiusY / 2;


    if (levels > 0) {
        //quadrante superior esquerdo
        draw_circle(x1, y2, smaller_radiusX, smaller_radiusY, levels - 1); 
        
        //quadrante superior direito
        draw_circle(x2, y2, smaller_radiusX, smaller_radiusY, levels - 1); 

        //quadrante inferior esquerdo
        draw_circle(x1, y1, smaller_radiusX, smaller_radiusY, levels - 1); 

        //quadrante inferior direito
        draw_circle(x2, y1, smaller_radiusX, smaller_radiusY, levels - 1); 
    }

}

//Função para fazer o quadrado recursivo
void draw_square(int x, int y, int size, int levels){

    if(levels > 0) {
        //quadrado cima
        draw_square(x + size / 2, y - size, size / 2, levels - 1);

        //quadrado baixo
        draw_square(x + size / 2, y + size * 2, size / 2, levels - 1);

        //quadrado direita
        draw_square(x + size * 2, y + size / 2, size / 2, levels -1) ;

        //quadrado esquerda
        draw_square(x - size, y + size/2, size / 2, levels - 1);
    }

    gfx_set_color(200, 100, 200);

    gfx_rectangle(x, y, x+size*2, y+size*2);

    gfx_set_color(0, 0, 0);

    gfx_filled_rectangle(x + 1, y + 1, x + size*2 - 1, y + size*2 - 1); //evitando o quadrado dentro de quadrado
    if (levels == 0) {
        return;
    }
}



int main() {
    int op, rec_level;
    int initial_centerX = 300;
    int initial_centerY = 300;
    int initial_radiusX = 256;
    int initial_radiusY = 256;
    int inicialX = 200;
    int inicialY = 200;
    int inicialSize = 100;

    while (1) {
        printf ("Escolha qual formato você quer:\n1 - CIRCULO\n2 - QUADRADO\n3 - SAIR\n");
        scanf ("%d" , &op);

        if (op == 3) {
            printf ("Saindo...\n");
            sleep (2);
            break;
        }

        while (1) {
            printRec();
            scanf ("%d" , &rec_level);

            if (rec_level > -1 && rec_level < 11) {
                break; 
            }
            else {
                printf("Apenas valores entre 0 - 10\n");
            }
        }
        
        if (op == 1) {
            gfx_init(TAM, TAM, "Círculo");
            gfx_set_color(200, 100, 200);
            draw_circle(initial_centerX, initial_centerY, initial_radiusX, initial_radiusY, rec_level);
        }

        if (op == 2) {
            gfx_init(TAM, TAM, "Quadrado");
            gfx_set_color(200, 100, 200);
            draw_square(inicialX, inicialY, inicialSize, rec_level);
        }
        
        gfx_paint();
        sleep(2);
        gfx_quit();
    } 


    return 0;
}
