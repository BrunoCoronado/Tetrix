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
void pararPieza(int codigoPieza);

bloque tablero[16][8];
int velocidad = 1;
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
     /*for (int i = 0; i < 16; ++i) {
         for (int j = 0; j < 8; ++j){
             printf("(%i,%i)", tablero[i][j].x, tablero[i][j].y);
         }
         printf("\n");
     }*/
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 8; ++j){
            printf("%i", tablero[i][j].valor);
        }
        printf("\n");
    }
    printf("\n");
}

void iniciarJuego(){
    int i = 0;
    while(i < 100){
        if(codigoPiezaActual == -1){
            generarPieza();
        }
        mostarTablero();
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
    //printf("\nPIEZA -> %i\n", piezaActual);
    piezaPrueba++;
    piezaPrueba = ;
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
                /*tablero[0][columnaInicio] = 1;piezaActual
                tablero[0][columnaInicio + 1] = 1;*/

                bloque piezaL_A = { .valor = 1, .tipoPieza = 1, .estado = 1, .codigoPieza = ++contadorPiezas, .y = 0, .x = columnaInicio };
                bloque piezaL_B = { .valor = 1, .tipoPieza = 1, .estado = 1, .codigoPieza = contadorPiezas, .y = 0, .x = columnaInicio + 1 };
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

                bloque piezaL_A = { .valor = 1, .tipoPieza = 2, .estado = 1, .codigoPieza = ++contadorPiezas, .y = 0, .x = columnaInicio };
                bloque piezaL_B = { .valor = 1, .tipoPieza = 2, .estado = 1, .codigoPieza = contadorPiezas, .y = 0, .x = columnaInicio + 1 };
                tablero[0][columnaInicio] = piezaL_A;
                tablero[0][columnaInicio + 1] = piezaL_B;
                codigoPiezaActual = contadorPiezas;
            }
            break;
        case 3: //pieza cubo
            restoPiezaActual = 1;
            if (columnaInicio < 7){
                /*tablero[0][columnaInicio] = 1;
                tablero[0][columnaInicio + 1] = 1;*/

                bloque piezaCubo_A = { .valor = 1, .tipoPieza = 3, .estado = 1, .codigoPieza = ++contadorPiezas, .y = 0, .x = columnaInicio };
                bloque piezaCubo_B = { .valor = 1, .tipoPieza = 3, .estado = 1, .codigoPieza = contadorPiezas, .y = 0, .x = columnaInicio + 1 };
                tablero[0][columnaInicio] = piezaCubo_A;
                tablero[0][columnaInicio + 1] = piezaCubo_B;
                codigoPiezaActual = contadorPiezas;
            }
            break;
        case 4: //pieza T
            restoPiezaActual = 1;
            if (columnaInicio < 6){
                //tablero[0][columnaInicio + 1] = 1;
                bloque piezaT = { .valor = 1, .tipoPieza = 4, .estado = 1, .codigoPieza = ++contadorPiezas, .y = 0, .x = columnaInicio + 1 };
                tablero[0][columnaInicio + 1] = piezaT;
                codigoPiezaActual = contadorPiezas;
            }
            break;
        case 5: //pieza "Z" *invertida
            restoPiezaActual = 1;
            if (columnaInicio < 6){
                /*tablero[0][columnaInicio + 1] = 1;
                tablero[0][columnaInicio + 2] = 1;*/

                bloque piezaZInvertida_A = { .valor = 1, .tipoPieza = 5, .estado = 1, .codigoPieza = ++contadorPiezas, .y = 0, .x = columnaInicio + 1 };
                bloque piezaZInvertida_B = { .valor = 1, .tipoPieza = 5, .estado = 1, .codigoPieza = contadorPiezas, .y = 0, .x = columnaInicio + 2 };
                tablero[0][columnaInicio + 1] = piezaZInvertida_A;
                tablero[0][columnaInicio + 2] = piezaZInvertida_B;
                codigoPiezaActual = contadorPiezas;
            }
            break;
        case 6: //pieza "Z"
            restoPiezaActual = 1;
            if (columnaInicio < 6){
                /*tablero[0][columnaInicio] = 1;
                tablero[0][columnaInicio + 1] = 1;*/
                bloque piezaZ_A = { .valor = 1, .tipoPieza = 6, .estado = 1, .codigoPieza = ++contadorPiezas, .y = 0, .x = columnaInicio };
                bloque piezaZ_B = { .valor = 1, .tipoPieza = 6, .estado = 1, .codigoPieza = contadorPiezas, .y = 0, .x = columnaInicio + 1 };
                tablero[0][columnaInicio] = piezaZ_A;
                tablero[0][columnaInicio + 1] = piezaZ_B;
                codigoPiezaActual = contadorPiezas;
            }
            break;
        default: break;
    }
}

//todo arreglar cuando hay una pieza debajo y se encuentra en la segunda posicion, la primera baja
//todo bug con las piezas que no se generan bien

