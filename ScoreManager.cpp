#include "ScoreManager.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void ScoreManager::registrarPuntaje(string nombre, int puntaje) {

    if (puntajes.count(nombre) == 0) {
        puntajes[nombre] = puntaje;
        cout << "Puntaje registrado para " << nombre << endl;
    }
    else {
        // Guardar solo si es mejor (menos puntos)
        if (puntaje < puntajes[nombre]) {
            cout << "Nuevo record! Puntaje anterior: " << puntajes[nombre] << endl;
            puntajes[nombre] = puntaje;
        }
        else {
            cout << "Tu mejor puntaje sigue siendo: " << puntajes[nombre] << endl;
        }
    }
}

int ScoreManager::obtenerPuntaje(string nombre) {

    if (puntajes.count(nombre))
        return puntajes[nombre];

    return -1;
}

void ScoreManager::mostrarRanking() {

    if (puntajes.empty()) {
        cout << "\nNo hay jugadores registrados aun." << endl;
        return;
    }

    cout << "\n========================================" << endl;
    cout << "         RANKING DE JUGADORES" << endl;
    cout << "========================================" << endl;
    
    // Copiar a vector para ordenar
    vector<pair<string, int>> ranking;
    
    for (auto p : puntajes) {
        ranking.push_back(p);
    }
    
    // Ordenar de menor a mayor puntaje
    for (int i = 0; i < ranking.size() - 1; i++) {
        for (int j = 0; j < ranking.size() - i - 1; j++) {
            if (ranking[j].second > ranking[j + 1].second) {
                pair<string, int> temp = ranking[j];
                ranking[j] = ranking[j + 1];
                ranking[j + 1] = temp;
            }
        }
    }
    
    // Mostrar ranking
    int posicion = 1;
    for (auto p : ranking) {
        cout << posicion << ". " << p.first << " - " << p.second << " puntos" << endl;
        posicion++;
    }
    
    cout << "========================================\n" << endl;
}