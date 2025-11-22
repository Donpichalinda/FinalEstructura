#include <iostream>
#include "Tablero.h"
#include "Jugador.h"
#include "ScoreManager.h"

using namespace std;

int main() {
    
    ScoreManager puntajes;
    char jugarOtravez = 'S';
    
    while (jugarOtravez == 'S' || jugarOtravez == 's') {
        
        cout << "\n=== JUEGO DEL LABERINTO ===" << endl << endl;

        string nombre;
        cout << "Ingrese su nombre: ";
        cin >> nombre;

        // Crear jugador y tablero
        Jugador jugador(nombre);
        Tablero tablero;

        tablero.inicializarTablero(&jugador);

        char opcion;
        bool juegoActivo = true;

        // Ciclo principal del juego
        while (juegoActivo) {
            
            cout << "\nPuntaje actual: " << jugador.getPuntaje() << " puntos" << endl;
            cout << "Tesoros recolectados: " << jugador.getCantidadTesoros() << "/10" << endl;
            
            tablero.mostrarTablero();
            
            cout << "\nMovimiento (W/A/S/D), T para ver tesoros, X para usar tesoro: ";
            cin >> opcion;
            
            // Convertir a mayuscula si es minuscula
            if (opcion >= 'a' && opcion <= 'z') {
                opcion = opcion - 32;
            }

            tablero.moverJugador(opcion, &jugador);
            
            // Verificar si gano
            if (jugador.getCantidadTesoros() >= 10) {
                juegoActivo = false;
            }
        }

        // Fin del juego
        int puntos = jugador.getPuntaje();
        cout << "\n========================================" << endl;
        cout << "   JUEGO TERMINADO!" << endl;
        cout << "   Jugador: " << jugador.getNombre() << endl;
        cout << "   Puntaje final: " << puntos << " puntos" << endl;
        cout << "========================================\n" << endl;

        // Guardar puntaje
        puntajes.registrarPuntaje(jugador.getNombre(), puntos);

        // Preguntar si quiere jugar de nuevo
        cout << "Desea jugar otra vez? (S/N): ";
        cin >> jugarOtravez;
    }
    
    // Mostrar ranking final
    puntajes.mostrarRanking();
    
    cout << "\nGracias por jugar!" << endl;

    return 0;
}