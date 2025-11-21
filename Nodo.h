#ifndef NODO_H
#define NODO_H

#include <string>

using namespace std;

class Nodo {
public:
    char simbolo;     // o, P, muro, etc.
    bool revelado;
    bool tieneTesoro;
    string tipoTesoro;

    Nodo* arriba;
    Nodo* abajo;
    Nodo* izquierda;
    Nodo* derecha;

    Nodo() {
        simbolo = 'o';
        revelado = false;
        tieneTesoro = false;
        tipoTesoro = "";
        arriba = abajo = izquierda = derecha = NULL;
    }
};

#endif
