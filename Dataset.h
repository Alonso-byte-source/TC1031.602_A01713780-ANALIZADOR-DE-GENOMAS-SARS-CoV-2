#ifndef DATASET_H
#define DATASET_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>

#include "SecuenciaViral.h"
#include "Ordenamiento.h"
#include "ArbolAccession.h"

class Dataset{
    private:
        std::vector<SecuenciaViral> secuencias;
        std::vector<int> ordenAccession;
        ArbolAccession arbol;
        int lineasOmitidas;
        void construirIndices();
    public:
        Dataset() : lineasOmitidas(0) {}
        bool cargarArchivo(const std::string&);
        void mostrarRegistros(int) const;
        int cantidadRegistros() const;
        int getLineasOmitidas() const;
        const std::vector<SecuenciaViral>& getSecuencias() const;
        const std::vector<int>& getOrdenAccession() const;
        const ArbolAccession& getArbol() const;
};

inline bool Dataset::cargarArchivo(const std::string& nombreArchivo){
    std::ifstream archivo(nombreArchivo);
    if(!archivo.is_open()){
        std::cout << "No se pudo abrir el archivo: " << nombreArchivo << "\n";
        return false;
    }

    secuencias.clear();
    lineasOmitidas = 0;

    std::string linea;

    std::getline(archivo, linea);

    while(std::getline(archivo, linea)){
        if(!linea.empty() && linea.back() == '\r'){
            linea.pop_back();
        }

        std::stringstream ss(linea);
        std::string celda;
        std::vector<std::string> campos;

        while(std::getline(ss, celda, '\t')){
            campos.push_back(celda);
        }

        if(campos.size() != 8){
            lineasOmitidas++;
            continue;
        }

        int longitud;
        char caracterExtra;

        std::istringstream conversion(campos[5]);

        if (!(conversion >> longitud) || (conversion >> caracterExtra)) {
            lineasOmitidas++;
            continue;
        }

        secuencias.push_back(SecuenciaViral(
            campos[0],
            campos[1],
            campos[2],
            campos[3],
            campos[4],
            longitud,
            campos[6],
            campos[7]
        ));
    }
    archivo.close();

    construirIndices();
    return true;
}

inline void Dataset::construirIndices(){
    ordenAccession = Ordenamiento::indicesPorAccesion(secuencias);
    arbol.construirBalanceado(secuencias, ordenAccession);
}

inline void Dataset::mostrarRegistros(int cantidad) const{
    int limite = std::min(cantidad, static_cast<int>(secuencias.size()));
    for(int i = 0; i < limite; i++){
        std::cout << "\nRegistro " << i + 1 << "\n";
        secuencias[i].imprimir(std::cout);
    }
}

inline int Dataset::cantidadRegistros() const{
    return static_cast<int>(secuencias.size());
}

inline int Dataset::getLineasOmitidas() const{
    return lineasOmitidas;
}

inline const std::vector<SecuenciaViral>& Dataset::getSecuencias() const {
    return secuencias;
}

inline const std::vector<int>& Dataset::getOrdenAccession() const {
    return ordenAccession;
}

inline const ArbolAccession& Dataset::getArbol() const {
    return arbol;
}

#endif
