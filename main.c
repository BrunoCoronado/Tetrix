#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct{
    int x;
    int y;
    int estado;//0 si esta parado 1 si esta en movimiento(caida)
    int valor;
    int codigoPieza;
    int tipoPieza;
}bloque;

void inicializarTablero();
void mostarTablero();
void iniciarJuego();
void generarPieza();
void moverPiezas();

bloque tablero[16][8];
int velocidad = 3;
int piezaActual = -1;
int restoPiezaActual = 0;
int contadorPiezas = 0;
int codigoPiezaActual = -1;

int main() {
    srand(time(NULL));//seed para numeros aleatorios
    inicializarTablero();
    iniciarJuego();
    return 0;
}

void inicializarTablero(){
    for (int k = 0; k < 16; ++k) {
        for (int i = 0; i < 8; ++i){
            bloque tmp = { .codigoPieza = -1, .tipoPieza = -1, .estado = -1, .valor = 0, .x = i, .y = k };
            tablero[k][i] = tmp;
        }
    }
    /*for (int i = 0; i < 8; ++i)
        tablero[0][i].valor = 1;
    for (int i = 0; i < 8; ++i)
        tablero[4][i].valor = 2;*/
}

void mostarTablero(){
     for (int i = 0; i < 16; ++i) {
         for (int j = 0; j < 8; ++j)
             printf("%i", tablero[i][j].valor);
         printf("\n");
     }
    printf("\n");
}

void iniciarJuego(){
    int i = 0;
    while(i < 100){
        mostarTablero();
        if((i % 25) == 0){
            generarPieza();
        }
        moverPiezas();

        //capturar entrada
        /*char entrada[200];
        memset(&entrada[0], 0, sizeof(entrada));
        scanf(" %[^\n]", entrada);

        if(strcmp(entrada, "a") == 0){
            printf("\nMOVIMEINTO IZQUIERDA\n");
        } else if(strcmp(entrada, "d") == 0){
            printf("\nMOVIMEINTO DERECHA\n");
        } else if(strcmp(entrada, "w") == 0){
            printf("\nMAS VELOCIDAD\n");
            if(velocidad > 1){
                velocidad--;
            }
        } else if(strcmp(entrada, "s") == 0){
            printf("\nMENOS VELOCIDAD\n");
            if(velocidad < 5){
                velocidad++;
            }
        } else if(strcmp(entrada, "q") == 0){
            printf("\nROTACION\n");
        }*/

        sleep(velocidad);
        i++;
    }
}

int piezaPrueba = -1;

void generarPieza(){
    piezaActual = rand() % 7;
    int columnaInicio = rand() % 8;
    //printf("\nPIEZA -> %i\n", num);
    piezaPrueba++;
    switch (piezaPrueba){
        case 0: //pieza "|"
            restoPiezaActual = 3;
            //tablero[0][columnaInicio] = 1;
            /*tablero[0][columnaInicio].valor = 1;
            tablero[0][columnaInicio].tipoPieza = 1;
            tablero[0][columnaInicio].estado = 1;
            tablero[0][columnaInicio].codigoPieza = ++contadorPiezas;*/
            bloque barra = { .valor = 1, .tipoPieza = 0, .estado = 1, .codigoPieza = ++contadorPiezas, .y = 0, .x = columnaInicio };
            tablero[0][columnaInicio] = barra;
            codigoPiezaActual = contadorPiezas;
            break;
        case 1: //pieza "L"
            restoPiezaActual = 2;
            if (columnaInicio < 7){
                /*tablero[0][columnaInicio] = 1;
                tablero[0][columnaInicio + 1] = 1;*/

                bloque piezaL_A = { .valor = 1, .tipoPieza = 1, .estado = 1, .codigoPieza = ++contadorPiezas, .y = 0, .x = columnaInicio };
                bloque piezaL_B = { .valor = 1, .tipoPieza = 1, .estado = 1, .codigoPieza = ++contadorPiezas, .y = 0, .x = columnaInicio + 1 };
                tablero[0][columnaInicio] = piezaL_A;
                tablero[0][columnaInicio + 1] = piezaL_B;
                codigoPiezaActual = contadorPiezas;
            }
            break;
        case 2: //pieza "L" *invertida
            restoPiezaActual = 2;
            if (columnaInicio < 7){
                /*tablero[0][columnaInicio] = 1;
                tablero[0][columnaInicio + 1] = 1;*/
            }
            break;
        case 3: //pieza cubo
            restoPiezaActual = 1;
            if (columnaInicio < 7){
                /*tablero[0][columnaInicio] = 1;
                tablero[0][columnaInicio + 1] = 1;*/
            }
            break;
        case 4: //pieza T
            restoPiezaActual = 1;
            if (columnaInicio < 6){
                //tablero[0][columnaInicio + 1] = 1;
            }
            break;
        case 5: //pieza "Z" *invertida
            restoPiezaActual = 1;
            if (columnaInicio < 6){
                /*tablero[0][columnaInicio + 1] = 1;
                tablero[0][columnaInicio + 2] = 1;*/
            }
            break;
        case 6: //pieza "Z"
            restoPiezaActual = 1;
            if (columnaInicio < 6){
                /*tablero[0][columnaInicio] = 1;
                tablero[0][columnaInicio + 1] = 1;*/
            }
            break;
        default: break;
    }
}

void moverPiezas(){
    bloque tmp[16][8];
    for (int j = 0; j < 8; ++j){
        bloque vacio = { .codigoPieza = -1, .tipoPieza = -1, .estado = -1, .valor = 0, .x = j, .y = 0 };
        tmp[0][j] = vacio;
    }
    if(restoPiezaActual != 0) {//generar partes restantes de la pieza generada
        for (int j = 0; j < 8; ++j) {
            if (tablero[0][j].codigoPieza == codigoPiezaActual) {
                if (tablero[0][j].tipoPieza == 0) {
                    bloque barra = {.valor = 1, .tipoPieza = 0, .estado = 1, .codigoPieza = codigoPiezaActual, .y = 0, .x = j};
                    tmp[0][j] = barra;
                }else if(tablero[0][j].tipoPieza == 1){
                    bloque barra = {.valor = 1, .tipoPieza = 1, .estado = 1, .codigoPieza = codigoPiezaActual, .y = 0, .x = j};
                    tmp[0][j] = barra;
                }
                restoPiezaActual--;
            }
        }
    }
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 8; ++j){
            if(i < 15){
                tablero[i][j].y++;
                tmp[i + 1][j] = tablero[i][j];
            }
        }
    }
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 8; ++j)
            tablero[i][j] = tmp[i][j];
    }
}