#include "Jugador.h"
#include <iostream>
using namespace std;

Jugador::Jugador(string n) {

    nombre = n;
    puntaje = 0;
}

void Jugador::sumarMovimiento() {
    puntaje++;
}

int Jugador::getPuntaje() {
    return puntaje;
}

string Jugador::getNombre() {
    return nombre;
}

void Jugador::agregarTesoro(string tipo) {

    cout << "Tesoro agregado: " << tipo << endl;
    tesoros.push(tipo);
}

int Jugador::getCantidadTesoros() {
    return tesoros.size();
}

stack<string> Jugador::getTesoros() {
    return tesoros;
}


// =========================================================
//   USAR TESORO Y APLICAR EFECTOS
// =========================================================
void Jugador::usarTesoro() {

    if (tesoros.empty()) {
        cout << "No tienes tesoros para usar." << endl;
        return;
    }

    string t = tesoros.top();
    tesoros.pop();

    cout << "Usando tesoro: " << t << endl;

    if (t == "Rubi") {

        // Mitad de los puntos
        puntaje = puntaje / 2;
        cout << "Rubí usado. Puntaje reducido a la mitad." << endl;
    }

    else if (t == "Diamante") {

        cout << "Diamante -> Eliminar 2 muros aleatoriamente." << endl;
        // La eliminación real la maneja Tablero cuando detecte uso del tesoro
    }

    else if (t == "Perla") {

        int r = rand() % 2;

        if (r == 0) {
            puntaje = 0;
            cout << "Perla -> Puntaje reiniciado a 0." << endl;
        }
        else {
            puntaje = puntaje * 2;
            cout << "Perla -> Puntaje duplicado." << endl;
        }
    }

    else if (t == "Ambar") {

        cout << "Ámbar -> Teletransporte a una zona aleatoria." << endl;
        // El teletransporte lo aplica Tablero
    }
}
