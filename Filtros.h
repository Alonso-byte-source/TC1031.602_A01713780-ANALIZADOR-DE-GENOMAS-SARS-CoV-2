#ifndef FILTROS_H
#define FILTROS_H

#include <vector>
#include <string>

#include "SecuenciaViral.h"

class Filtros {
public:

    static std::vector<SecuenciaViral> porLinaje(const std::vector<SecuenciaViral>& datos, const std::string& linajeBuscado){
        std::vector<SecuenciaViral> resultado;
        for (const SecuenciaViral& secuencia : datos) {
            if (secuencia.getLinaje() == linajeBuscado) {
                resultado.push_back(secuencia);
            }
        }
        return resultado;
    }


    static std::vector<SecuenciaViral> porUbicacion(const std::vector<SecuenciaViral>& datos, const std::string& ubicacionBuscada){
        std::vector<SecuenciaViral> resultado;
        for (const SecuenciaViral& secuencia : datos) {
            if (secuencia.getUbicacion() == ubicacionBuscada) {
                resultado.push_back(secuencia);
            }
        }
        return resultado;
    }


    static std::vector<SecuenciaViral> porHuesped(const std::vector<SecuenciaViral>& datos, const std::string& huespedBuscado){
        std::vector<SecuenciaViral> resultado;
        for (const SecuenciaViral& secuencia : datos) {
            if (secuencia.getHuesped() == huespedBuscado) {
                resultado.push_back(secuencia);
            }
        }
        return resultado;
    }


    static std::vector<SecuenciaViral> porCompletitud(const std::vector<SecuenciaViral>& datos, const std::string& completitudBuscada){
        std::vector<SecuenciaViral> resultado;
        for (const SecuenciaViral& secuencia : datos) {
            if (secuencia.getCompletitud() == completitudBuscada) {
                resultado.push_back(secuencia);
            }
        }
        return resultado;
    }


    static std::vector<SecuenciaViral> porLongitud(const std::vector<SecuenciaViral>& datos, int minimo, int maximo){
        std::vector<SecuenciaViral> resultado;
        for (const SecuenciaViral& secuencia : datos){
            int longitud = secuencia.getLongitud();
            if (longitud >= minimo && longitud <= maximo){
                resultado.push_back(secuencia);
            }
        }
        return resultado;
    }
};

#endif