#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <stack>
using namespace std;

class Jugador {
private:
    string nombre;
    int puntaje;

    stack<string> tesoros;

public:
    Jugador(string n);

    void agregarTesoro(string tipo);
    void usarTesoro();

    int getPuntaje();
    void sumarMovimiento();

    int getTesorosRecogidos();
    string getNombre();
};

#endif
