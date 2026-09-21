#include <iostream>
#include <vector>
#include <string>
#include <chrono>

#include "Dataset.h"
#include "Filtros.h"
#include "Busqueda.h"
#include "Ordenamiento.h"

using namespace std;

void mostrarResultados(const vector<SecuenciaViral>& resultados, int cantidad){
    int limite = min(cantidad, static_cast<int>(resultados.size()));

    for (int i = 0; i < limite; i++) {
        cout << "\nRegistro " << i + 1 << "\n";
        cout << "Accession: "
             << resultados[i].getAccesion() << "\n";
        cout << "Linaje: "
             << resultados[i].getLinaje() << "\n";
        cout << "Ubicacion: "
             << resultados[i].getUbicacion() << "\n";
        cout << "Longitud: "
             << resultados[i].getLongitud() << "\n";
    }
}

void menu() {

    Dataset dataset;

    string archivo = "C:/Datasets/sars_cov2_100000.tsv";

    cout << "Cargando dataset...\n";

    if (!dataset.cargarArchivo(archivo)) {
        cout << "Error al cargar el dataset.\n";
        return;
    }

    cout << "\nDataset cargado correctamente.\n";
    cout << "Registros: " << dataset.cantidadRegistros() << "\n";

    int opcion;

    do{
        cout << "\n====================================\n";
        cout << " ANALIZADOR DE GENOMAS SARS-CoV-2\n";
        cout << "====================================\n";

        cout << "1. Mostrar registros\n";
        cout << "2. Filtrar por linaje\n";
        cout << "3. Filtrar por ubicacion\n";
        cout << "4. Filtrar por longitud\n";
        cout << "5. Buscar por accession\n";
        cout << "6. Ordenar por longitud\n";
        cout << "0. Salir\n";

        cout << "\nSeleccione una opcion: ";

        cin >> opcion;

        // OPCION 1

        if (opcion == 1) {
            int cantidad;
            cout << "Cuantos registros desea mostrar: ";
            cin >> cantidad;
            dataset.mostrarRegistros(cantidad);
        }

        // OPCION 2

        else if (opcion == 2) {
            string linaje;
            cout << "Ingrese el linaje: ";
            cin >> linaje;
            vector<SecuenciaViral> resultado = Filtros::porLinaje(dataset.getSecuencias(), linaje);
            cout << "\nRegistros encontrados: " << resultado.size() << "\n";
            mostrarResultados(resultado, 5);
        }

        // OPCION 3

        else if (opcion == 3) {
            string ubicacion;
            cout << "Ingrese la ubicacion exactamente como aparece en el dataset:\n";
            cin.ignore();
            getline(cin, ubicacion);
            vector<SecuenciaViral> resultado = Filtros::porUbicacion(dataset.getSecuencias(), ubicacion);
            cout << "\nRegistros encontrados: " << resultado.size() << "\n";
            mostrarResultados(resultado, 5);
        }

        // OPCION 4

        else if (opcion == 4) {
            int minimo;
            int maximo;
            cout << "Longitud minima: ";
            cin >> minimo;
            cout << "Longitud maxima: ";
            cin >> maximo;
            vector<SecuenciaViral> resultado = Filtros::porLongitud(dataset.getSecuencias(), minimo, maximo);
            cout << "\nRegistros encontrados: " << resultado.size() << "\n";
            mostrarResultados(resultado, 5);
        }

        // OPCION 5

        else if (opcion == 5) {
            string accession;
            cout << "Ingrese accession: ";
            cin >> accession;
            int posicion = Busqueda::secuencialPorAccesion(dataset.getSecuencias(), accession);
            if (posicion != -1) {
                cout << "\nSecuencia encontrada.\n";
                cout << "Posicion: " << posicion << "\n";
                cout << "Linaje: " << dataset.getSecuencias()[posicion].getLinaje() << "\n";
            } else{
                cout << "\nNo se encontro la secuencia.\n";
            }
        }

        // OPCION 6

        else if (opcion == 6) {
            vector<SecuenciaViral> datos = dataset.getSecuencias();
            cout << "\nOrdenando...\n";
            Ordenamiento::mergeSortLongitud(datos, 0, datos.size() - 1);
            cout << "Ordenamiento terminado.\n";
            cout << "\nPrimeros registros:\n";
            mostrarResultados(datos, 10);
        }
    } while (opcion != 0);
    cout << "\nPrograma terminado.\n";
}


int main() {
    menu();
    return 0;
}