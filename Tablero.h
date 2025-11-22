#ifndef TABLERO_H
#define TABLERO_H

#include "Nodo.h"
#include "Jugador.h"
#include <stack>

using namespace std;

class Tablero {

private:

    Nodo* inicio;           // Nodo superior izquierdo
    Nodo* jugadorPos;       // Posición actual del jugador

public:

    Tablero();

    // Construcción
    void generarNodos();
    Nodo* getNodoPorIndice(int index);
    void inicializarTablero(Jugador* jugador);

    // Juego
    void moverJugador(char mov, Jugador* jugador);

    // Renderizado
    void mostrarTablero();
    void mostrarTesoros(Jugador* jugador);

    // Aleatorios
    void colocarMuros();
    void colocarTesoros();

    // Efectos especiales
    void usarTesoroConEfecto(Jugador* jugador);
    void eliminarMurosAleatorios(int cantidad);
    void teletransportarJugador();
    void recolocarTesoro(string tipo);
    void taparCasillas();
};

#endif