void moverPiezas(){
    bloque tmp[16][8];
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 8; ++j){
            bloque vacio = { .codigoPieza = -1, .tipoPieza = -1, .estado = -1, .valor = 0, .x = j, .y = i };
            tmp[i][j] = vacio;
        }
    }
    if(restoPiezaActual != 0) {//generar partes restantes de la pieza generada
        for (int j = 0; j < 8; ++j) {
            if (tablero[0][j].codigoPieza == codigoPiezaActual) {
                if (tablero[0][j].tipoPieza == 0) {
                    bloque barra = {.valor = 1, .tipoPieza = 0, .estado = 1, .codigoPieza = codigoPiezaActual, .y = 0, .x = j};
                    tmp[0][j] = barra;
                }else if(tablero[0][j].tipoPieza == 1){
                    bloque piezaL = {.valor = 1, .tipoPieza = 1, .estado = 1, .codigoPieza = codigoPiezaActual, .y = 0, .x = j};
                    tmp[0][j] = piezaL;
                }else if(tablero[0][j].tipoPieza == 2){
                    if(restoPiezaActual == 2){
                        bloque piezaLInvertida = {.valor = 1, .tipoPieza = 2, .estado = 1, .codigoPieza = codigoPiezaActual, .y = 0, .x = j + 1};
                        tmp[0][j + 1] = piezaLInvertida;
                    }else{
                        bloque piezaLInvertida = {.valor = 1, .tipoPieza = 2, .estado = 1, .codigoPieza = codigoPiezaActual, .y = 0, .x = j};
                        tmp[0][j] = piezaLInvertida;
                    }
                }else if(tablero[0][j].tipoPieza == 3){
                    bloque cubo_A = {.valor = 1, .tipoPieza = 3, .estado = 1, .codigoPieza = codigoPiezaActual, .y = 0, .x = j};
                    tmp[0][j] = cubo_A;
                    bloque cubo_B = {.valor = 1, .tipoPieza = 3, .estado = 1, .codigoPieza = codigoPiezaActual, .y = 0, .x = j + 1};
                    tmp[0][j + 1] = cubo_B;
                }else if(tablero[0][j].tipoPieza == 4){
                    bloque piezaT_A = {.valor = 1, .tipoPieza = 4, .estado = 1, .codigoPieza = codigoPiezaActual, .y = 0, .x = j - 1};
                    tmp[0][j - 1] = piezaT_A;
                    bloque piezaT_B = {.valor = 1, .tipoPieza = 4, .estado = 1, .codigoPieza = codigoPiezaActual, .y = 0, .x = j};
                    tmp[0][j] = piezaT_B;
                    bloque piezaT_C = {.valor = 1, .tipoPieza = 4, .estado = 1, .codigoPieza = codigoPiezaActual, .y = 0, .x = j + 1};
                    tmp[0][j + 1] = piezaT_C;
                }else if(tablero[0][j].tipoPieza == 5){
                    bloque piezaZInvertida_A = {.valor = 1, .tipoPieza = 5, .estado = 1, .codigoPieza = codigoPiezaActual, .y = 0, .x = j - 1};
                    tmp[0][j - 1] = piezaZInvertida_A;
                    bloque piezaZInvertida_B = {.valor = 1, .tipoPieza = 5, .estado = 1, .codigoPieza = codigoPiezaActual, .y = 0, .x = j};
                    tmp[0][j] = piezaZInvertida_B;
                }else if(tablero[0][j].tipoPieza == 6){
                    bloque piezaZInvertida_A = {.valor = 1, .tipoPieza = 6, .estado = 1, .codigoPieza = codigoPiezaActual, .y = 0, .x = j + 1};
                    tmp[0][j + 1] = piezaZInvertida_A;
                    bloque piezaZInvertida_B = {.valor = 1, .tipoPieza = 6, .estado = 1, .codigoPieza = codigoPiezaActual, .y = 0, .x = j + 2};
                    tmp[0][j + 2] = piezaZInvertida_B;
                }
                restoPiezaActual--;
                break;
            }
        }
    }

    for (int k = 15; k > -1; --k) {
        for (int i = 0; i < 8; ++i) {
            if(k < 15){
                //printf("\n BLOQUE (%i,%i) ESTADO %i\n", tablero[k][i].x,tablero[k][i].y, tablero[k][i].estado);
                if(tablero[k][i].estado == 1){
                    if(tablero[k + 1][i].valor == 1 && tablero[k + 1][i].codigoPieza != tablero[k][i].codigoPieza){//si hay un bloque debajo debe para la pieza actual
                        printf("pieza debajo\n");
                        pararPieza(tablero[k][i].codigoPieza);
                        tmp[k][i] = tablero[k][i];
                    }else{//si no hay bloque debajo debe continuar su camnino
                        tablero[k][i].y++;
                        tmp[k + 1][i] = tablero[k][i];
                    }
                }else/* if(tablero[k][i].estado == 0)*/{
                    tmp[k][i] = tablero[k][i];
                }
            }else{
                if(tablero[k][i].estado == 1 && tablero[k][i].tipoPieza != -1){
                    //printf("\nPIEZA %i ESTADO%i\n", tablero[k][i].tipoPieza, tablero[k][i].estado);
                    pararPieza(tablero[k][i].codigoPieza);
                    tmp[k][i] = tablero[k][i];
                }else if(tablero[k][i].estado == 0){
                    tmp[k][i] = tablero[k][i];
                }
                /*//if(tablero[k][i].tipoPieza != -1){
                    //printf("\n PARANDO PIEZA ENCONTRADA EN (%i,%i)\n", tablero[k][i].x,tablero[k][i].y);
                    pararPieza(tablero[k][i].codigoPieza);
                    //tablero[k][i].estado = 0;
                }*/
            }
        }
    }

    /*for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 8; ++j){
            if(i < 15){
                if(tablero[i][j].estado != 0){
                    tablero[i][j].y++;
                    tmp[i + 1][j] = tablero[i][j];
                }
            }
        }
    }*/
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 8; ++j)
            tablero[i][j] = tmp[i][j];
    }
}

void pararPieza(int codigoPieza){
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 8; ++j){
            if(tablero[i][j].codigoPieza == codigoPieza){
                tablero[i][j].estado = 0;
                codigoPiezaActual = -1;
                //printf("\n PARANDO PIEZA (%i,%i)\n", tablero[i][j].x,tablero[i][j].y);
            }
        }
    }
}