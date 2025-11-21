#include <iostream>
#include "Tablero.h"
#include "Jugador.h"
#include "ScoreManager.h"

using namespace std;

int main() {
    cout << "=== JUEGO DEL LABERINTO ===" << endl << endl;

    string nombre;
    cout << "Ingrese su nombre: ";
    cin >> nombre;

    // Crear jugador y tablero
    Jugador jugador(nombre);
    Tablero tablero;
    ScoreManager puntajes;

    tablero.inicializarTablero(&jugador);

    char opcion;

    // Ciclo principal del juego
    do {
        tablero.mostrarTablero();
        cout << "Movimiento (W/A/S/D), T para ver tesoros, X para usar tesoro: ";
        cin >> opcion;

        tablero.moverJugador(opcion, &jugador);

    } while (jugador.getTesorosRecogidos() < 10);

    int puntos = jugador.getPuntaje();
    cout << "Juego terminado en " << puntos << " puntos." << endl;

    // Guardar puntaje
    puntajes.registrarPuntaje(jugador.getNombre(), puntos);

    return 0;
}
