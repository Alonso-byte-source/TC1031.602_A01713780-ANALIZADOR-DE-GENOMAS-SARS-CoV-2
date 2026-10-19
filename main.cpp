#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <string>
#include <chrono>

#include "Dataset.h"
#include "Filtros.h"
#include "Busqueda.h"
#include "Ordenamiento.h"
#include "Exportador.h"
#include "Entrada.h"

using namespace std;
const string RUTA_DATASET = "data/sars_cov2_100000.tsv";

typedef chrono::steady_clock Reloj;

double milisegundosDesde(Reloj::time_point inicio){
    return chrono::duration<double, milli>(Reloj::now() - inicio).count();
}

double microsegundos(Reloj::time_point inicio, Reloj::time_point fin){
    return chrono::duration<double, micro>(fin - inicio).count();
}

// Cambiar cantidad si quieres visualizar mas resultados
void mostrarResultados(const vector<SecuenciaViral>& resultados, int cantidad){
    int limite = min(cantidad, static_cast<int>(resultados.size()));

    for (int i = 0; i < limite; i++) {
        cout << "\nRegistro " << i + 1 << "\n";
        cout << "Accession: " << resultados[i].getAccesion() << "\n";
        cout << "Linaje: " << resultados[i].getLinaje() << "\n";
        cout << "Ubicacion: " << resultados[i].getUbicacion() << "\n";
        cout << "Longitud: " << resultados[i].getLongitud() << "\n";
    }
}

// Pregunta si se desea guardar TODOS los resultados en un archivo TSV.
void ofrecerGuardado(const vector<SecuenciaViral>& resultados, const string& nombreArchivo){
    if (resultados.empty()) return;
    cout << "\n";
    if (!Entrada::leerSiNo("Guardar los " + to_string(resultados.size()) + " resultados en '" + nombreArchivo + "'? (s/n): ")) {
        return;
    }

    if (Exportador::guardarTSV(resultados, nombreArchivo)) {
        cout << "Archivo guardado: " << nombreArchivo << "\n";
    } else {
        cout << "No se pudo escribir el archivo.\n";
    }
}

// Muestra el conteo, las primeras 5 filas y ofrece guardar.
void reportarResultados(const vector<SecuenciaViral>& resultado, const string& archivoSugerido){
    cout << "\nRegistros encontrados: " << resultado.size() << "\n";
    mostrarResultados(resultado, 5);
    ofrecerGuardado(resultado, archivoSugerido);
}

// OPCION 1
void opcionMostrar(const Dataset& dataset){
    int cantidad = Entrada::leerEntero("Cuantos registros desea mostrar: ", 1, dataset.cantidadRegistros());
    dataset.mostrarRegistros(cantidad);
}

// OPCIONES 2 a 5
void opcionLinaje(const Dataset& dataset){
    string linaje = Entrada::leerLinea("Ingrese el linaje: ");
    reportarResultados(Filtros::porLinaje(dataset.getSecuencias(), linaje), "resultados_linaje.tsv");
}

void opcionUbicacion(const Dataset& dataset){
    string ubicacion = Entrada::leerLinea("Ingrese la ubicacion exactamente como aparece en el dataset:\n");
    reportarResultados(Filtros::porUbicacion(dataset.getSecuencias(), ubicacion), "resultados_ubicacion.tsv");
}

void opcionHuesped(const Dataset& dataset){
    string huesped = Entrada::leerLinea("Ingrese el huesped (ej. Homo sapiens): ");
    reportarResultados(Filtros::porHuesped(dataset.getSecuencias(), huesped), "resultados_huesped.tsv");
}

void opcionCompletitud(const Dataset& dataset){
    string completitud = Entrada::leerLinea("Ingrese la completitud (ej. COMPLETE): ");
    reportarResultados(Filtros::porCompletitud(dataset.getSecuencias(), completitud), "resultados_completitud.tsv");
}

// OPCION 6
void opcionLongitud(const Dataset& dataset){
    int minimo = Entrada::leerEntero("Longitud minima: ", 0, 1000000);
    int maximo = Entrada::leerEntero("Longitud maxima: ", minimo, 1000000);
    reportarResultados(Filtros::porLongitud(dataset.getSecuencias(), minimo, maximo), "resultados_longitud.tsv");
}

// Imprime una fila de la tabla comparativa de busquedas.
void imprimirFilaBusqueda(const string& metodo, int posicion, double tiempoUs, const string& complejidad){
    cout << left << setw(14) << metodo << setw(11) << posicion << setw(15) << fixed << setprecision(2) << tiempoUs << complejidad << "\n";
}

