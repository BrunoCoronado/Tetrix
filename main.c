#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct{
    int estado;//0 si esta parado 1 si esta en movimiento(caida)
    int valor;
    int codigoPieza;
}bloque;

void inicializarTablero();
void mostarTablero();
void iniciarJuego();
int generarPieza();
void pararPieza(int codigoPieza);
void flujoCaida();
int verificarFlujoCaidaDePieza(int numeroFila, int codigoPieza);

bloque tablero[16][8];
int velocidad = 1;//velocidad del juego
int contadorPiezas = 0;//para llevar el codigo de las piezas
char nuevaPieza = '1';//nos va a decir si necesitamos o no generar una nueva pieza

int main() {
    srand(time(NULL));//seed para numeros aleatorios
    inicializarTablero();
    iniciarJuego();
    return 0;
}

void inicializarTablero(){
    bloque tmp = { .codigoPieza = -1, .estado = -1, .valor = 0 };
    for (int k = 0; k < 16; ++k) {
        for (int i = 0; i < 8; ++i)
            tablero[k][i] = tmp;
    }
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
        if(nuevaPieza == '1')
            generarPieza();
        mostarTablero();
        flujoCaida();
        sleep(velocidad);
        i++;
    }
}

int generarPieza(){
    nuevaPieza = '0';
    bloque bloquePieza = { .valor = 1, .estado = 1, .codigoPieza = ++contadorPiezas };
    int tipoPieza = rand() % 7, columnaInicio = rand() % 8;
    if(tipoPieza == 0){ //pieza "|"
        for (int i = 0; i < 4; ++i)
            tablero[i][columnaInicio] = bloquePieza;
        return 0;
    }else if(tipoPieza == 1){ //pieza "L"
        if (columnaInicio < 7){
            for (int i = 0; i < 3; ++i)
                tablero[i][columnaInicio] = bloquePieza;
            tablero[2][columnaInicio + 1] = bloquePieza;
            return 0;
        }
    }else if(tipoPieza == 2){ //pieza "L" *invertida
        if (columnaInicio < 7){
            for (int i = 0; i < 3; ++i)
                tablero[i][columnaInicio + 1] = bloquePieza;
            tablero[2][columnaInicio] = bloquePieza;
            return 0;
        }
    }else if(tipoPieza == 3){ //pieza cubo
        if (columnaInicio < 7){
            for (int i = 0; i < 2; ++i) {
                for (int j = 0; j < 2; ++j)
                    tablero[i][columnaInicio + j] = bloquePieza;
            }
            return 0;
        }
    }else if(tipoPieza == 4){ //pieza T
        if (columnaInicio < 7 && columnaInicio > 0){
            for (int i = -1; i < 2; ++i)
                tablero[0][columnaInicio + i] = bloquePieza;
            tablero[1][columnaInicio] = bloquePieza;
            return 0;
        }
    }else if(tipoPieza == 5){ //pieza "Z" *invertida
        if (columnaInicio < 7 && columnaInicio > 0){
            for (int i = 0; i < 2; ++i)
                tablero[0][columnaInicio + i] = bloquePieza;
            for (int j = -1; j < 1; ++j)
                tablero[1][columnaInicio + j] = bloquePieza;
            return 0;
        }else{
            contadorPiezas--;
            generarPieza();
        }
    }else if(tipoPieza == 6){ //pieza "Z"
        if (columnaInicio < 7 && columnaInicio > 0){
            for (int i = -1; i < 1; ++i)
                tablero[0][columnaInicio + i] = bloquePieza;
            for (int j = 0; j < 2; ++j)
                tablero[1][columnaInicio + j] = bloquePieza;
            return 0;
        }
    }
    contadorPiezas--;
    return generarPieza();
}

void flujoCaida(){//arreglar paro de bloques
    bloque vacio = { .codigoPieza = -1, .estado = -1, .valor = 0 };
    for (int k = 15; k > -1; --k) {
        for (int i = 0; i < 8; ++i){
            if(k == 15){
                if(tablero[k][i].valor == 1 && tablero[k][i].estado == 1){
                    pararPieza(tablero[k][i].codigoPieza);
                }
            }else{
                if(tablero[k][i].valor == 1 && tablero[k][i].estado == 1){
                    if(verificarFlujoCaidaDePieza(k, tablero[k][i].codigoPieza) == 1){
                        tablero[k + 1][i] = tablero[k][i];
                        tablero[k][i] = vacio;
                    }else{
                        pararPieza(tablero[k][i].codigoPieza);
                    }
                }
            }
        }
    }
}

void pararPieza(int codigoPieza){
    nuevaPieza = '1';
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < 8; ++j){
            if(tablero[i][j].codigoPieza == codigoPieza && tablero[i][j].estado == 1)
                tablero[i][j].estado = 0;
        }
    }
}

int verificarFlujoCaidaDePieza(int numeroFila, int codigoPieza){//retorna 0 si no es posible hacer el movimiento y 1 si es posible
    for (int i = 0; i < 8; ++i) {
        if(tablero[numeroFila][i].codigoPieza == codigoPieza){
            if(tablero[numeroFila + 1][i].valor != 0)
                return 0;
        }
    }
    return 1;
}