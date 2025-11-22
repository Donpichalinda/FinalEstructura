#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Tablero.h"

using namespace std;

Tablero::Tablero() {
    inicio = NULL;
    jugadorPos = NULL;
    srand(time(NULL));
}


// =============================================================
//   BUSCAR NODO POR ÍNDICE (0 – 80)
// =============================================================
Nodo* Tablero::getNodoPorIndice(int index) {

    Nodo* temp = inicio;
    int fila = index / 9;
    int col = index % 9;

    // Bajar filas
    for (int i = 0; i < fila; i++) {
        temp = temp->abajo;
    }

    // Moverse a la derecha
    for (int j = 0; j < col; j++) {
        temp = temp->derecha;
    }

    return temp;
}


// =============================================================
//   GENERAR TABLERO 9x9 ENLAZADO SIN MATRICES
// =============================================================
void Tablero::generarNodos() {

    Nodo* filaAnterior = NULL;
    Nodo* primerNodoFilaActual = NULL;

    for (int i = 0; i < 9; i++) {

        Nodo* nodoAnterior = NULL;
        primerNodoFilaActual = NULL;

        for (int j = 0; j < 9; j++) {

            Nodo* nuevo = new Nodo();

            // Guardar primer nodo del tablero
            if (i == 0 && j == 0) {
                inicio = nuevo;
            }

            // Guardar primer nodo de esta fila
            if (j == 0) {
                primerNodoFilaActual = nuevo;
            }

            // Enlazar con nodo izquierdo
            if (nodoAnterior != NULL) {
                nodoAnterior->derecha = nuevo;
                nuevo->izquierda = nodoAnterior;
            }

            // Enlazar con nodo de arriba
            if (filaAnterior != NULL) {
                Nodo* nodoArriba = filaAnterior;
                for (int k = 0; k < j; k++) {
                    nodoArriba = nodoArriba->derecha;
                }
                nuevo->arriba = nodoArriba;
                nodoArriba->abajo = nuevo;
            }

            nodoAnterior = nuevo;
        }

        filaAnterior = primerNodoFilaActual;
    }
}


// =============================================================
//   INICIALIZAR TABLERO
// =============================================================
void Tablero::inicializarTablero(Jugador* jugador) {

    generarNodos();

    // Colocar tesoros primero
    colocarTesoros();
    
    // Colocar muros
    colocarMuros();

    // Posición aleatoria para el jugador (evitar tesoros y muros)
    int pos;
    Nodo* temp;
    
    do {
        pos = rand() % 81;
        temp = getNodoPorIndice(pos);
    } while (temp->tieneTesoro || temp->simbolo == '|');

    jugadorPos = temp;
    jugadorPos->simbolo = 'P';
    jugadorPos->revelado = true;
}


// =============================================================
//   MOSTRAR TABLERO EN CONSOLA
// =============================================================
void Tablero::mostrarTablero() {

    cout << "\n  "; 
    for (int i = 0; i < 9; i++) {
        cout << i << " ";
    }
    cout << endl;

    Nodo* fila = inicio;
    int numFila = 0;

    while (fila != NULL) {

        cout << numFila << " ";
        Nodo* col = fila;

        while (col != NULL) {

            if (col == jugadorPos) {
                cout << "P ";
            }
            else if (!col->revelado && col->simbolo != '|') {
                cout << "o ";
            }
            else {
                cout << col->simbolo << " ";
            }

            col = col->derecha;
        }

        cout << endl;
        fila = fila->abajo;
        numFila++;
    }

    cout << endl;
}


// =============================================================
//   COLOCAR 16 MUROS ALEATORIOS
// =============================================================
void Tablero::colocarMuros() {

    int murosColocados = 0;

    while (murosColocados < 16) {

        int pos = rand() % 81;
        Nodo* temp = getNodoPorIndice(pos);

        // No colocar en jugador o donde ya hay muro o tesoro
        if (temp->simbolo == 'o' && !temp->tieneTesoro) {
            temp->simbolo = '|';
            murosColocados++;
        }
    }
}


// =============================================================
//   COLOCAR 10 TESOROS ALEATORIOS
// =============================================================
void Tablero::colocarTesoros() {

    string tipos[4] = {"Rubi", "Diamante", "Perla", "Ambar"};

    int tesorosColocados = 0;

    while (tesorosColocados < 10) {

        int pos = rand() % 81;
        Nodo* temp = getNodoPorIndice(pos);

        // No colocar en tesoro existente
        if (!temp->tieneTesoro) {
            temp->tieneTesoro = true;
            temp->tipoTesoro = tipos[rand() % 4];
            tesorosColocados++;
        }
    }
}


