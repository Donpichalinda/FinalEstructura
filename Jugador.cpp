#include "Jugador.h"

Jugador::Jugador(string n) {
    nombre = n;
    puntaje = 0;
}

void Jugador::sumarMovimiento() {
    puntaje++;
}

void Jugador::agregarTesoro(string tipo) {
    tesoros.push(tipo);
}

void Jugador::usarTesoro() {
    if (!tesoros.empty()) {
        string t = tesoros.top();
        tesoros.pop();
        // Aplicar efecto del tesoro (se programará luego)
    }
}

int Jugador::getPuntaje() {
    return puntaje;
}

int Jugador::getTesorosRecogidos() {
    return tesoros.size();
}

string Jugador::getNombre() {
    return nombre;
}
