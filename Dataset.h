#ifndef DATASET_H
#define DATASET_H

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include "SecuenciaViral.h"

class Dataset{
    private:
        std::vector<SecuenciaViral> secuencias;
    public:
        bool cargarArchivo(const std::string&);
        void mostrarRegistros(int);
        int cantidadRegistros();
        const std::vector<SecuenciaViral>& getSecuencias() const;
};


bool Dataset::cargarArchivo(const std::string& nombreArchivo){
    std::ifstream archivo(nombreArchivo);

    if(!archivo.is_open()){
        std::cout << "No se puedo abrir el archivo.\n";
        return false;
    }

    std::string linea;

    std::getline(archivo, linea); 

    while (getline(archivo, linea)){
        std::stringstream ss(linea);
        std::string celda;
        std::vector<std::string> campos;

        while(getline(ss, celda, '\t')){
            campos.push_back(celda); 
        }

        if(campos.size() != 8){
            continue;
        }
        SecuenciaViral secuencia(
            campos[0],
            campos[1],
            campos[2],
            campos[3],
            campos[4],
            std::stoi(campos[5]),
            campos[6],
            campos[7]
        );
        secuencias.push_back(secuencia);
    }
    archivo.close();
    return true;
}

void Dataset::mostrarRegistros(int cantidad){
    int limite = std::min(cantidad, (int)secuencias.size());
    for(int i = 0; i < limite; i++){
        std::cout << "\nRegistro" << i + 1 << "\n";

        std::cout << "Accession: " 
                  << secuencias[i].getAccesion() << "\n";
        std::cout << "Linaje: " 
                  << secuencias[i].getLinaje() << "\n";
        std::cout << "Ubicacion: " 
                  << secuencias[i].getUbicacion() << "\n";
        std::cout << "Fecha de muestra: " 
                  << secuencias[i].getFechaMuestra() << "\n";
        std::cout << "Huesped: " 
                  << secuencias[i].getHuesped() << "\n";
        std::cout << "Longitud: " 
                  << secuencias[i].getLongitud() << "\n";
        std::cout << "Completitud: " 
                  << secuencias[i].getCompletitud() << "\n";
        std::cout << "Fecha de liberacion: " 
                  << secuencias[i].getFechaLiberacion() << "\n";
    }

}

int Dataset::cantidadRegistros(){
    return secuencias.size();
}

const std::vector<SecuenciaViral>& Dataset::getSecuencias() const {
    return secuencias;
}




#endif