// =============================================================
//   MOVIMIENTO DEL JUGADOR
// =============================================================
void Tablero::moverJugador(char mov, Jugador* jugador) {

    // Comandos especiales
    if (mov == 'T') {
        mostrarTesoros(jugador);
        return;
    }

    if (mov == 'X') {
        usarTesoroConEfecto(jugador);
        return;
    }

    // Movimiento normal
    Nodo* nuevaPos = NULL;

    switch (mov) {
        case 'W':
            nuevaPos = jugadorPos->arriba;
            break;
        case 'S':
            nuevaPos = jugadorPos->abajo;
            break;
        case 'A':
            nuevaPos = jugadorPos->izquierda;
            break;
        case 'D':
            nuevaPos = jugadorPos->derecha;
            break;
        default:
            cout << "Comando no valido." << endl;
            return;
    }

    // Validar si existe casilla (pared exterior)
    if (nuevaPos == NULL) {
        cout << "No se puede mover, hay una pared!" << endl;
        return;
    }

    // Validar si es muro
    if (nuevaPos->simbolo == '|') {
        cout << "Hay un muro, no puedes pasar!" << endl;
        nuevaPos->revelado = true;
        return;
    }

    // Movimiento válido
    jugadorPos->simbolo = ' ';
    jugadorPos->revelado = true;

    jugadorPos = nuevaPos;
    jugadorPos->simbolo = 'P';
    jugadorPos->revelado = true;

    jugador->sumarMovimiento();

    // Si hay tesoro
    if (jugadorPos->tieneTesoro) {
        cout << "\n*** TESORO ENCONTRADO: " << jugadorPos->tipoTesoro << " ***\n" << endl;
        jugador->agregarTesoro(jugadorPos->tipoTesoro);
        jugadorPos->tieneTesoro = false;
        jugadorPos->tipoTesoro = "";
    }
}


// =============================================================
//   MOSTRAR TESOROS DEL JUGADOR
// =============================================================
void Tablero::mostrarTesoros(Jugador* jugador) {
    
    cout << "\n=== TESOROS RECOLECTADOS ===" << endl;
    
    if (jugador->getCantidadTesoros() == 0) {
        cout << "No tienes tesoros aun." << endl;
        return;
    }
    
    stack<string> temp = jugador->getTesoros();
    int num = 1;
    
    cout << "(El ultimo es el que puedes usar)" << endl;
    
    while (!temp.empty()) {
        cout << num << ". " << temp.top() << endl;
        temp.pop();
        num++;
    }
    
    cout << endl;
}


// =============================================================
//   USAR TESORO Y APLICAR EFECTOS EN EL TABLERO
// =============================================================
void Tablero::usarTesoroConEfecto(Jugador* jugador) {
    
    if (jugador->getCantidadTesoros() == 0) {
        cout << "No tienes tesoros para usar!" << endl;
        return;
    }
    
    stack<string> temp = jugador->getTesoros();
    string tipoTesoro = temp.top();
    
    cout << "\n*** USANDO TESORO: " << tipoTesoro << " ***\n" << endl;
    
    // Aplicar efecto del jugador (modifica puntaje)
    jugador->usarTesoro();
    
    // Aplicar efectos especiales del tablero
    if (tipoTesoro == "Diamante") {
        eliminarMurosAleatorios(2);
    }
    else if (tipoTesoro == "Ambar") {
        teletransportarJugador();
    }
    
    // Recolocar el tesoro usado
    recolocarTesoro(tipoTesoro);
    
    // Tapar casillas reveladas
    taparCasillas();
}


// =============================================================
//   ELIMINAR MUROS ALEATORIOS
// =============================================================
void Tablero::eliminarMurosAleatorios(int cantidad) {
    
    int eliminados = 0;
    int intentos = 0;
    
    while (eliminados < cantidad && intentos < 100) {
        
        int pos = rand() % 81;
        Nodo* temp = getNodoPorIndice(pos);
        
        if (temp->simbolo == '|') {
            temp->simbolo = ' ';
            temp->revelado = true;
            eliminados++;
            cout << "Muro eliminado!" << endl;
        }
        
        intentos++;
    }
}


// =============================================================
//   TELETRANSPORTAR JUGADOR
// =============================================================
void Tablero::teletransportarJugador() {
    
    // Limpiar posición actual
    jugadorPos->simbolo = ' ';
    jugadorPos->revelado = true;
    
    // Buscar nueva posición
    Nodo* nuevaPos;
    
    do {
        int pos = rand() % 81;
        nuevaPos = getNodoPorIndice(pos);
    } while (nuevaPos->revelado || nuevaPos->simbolo == '|' || nuevaPos->tieneTesoro);
    
    jugadorPos = nuevaPos;
    jugadorPos->simbolo = 'P';
    jugadorPos->revelado = true;
    
    cout << "Teletransportado a una nueva ubicacion!" << endl;
}


// =============================================================
//   RECOLOCAR TESORO USADO
// =============================================================
void Tablero::recolocarTesoro(string tipo) {
    
    Nodo* temp;
    
    do {
        int pos = rand() % 81;
        temp = getNodoPorIndice(pos);
    } while (temp->tieneTesoro || temp == jugadorPos || temp->simbolo == '|');
    
    temp->tieneTesoro = true;
    temp->tipoTesoro = tipo;
    
    cout << "El tesoro " << tipo << " ha sido recolocado en el laberinto!" << endl;
}


// =============================================================
//   TAPAR CASILLAS REVELADAS (excepto muros)
// =============================================================
void Tablero::taparCasillas() {
    
    Nodo* fila = inicio;
    
    while (fila != NULL) {
        Nodo* col = fila;
        
        while (col != NULL) {
            
            if (col != jugadorPos && col->revelado && col->simbolo != '|') {
                col->simbolo = 'o';
                col->revelado = false;
            }
            
            col = col->derecha;
        }
        
        fila = fila->abajo;
    }
    
    cout << "El laberinto se ha vuelto a tapar!" << endl;
}