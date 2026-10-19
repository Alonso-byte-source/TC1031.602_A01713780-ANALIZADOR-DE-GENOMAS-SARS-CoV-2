#ifndef BUSQUEDA_H
#define BUSQUEDA_H

#include <vector>
#include <string>

#include "SecuenciaViral.h"

class Busqueda{
    public:
        static int secuencialPorAccesion(const std::vector<SecuenciaViral>& datos, const std::string& accessionBuscado){
        int total = static_cast<int>(datos.size());
        for(int i = 0; i < total; i++) {
            if (datos[i].getAccesion() == accessionBuscado) {
                return i;
            }
        }
        return -1;
    }

    static int binariaPorAccesion(  const std::vector<SecuenciaViral>& datos, const std::vector<int>& orden, const std::string& accessionBuscado){
        int izquierda = 0;
        int derecha = static_cast<int>(orden.size()) - 1;
        while(izquierda <= derecha){
            int medio = izquierda + (derecha - izquierda) / 2;
            const std::string& actual = datos[orden[medio]].getAccesion();
            if(actual == accessionBuscado){
                return orden[medio];
            }
            if(actual < accessionBuscado){
                izquierda = medio + 1;
            } 
            else{
                derecha = medio - 1;
            }
        }
        return -1;
    }
};

#endif
