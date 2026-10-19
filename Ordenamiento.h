#ifndef ORDENAMIENTO_H
#define ORDENAMIENTO_H

#include <cstddef>
#include <vector>
#include <string>
#include <utility>

#include "SecuenciaViral.h"

class Ordenamiento{
    public:
        template <typename T, typename Comparador>
        static void mergeSort(std::vector<T>& datos, Comparador menorQue){
            if (datos.size() < 2) {
                return;
            }
            std::vector<T> auxiliar(datos);
            ordenar(datos, auxiliar, 0,
            static_cast<int>(datos.size()) - 1, menorQue);
        }

        // Ordena las secuencias por longitud (ascendente).
        static void porLongitud(std::vector<SecuenciaViral>& datos){
            mergeSort(datos, [](const SecuenciaViral& a, const SecuenciaViral& b){
                return a.getLongitud() < b.getLongitud();
            });
        }

        // Ordena las secuencias por accession (ascendente).
        static void porAccesion(std::vector<SecuenciaViral>& datos){
            mergeSort(datos, [](const SecuenciaViral& a, const SecuenciaViral& b){
                return a.getAccesion() < b.getAccesion();
            });
        }

        static std::vector<int> indicesPorAccesion(const std::vector<SecuenciaViral>& datos){
            std::vector<int> indices(datos.size());
            for (std::size_t i = 0; i < indices.size(); i++) {
                indices[i] = static_cast<int>(i);
            }
            mergeSort(indices, [&datos](int a, int b){
            return datos[a].getAccesion() < datos[b].getAccesion();
            });
            return indices;
         }

    private:
        template <typename T, typename Comparador>
        static void ordenar(std::vector<T>& datos, std::vector<T>& auxiliar, int izquierda, int derecha, Comparador menorQue){
            if (izquierda >= derecha) {
                return;
            }
            int medio = izquierda + (derecha - izquierda) / 2;

            ordenar(datos, auxiliar, izquierda, medio, menorQue);
            ordenar(datos, auxiliar, medio + 1, derecha, menorQue);
            merge(datos, auxiliar, izquierda, medio, derecha, menorQue);
        }

        template <typename T, typename Comparador>
        static void merge(std::vector<T>& datos, std::vector<T>& auxiliar, int izquierda, int medio, int derecha, Comparador menorQue){
            for(int k = izquierda; k <= derecha; k++){
                auxiliar[k] = std::move(datos[k]);
            }

            int i = izquierda;
            int j = medio + 1;
            int k = izquierda;

            while(i <= medio && j <= derecha){
                if(menorQue(auxiliar[j], auxiliar[i])){
                    datos[k++] = std::move(auxiliar[j++]);
                } else{
                    datos[k++] = std::move(auxiliar[i++]);
                }
            }

            while(i <= medio){
                datos[k++] = std::move(auxiliar[i++]);
            }

            while(j <= derecha){
                datos[k++] = std::move(auxiliar[j++]);
            }
        }
};

#endif
