#ifndef SECUENCIAVIRAL_H
#define SECUENCIAVIRAL_H

#include <string>
#include <ostream>

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
        SecuenciaViral(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, int, const std::string&, const std::string&);
        // Los getters devuelven const& para NO copiar la cadena.
        const std::string& getAccesion() const;
        const std::string& getLinaje() const;
        const std::string& getUbicacion() const;
        const std::string& getFechaMuestra() const;
        const std::string& getHuesped() const;
        const std::string& getCompletitud() const;
        const std::string& getFechaLiberacion() const;
        int getLongitud() const;
        void imprimir(std::ostream&) const;
};

inline SecuenciaViral::SecuenciaViral(const std::string& accession1, const std::string& linaje1, const std::string& ubicacion1, const std::string& fechaMuestra1, const std::string& huesped1, int longitud1, const std::string& completitud1, const std::string& fechaLiberacion1)
    : accession(accession1), linaje(linaje1), ubicacion(ubicacion1), fechaMuestra(fechaMuestra1), huesped(huesped1), completitud(completitud1), fechaLiberacion(fechaLiberacion1), longitud(longitud1){}

inline const std::string& SecuenciaViral::getAccesion() const{
    return accession;
}

inline const std::string& SecuenciaViral::getLinaje() const{
    return linaje;
}

inline const std::string& SecuenciaViral::getUbicacion() const{
    return ubicacion;
}

inline const std::string& SecuenciaViral::getFechaMuestra() const{
    return fechaMuestra;
}

inline const std::string& SecuenciaViral::getHuesped() const{
    return huesped;
}

inline const std::string& SecuenciaViral::getCompletitud() const{
    return completitud;
}

inline const std::string& SecuenciaViral::getFechaLiberacion() const{
    return fechaLiberacion;
}

inline int SecuenciaViral::getLongitud() const{
    return longitud;
}


inline void SecuenciaViral::imprimir(std::ostream& salida) const{
    salida << "Accession: " << accession << "\n" << "Linaje: " << linaje << "\n" << "Ubicacion: " << ubicacion << "\n" << "Fecha de muestra: " << fechaMuestra << "\n" << "Huesped: " << huesped << "\n" << "Longitud: " << longitud << "\n" << "Completitud: " << completitud << "\n" << "Fecha de liberacion: " << fechaLiberacion << "\n";
}

#endif
