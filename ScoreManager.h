#ifndef SCORE_MANAGER_H
#define SCORE_MANAGER_H

#include <string>
#include <map>

using namespace std;

// Se usará un map como tabla hash simple
class ScoreManager {
private:
    map<string, int> tablaPuntajes;

public:
    void registrarPuntaje(string nombre, int puntaje);
    void mostrarPuntaje(string nombre);
    void mostrarRanking();
};

#endif
