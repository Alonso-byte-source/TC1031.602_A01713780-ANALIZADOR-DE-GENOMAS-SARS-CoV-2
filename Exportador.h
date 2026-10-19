#ifndef EXPORTADOR_H
#define EXPORTADOR_H

#include <vector>
#include <string>
#include <fstream>

#include "SecuenciaViral.h"

class Exportador {
    public:
        static bool guardarTSV(const std::vector<SecuenciaViral>& datos, const std::string& nombreArchivo){
        std::ofstream archivo(nombreArchivo);

        if (!archivo.is_open()) {
            return false;
        }

        archivo << "Accession\tVirus Pangolin Classification\t" << "Geographic Location\tIsolate Collection date\t" << "Host Name\tLength\tCompleteness\tRelease date\n";

        for(const SecuenciaViral& s : datos){
            archivo << s.getAccesion() << "\t" << s.getLinaje() << "\t" << s.getUbicacion() << "\t" << s.getFechaMuestra() << "\t" << s.getHuesped() << "\t" << s.getLongitud() << "\t" << s.getCompletitud() << "\t" << s.getFechaLiberacion() << "\n";
        }

        archivo.close();
        return true;
    }
};

#endif
