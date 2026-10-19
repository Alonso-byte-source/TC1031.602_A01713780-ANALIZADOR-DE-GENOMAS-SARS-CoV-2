
#ifndef ARBOLACCESSION_H
#define ARBOLACCESSION_H

#include <algorithm>
#include <cstddef>
#include <string>
#include <vector>

#include "SecuenciaViral.h"

class ArbolAccession {
private:
    struct Nodo {
        std::string accession;
        int indice;
        int nivel;
        int balance;

        Nodo* izquierdo;
        Nodo* derecho;

        Nodo(const std::string& accession1, int indice1)
            : accession(accession1),
              indice(indice1),
              nivel(1),
              balance(0),
              izquierdo(nullptr),
              derecho(nullptr) {}
    };

    Nodo* raiz;
    int cantidad;

    static int alturaDe(Nodo* nodo) {
        return (nodo == nullptr) ? 0 : nodo->nivel;
    }

    static void actualizar(Nodo* nodo) {
        if (nodo == nullptr) {
            return;
        }

        int izquierda = alturaDe(nodo->izquierdo);
        int derecha = alturaDe(nodo->derecho);

        nodo->nivel = 1 + std::max(izquierda, derecha);
        nodo->balance = izquierda - derecha;
    }

    static Nodo* rotarDerecha(Nodo* y) {
        Nodo* x = y->izquierdo;
        Nodo* temporal = x->derecho;

        x->derecho = y;
        y->izquierdo = temporal;

        actualizar(y);
        actualizar(x);

        return x;
    }

    static Nodo* rotarIzquierda(Nodo* x) {
        Nodo* y = x->derecho;
        Nodo* temporal = y->izquierdo;

        y->izquierdo = x;
        x->derecho = temporal;

        actualizar(x);
        actualizar(y);

        return y;
    }

    static Nodo* balancear(Nodo* nodo) {
        if (nodo == nullptr) {
            return nullptr;
        }

        actualizar(nodo);

        // Desbalance hacia la izquierda.
        if (nodo->balance > 1) {
            if (nodo->izquierdo->balance < 0) {
                nodo->izquierdo =
                    rotarIzquierda(nodo->izquierdo);
            }

            return rotarDerecha(nodo);
        }

        // Desbalance hacia la derecha.
        if (nodo->balance < -1) {
            if (nodo->derecho->balance > 0) {
                nodo->derecho =
                    rotarDerecha(nodo->derecho);
            }

            return rotarIzquierda(nodo);
        }

        return nodo;
    }

    static Nodo* insertarAVL(
        Nodo* nodo,
        const std::string& accession,
        int indice,
        bool& insertado
    ) {
        if (nodo == nullptr) {
            insertado = true;
            return new Nodo(accession, indice);
        }

        if (accession == nodo->accession) {
            insertado = false;
            return nodo;
        }

        if (accession < nodo->accession) {
            nodo->izquierdo = insertarAVL(
                nodo->izquierdo,
                accession,
                indice,
                insertado
            );
        } else {
            nodo->derecho = insertarAVL(
                nodo->derecho,
                accession,
                indice,
                insertado
            );
        }

        if (!insertado) {
            return nodo;
        }

        return balancear(nodo);
    }

    static void recorrer(
        Nodo* nodo,
        std::vector<int>& salida,
        std::size_t limite
    ) {
        if (nodo == nullptr || salida.size() >= limite) {
            return;
        }

        recorrer(nodo->izquierdo, salida, limite);

        if (salida.size() < limite) {
            salida.push_back(nodo->indice);
        }

        recorrer(nodo->derecho, salida, limite);
    }

    static void liberar(Nodo* nodo) {
        if (nodo == nullptr) {
            return;
        }

        liberar(nodo->izquierdo);
        liberar(nodo->derecho);

        delete nodo;
    }

public:
    ArbolAccession() : raiz(nullptr), cantidad(0) {}

    // Evita copias superficiales que provocarían doble liberación.
    ArbolAccession(const ArbolAccession&) = delete;
    ArbolAccession& operator=(const ArbolAccession&) = delete;

    ~ArbolAccession() {
        liberar(raiz);
    }

    // Inserta un accession; devuelve false si ya existe.
    // Tiempo: O(log n) porque el árbol es AVL.
    bool insertar(const std::string& accession, int indice) {
        bool insertado = false;

        raiz = insertarAVL(
            raiz, accession, indice, insertado
        );

        if (insertado) {
            cantidad++;
        }

        return insertado;
    }

    // Construye el árbol a partir de los registros del dataset.
    // Los accession repetidos se omiten.
    void construirBalanceado(
        const std::vector<SecuenciaViral>& datos,
        const std::vector<int>& orden
    ) {
        liberar(raiz);
        raiz = nullptr;
        cantidad = 0;

        for (std::size_t i = 0; i < orden.size(); i++) {
            int indice = orden[i];

            insertar(
                datos[indice].getAccesion(),
                indice
            );
        }
    }

    // Devuelve el índice del registro o -1 si no existe.
    int buscar(const std::string& accession) const {
        Nodo* actual = raiz;

        while (actual != nullptr) {
            if (accession == actual->accession) {
                return actual->indice;
            }

            if (accession < actual->accession) {
                actual = actual->izquierdo;
            } else {
                actual = actual->derecho;
            }
        }

        return -1;
    }

    // Agrega índices en orden ascendente de accession.
    void enOrden(
        std::vector<int>& salida,
        std::size_t limite
    ) const {
        recorrer(raiz, salida, limite);
    }

    // Altura del árbol; un árbol vacío tiene altura 0.
    int altura() const {
        return alturaDe(raiz);
    }

    int tamano() const {
        return cantidad;
    }
};

#endif
