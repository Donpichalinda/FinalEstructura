#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Tablero.h"

using namespace std;

Tablero::Tablero() {
    inicio = NULL;
}

void Tablero::inicializarTablero(Jugador* jugador) {
    // Crear los 81 nodos conectados en forma de lista enlazada 9x9
    // Por simplicidad se asume que esto se implementará después
    // Aquí también se colocarán muros y tesoros
    colocarMuros();
    colocarTesoros();
}

void Tablero::mostrarTablero() {
    // Recorrer e imprimir el 9x9
    cout << "Mostrando tablero..." << endl;
}

void Tablero::colocarTesoros() {
    // 10 tesoros aleatorios
}

void Tablero::colocarMuros() {
    // Colocar 16 muros "|"
}

void Tablero::moverJugador(char mov, Jugador* jugador) {
    // Revisar movimiento, actualizar puntero del jugador, sumar puntos
}
