#include <iostream>
#include "ScoreManager.h"

using namespace std;

void ScoreManager::registrarPuntaje(string nombre, int puntaje) {
    if (tablaPuntajes.count(nombre) == 0) {
        tablaPuntajes[nombre] = puntaje;
    } else {
        if (puntaje < tablaPuntajes[nombre]) {
            tablaPuntajes[nombre] = puntaje;
        }
    }
}

void ScoreManager::mostrarPuntaje(string nombre) {
    if (tablaPuntajes.count(nombre)) {
        cout << nombre << " tiene mejor puntaje: " << tablaPuntajes[nombre] << endl;
    } else {
        cout << "Este jugador no tiene registros." << endl;
    }
}

void ScoreManager::mostrarRanking() {
    cout << "Ranking de jugadores:" << endl;
    for (auto p : tablaPuntajes) {
        cout << p.first << " -> " << p.second << endl;
    }
}
