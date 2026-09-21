#ifndef SECUENCIAVIRAL_H
#define SECUENCIAVIRAL_H

#include <string>

class SecuenciaViral{
    private:
        std::string accession;
        std::string linaje;
        std::string ubicacion;
        std::string fechaMuestra;
        std::string huesped;
        std::string completitud;
        std::string fechaLiberacion;
        int longitud; 
    public:
        SecuenciaViral();
        SecuenciaViral(
            const std::string&,
            const std::string&,
            const std::string&,
            const std::string&,
            const std::string&,
            int longitud,
            const std::string&,
            const std::string&
        );
        std::string getAccesion() const;
        std::string getLinaje() const;
        std::string getUbicacion() const;
        std::string getFechaMuestra() const;
        std::string getHuesped() const;
        std::string getCompletitud() const;
        std::string getFechaLiberacion() const;
        int getLongitud() const;

};

SecuenciaViral::SecuenciaViral(
    const std::string& accession1,
    const std::string& linaje1,
    const std::string& ubicacion1,
    const std::string& fechaMuestra1,
    const std::string& huesped1,
    int longitud1,
    const std::string& completitud1,
    const std::string& fechaLiberacion1
): 
    accession(accession1),       
    linaje(linaje1),            
    ubicacion(ubicacion1),      
    fechaMuestra(fechaMuestra1),
    huesped(huesped1),
    longitud(longitud1),
    completitud(completitud1),
    fechaLiberacion(fechaLiberacion1)
{}

std::string SecuenciaViral::getAccesion() const{
    return accession;
}

std::string SecuenciaViral::getLinaje() const{
    return linaje;
}

std::string SecuenciaViral::getUbicacion() const{
    return ubicacion;
}

std::string SecuenciaViral::getFechaMuestra() const{
    return fechaMuestra;
}

std::string SecuenciaViral::getHuesped() const{
    return huesped;
}

std::string SecuenciaViral::getCompletitud() const{
    return completitud;
}

std::string SecuenciaViral::getFechaLiberacion() const{
    return fechaLiberacion;
}

int SecuenciaViral::getLongitud() const{
    return longitud;
}

#endif