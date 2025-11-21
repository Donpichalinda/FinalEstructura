#ifndef TABLERO_H
#define TABLERO_H

#include "Nodo.h"
#include "Jugador.h"

class Tablero {
private:
    Nodo* inicio;   // Primer nodo (0,0)

public:
    Tablero();
    void inicializarTablero(Jugador* jugador);
    void mostrarTablero();
    void colocarTesoros();
    void colocarMuros();
    void moverJugador(char mov, Jugador* jugador);
};

#endif
