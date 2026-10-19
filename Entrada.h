
#ifndef ENTRADA_H
#define ENTRADA_H

#include <iostream>
#include <sstream>
#include <string>

class Entrada{
    public:
        static std::string recortar(const std::string& texto) {
            const std::string blancos = " \t\r\n";
            std::string::size_type inicio = texto.find_first_not_of(blancos);
            if (inicio == std::string::npos) {
                return "";
            }
            std::string::size_type fin = texto.find_last_not_of(blancos);
            return texto.substr(inicio, fin - inicio + 1);
        }

        static std::string leerLinea(const std::string& mensaje) {
            std::string linea;
            std::cout << mensaje;

            if (!std::getline(std::cin, linea)) {
                return "";
            }
            return recortar(linea);
        }

        static int leerEntero(const std::string& mensaje, int minimo, int maximo){
            while(true){
                std::string linea = leerLinea(mensaje);
                if(!std::cin){
                    return -1;
                }
                std::istringstream conversion(linea);

                int valor;
                char caracterExtra;
                if((conversion >> valor) && !(conversion >> caracterExtra) && valor >= minimo && valor <= maximo){
                    return valor;
                }

                std::cout << "Entrada invalida. Escriba un entero entre " << minimo << " y " << maximo << ".\n";
            }
        }

        static bool leerSiNo(const std::string& mensaje) {
            std::string respuesta = leerLinea(mensaje);

            return !respuesta.empty() && (respuesta[0] == 's' || respuesta[0] == 'S');
        }
};

#endif
