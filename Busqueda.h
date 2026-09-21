#ifndef BUSQUEDA_H
#define BUSQUEDA_H

#include <vector>
#include <string>

#include "SecuenciaViral.h"

class Busqueda {

public:
    static int secuencialPorAccesion(const std::vector<SecuenciaViral>& datos, const std::string& accessionBuscado){
        for (int i = 0; i < datos.size(); i++) {
            if (datos[i].getAccesion() == accessionBuscado) {
                return i;
            }
        }
        return -1;
    }

    static int binariaPorAccesion(const std::vector<SecuenciaViral>& datos, const std::string& accessionBuscado){
        int izquierda = 0;
        int derecha = datos.size() - 1;
        while (izquierda <= derecha) {
            int medio = izquierda + (derecha - izquierda) / 2;
            if (datos[medio].getAccesion() == accessionBuscado) {
                return medio;
            }
            if (datos[medio].getAccesion() < accessionBuscado) {
                izquierda = medio + 1;
            }
            else {
                derecha = medio - 1;
            }
        }
        return -1;
    }
};

#endif