// OPCION 7: busca el mismo accession con los tres metodos y compara.
void opcionBuscar(const Dataset& dataset){
    string accession = Entrada::leerLinea("Ingrese accession: ");
    const vector<SecuenciaViral>& datos = dataset.getSecuencias();

    Reloj::time_point t0 = Reloj::now();
    int posSecuencial = Busqueda::secuencialPorAccesion(datos, accession);
    Reloj::time_point t1 = Reloj::now();
    int posBinaria = Busqueda::binariaPorAccesion(datos, dataset.getOrdenAccession(), accession);
    Reloj::time_point t2 = Reloj::now();
    int posArbol = dataset.getArbol().buscar(accession);
    Reloj::time_point t3 = Reloj::now();

    cout << "\n" << left << setw(14) << "Metodo" << setw(11) << "Posicion" << setw(15) << "Tiempo (us)" << "Complejidad\n";
    
    imprimirFilaBusqueda("Secuencial", posSecuencial, microsegundos(t0, t1), "O(n)");
    imprimirFilaBusqueda("Binaria", posBinaria, microsegundos(t1, t2), "O(log n)");
    imprimirFilaBusqueda("Arbol BST", posArbol, microsegundos(t2, t3), "O(log n)");
    
    cout << "(Posicion -1 = no encontrado. Una sola medicion: los " << "tiempos pueden variar.)\n";

    if(posArbol != -1){
        cout << "\nSecuencia encontrada:\n";
        datos[posArbol].imprimir(cout);
    } else{
        cout << "\nNo se encontro la secuencia.\n";
    }
}

// OPCION 8
void opcionOrdenarLongitud(const Dataset& dataset){
    vector<SecuenciaViral> datos = dataset.getSecuencias();
    cout << "\nOrdenando por longitud (Merge Sort)...\n";

    Reloj::time_point inicio = Reloj::now();
    Ordenamiento::porLongitud(datos);
    double ms = milisegundosDesde(inicio);

    cout << "Ordenamiento terminado en " << fixed << setprecision(1) << ms << " ms.\n";
    cout << "\nPrimeros registros (los mas cortos):\n";
    mostrarResultados(datos, 10);
    ofrecerGuardado(datos, "ordenado_por_longitud.tsv");
}

// OPCION 9: recorrido en orden del arbol = registros por accession.
void opcionArbol(const Dataset& dataset){
    const ArbolAccession& arbol = dataset.getArbol();
    int n = arbol.tamano();
    int minimo = static_cast<int>(ceil(log2(n + 1.0)));

    cout << "\nArbol binario de busqueda por accession\n";
    cout << "Nodos: " << n << "\n";
    cout << "Altura: " << arbol.altura() << " (minimo posible: " << minimo << ")\n";

    int cantidad = Entrada::leerEntero("Cuantos registros mostrar en orden de accession: ", 1, n);

    vector<int> indices;
    arbol.enOrden(indices, static_cast<size_t>(n));

    vector<SecuenciaViral> ordenados;
    ordenados.reserve(indices.size());
    for(size_t i = 0; i < indices.size(); i++){
        ordenados.push_back(dataset.getSecuencias()[indices[i]]);
    }
    mostrarResultados(ordenados, cantidad);
    ofrecerGuardado(ordenados, "ordenado_por_accession.tsv");
}

void imprimirMenu(){
    cout << "\n====================================\n";
    cout << " ANALIZADOR DE GENOMAS SARS-CoV-2\n";
    cout << "====================================\n";

    cout << "1. Mostrar registros\n";
    cout << "2. Filtrar por linaje\n";
    cout << "3. Filtrar por ubicacion\n";
    cout << "4. Filtrar por huesped\n";
    cout << "5. Filtrar por completitud\n";
    cout << "6. Filtrar por longitud\n";
    cout << "7. Buscar por accession (comparar metodos)\n";
    cout << "8. Ordenar por longitud\n";
    cout << "9. Recorrer arbol (orden por accession)\n";
    cout << "0. Salir\n";
}

void menu(const string& archivo) {
    Dataset dataset;
    cout << "Cargando dataset desde '" << archivo << "'...\n";

    Reloj::time_point inicio = Reloj::now();
    if (!dataset.cargarArchivo(archivo)) {
        cout << "Error al cargar el dataset.\n";
        cout << "Ejecuta el programa desde la raiz del proyecto o ";
        cout << "indica la ruta como argumento.\n";
        return;
    }
    double ms = milisegundosDesde(inicio);

    cout << "\nDataset cargado correctamente.\n";
    cout << "Registros: " << dataset.cantidadRegistros() << "\n";
    if (dataset.getLineasOmitidas() > 0) {
        cout << "Lineas omitidas (mal formadas): " << dataset.getLineasOmitidas() << "\n";
    }

    cout << "Arbol construido: altura " << dataset.getArbol().altura() << ". Carga + ordenamiento + arbol: " << fixed << setprecision(0) << ms << " ms\n";

    int opcion;

    do{
        imprimirMenu();
        opcion = Entrada::leerEntero("\nSeleccione una opcion: ", 0, 9);
        if(!cin){
            break;
        }
        switch (opcion) {
            case 1: opcionMostrar(dataset); break;
            case 2: opcionLinaje(dataset); break;
            case 3: opcionUbicacion(dataset); break;
            case 4: opcionHuesped(dataset); break;
            case 5: opcionCompletitud(dataset); break;
            case 6: opcionLongitud(dataset); break;
            case 7: opcionBuscar(dataset); break;
            case 8: opcionOrdenarLongitud(dataset); break;
            case 9: opcionArbol(dataset); break;
            default: break;
        }
    } while(opcion != 0);
    cout << "\nPrograma terminado.\n";
}

int main(int argc, char* argv[]){
    string archivo = RUTA_DATASET;
    if (argc > 1) {
        archivo = argv[1];
    }
    menu(archivo);
   if(!cin){
    cout << "\nEntrada cerrada. Programa terminado.\n";
   }
    return 0;
}
