#ifndef ORDENAMIENTO_H
#define ORDENAMIENTO_H

#include <vector>
#include <string>

#include "SecuenciaViral.h"

class Ordenamiento {

public:
    // MERGE SORT
    static void merge(std::vector<SecuenciaViral>& datos, int izquierda, int medio, int derecha){
        std::vector<SecuenciaViral> izquierdaVector;
        std::vector<SecuenciaViral> derechaVector;

        for (int i = izquierda; i <= medio; i++) {
            izquierdaVector.push_back(datos[i]);
        }

        for (int i = medio + 1; i <= derecha; i++) {
            derechaVector.push_back(datos[i]);
        }

        int i = 0;
        int j = 0;
        int k = izquierda;

        while (i < izquierdaVector.size() && j < derechaVector.size()){
            if (izquierdaVector[i].getLongitud() <= derechaVector[j].getLongitud()){
                datos[k] = izquierdaVector[i];
                i++;
            } else{
                datos[k] = derechaVector[j];
                j++;
            }
            k++;
        }

        while (i < izquierdaVector.size()) {
            datos[k] = izquierdaVector[i];
            i++;
            k++;
        }

        while (j < derechaVector.size()) {
            datos[k] = derechaVector[j];
            j++;
            k++;
        }
    }


    static void mergeSortLongitud(std::vector<SecuenciaViral>& datos, int izquierda, int derecha){
        if (izquierda >= derecha) {
            return;
        }

        int medio = izquierda + (derecha - izquierda) / 2;

        mergeSortLongitud(datos, izquierda, medio);
        mergeSortLongitud(datos, medio + 1, derecha);
        merge(datos, izquierda, medio, derecha);
    }

};

#endif