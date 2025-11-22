#ifndef SCORE_MANAGER_H
#define SCORE_MANAGER_H

#include <string>
#include <map>
using namespace std;

// Usaremos un map como tabla hash simple
class ScoreManager {

private:
    map<string, int> puntajes;

public:

    void registrarPuntaje(string nombre, int puntaje);
    int obtenerPuntaje(string nombre);
    void mostrarRanking();
};

#endif
