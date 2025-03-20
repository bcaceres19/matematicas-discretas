#include <iostream>
#include <list>
#include <map>
#include <string>
#include <regex>
#include <vector>
#include <cmath>
#include <sstream>
#include <algorithm> // para std::find y std::sort

using namespace std;

// Función para eliminar duplicados y ordenar el conjunto
void eliminarDuplicados(vector<int>& conjunto) {
    sort(conjunto.begin(), conjunto.end()); // Ordenar el vector
    conjunto.erase(unique(conjunto.begin(), conjunto.end()), conjunto.end()); // Eliminar duplicados
}

// Función para convertir una cadena en una lista de enteros
vector<int> convertirALista(const string& str) {
    vector<int> resultado;
    stringstream ss(str);
    string temp;
    while (getline(ss, temp, ',')) {
        if (!temp.empty()) { // Evita el último carácter si hay una coma final
            resultado.push_back(stoi(temp));
        }
    }
    eliminarDuplicados(resultado); // Eliminar duplicados y ordenar
    return resultado;
}

// Función para generar subconjuntos faltantes del conjunto universal respecto a un subconjunto
vector<int> obtenerSubconjuntosFaltantes(const vector<int>& universal, const vector<int>& subconjunto) {
    vector<int> subconjuntosFaltantes;
    for (int elem : universal) {
        if (find(subconjunto.begin(), subconjunto.end(), elem) == subconjunto.end()) {
            subconjuntosFaltantes.push_back(elem);
        }
    }
    return subconjuntosFaltantes;
}

// Función para generar y mostrar todos los subconjuntos (power set)
void generarSubconjuntos(const vector<int>& conjunto) {
    int n = conjunto.size();
    int totalSubconjuntos = pow(2, n); // 2^n subconjuntos
    cout << "Total de subconjuntos: " << totalSubconjuntos << endl;
    cout << "Los subconjuntos son:" << endl;
    for (int mascara = 0; mascara < totalSubconjuntos; mascara++) {
        cout << "{ ";
        bool primero = true;
        for (int j = 0; j < n; j++) {
            if (mascara & (1 << j)) {
                if (!primero) cout << ", ";
                cout << conjunto[j];
                primero = false;
            }
        }
        cout << " }" << endl;
    }
}

// Función para generar y mostrar los subconjuntos propios (sin el vacío y el conjunto completo)
void generarSubconjuntosPropios(const vector<int>& conjunto) {
    int n = conjunto.size();
    int totalSubconjuntos = pow(2, n);
    cout << "Subconjuntos propios:" << endl;
    for (int mascara = 1; mascara < totalSubconjuntos - 1; mascara++) {
        cout << "{ ";
        bool primero = true;
        for (int j = 0; j < n; j++) {
            if (mascara & (1 << j)) {
                if (!primero) cout << ", ";
                cout << conjunto[j];
                primero = false;
            }
        }
        cout << " }" << endl;
    }
}

// Función para generar y devolver el conjunto potencia (power set) en forma de vector de subconjuntos
vector<vector<int>> obtenerConjuntoPotencia(const vector<int>& conjunto) {
    int n = conjunto.size();
    int totalSubconjuntos = pow(2, n);
    vector<vector<int>> potencia;
    for (int mascara = 0; mascara < totalSubconjuntos; mascara++) {
        vector<int> subset;
        for (int j = 0; j < n; j++) {
            if (mascara & (1 << j)) {
                subset.push_back(conjunto[j]);
            }
        }
        potencia.push_back(subset);
    }
    return potencia;
}

// Función para imprimir el conjunto potencia a partir del vector de subconjuntos
void imprimirConjuntoPotencia(const vector<vector<int>>& potencia) {
    cout << "Conjunto potencia:" << endl;
    for (const auto& subset : potencia) {
        cout << "{ ";
        bool primero = true;
        for (int elem : subset) {
            if (!primero) cout << ", ";
            cout << elem;
            primero = false;
        }
        cout << " }" << endl;
    }
}

// Función para imprimir un conjunto (vector de enteros)
void imprimirConjunto(const vector<int>& conjunto) {
    cout << "{ ";
    for (size_t i = 0; i < conjunto.size(); i++) {
        if (i > 0) cout << ", ";
        cout << conjunto[i];
    }
    cout << " }" << endl;
}

int main() {
    string modeloUniversal;
    string patron = R"(^[0-9]+(,[0-9]+)*$)";
    regex regexPatron(patron);
    
    // Se solicita inicialmente el conjunto universal
    vector<int> conjuntoUniversal;
    while (true) {
        cout << "Ingrese el conjunto universal (ejemplo: 1,2,3,4): ";
        cin >> modeloUniversal;
        if (regex_match(modeloUniversal, regexPatron)) {
            conjuntoUniversal = convertirALista(modeloUniversal);
            cout << "Conjunto universal procesado (sin duplicados): ";
            imprimirConjunto(conjuntoUniversal);
            break;
        } else {
            cout << "Entrada inválida. Intente nuevamente." << endl;
        }
    }

    int opcion;
    do {
        cout << "\nMenú de opciones:" << endl;
        cout << "1. Generar todos los subconjuntos" << endl;
        cout << "2. Generar subconjuntos propios" << endl;
        cout << "3. Generar ambos" << endl;
        cout << "4. Ingresar un subconjunto y operar con sus subconjuntos faltantes" << endl;
        cout << "5. Ingresar un nuevo conjunto universal" << endl;
        cout << "6. Mostrar el conjunto potencia" << endl;
        cout << "7. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        switch (opcion) {
            case 1:
                generarSubconjuntos(conjuntoUniversal);
                break;
            case 2:
                generarSubconjuntosPropios(conjuntoUniversal);
                break;
            case 3:
                generarSubconjuntos(conjuntoUniversal);
                generarSubconjuntosPropios(conjuntoUniversal);
                break;
            case 4: {
                string subconjuntoStr;
                cout << "Ingrese el subconjunto (ejemplo: 1,3): ";
                cin >> subconjuntoStr;
                if (regex_match(subconjuntoStr, regexPatron)) {
                    vector<int> subconjunto = convertirALista(subconjuntoStr);
                    // Obtener subconjuntos faltantes
                    vector<int> subconjuntosFaltantes = obtenerSubconjuntosFaltantes(conjuntoUniversal, subconjunto);
                    if (subconjuntosFaltantes.empty()) {
                        cout << "No hay elementos faltantes en el conjunto universal respecto al subconjunto ingresado." << endl;
                    } else {
                        cout << "Subconjuntos faltantes: ";
                        imprimirConjunto(subconjuntosFaltantes);
                        int subOpcion;
                        cout << "\nOpciones para los subconjuntos faltantes:" << endl;
                        cout << "1. Generar subconjuntos propios de los subconjuntos faltantes" << endl;
                        cout << "2. Generar todos los subconjuntos de los subconjuntos faltantes" << endl;
                        cout << "Seleccione una opción: ";
                        cin >> subOpcion;
                        if (subOpcion == 1) {
                            generarSubconjuntosPropios(subconjuntosFaltantes);
                        } else if (subOpcion == 2) {
                            generarSubconjuntos(subconjuntosFaltantes);
                        } else {
                            cout << "Opción inválida." << endl;
                        }
                    }
                } else {
                    cout << "Formato inválido." << endl;
                }
                break;
            }
            case 5:
                cout << "Ingrese el nuevo conjunto universal: ";
                cin >> modeloUniversal;
                if (regex_match(modeloUniversal, regexPatron)) {
                    conjuntoUniversal = convertirALista(modeloUniversal);
                    cout << "Nuevo conjunto universal actualizado: ";
                    imprimirConjunto(conjuntoUniversal);
                } else {
                    cout << "Entrada inválida. No se actualizó el conjunto." << endl;
                }
                break;
            case 6: {
                vector<vector<int>> potencia = obtenerConjuntoPotencia(conjuntoUniversal);
                imprimirConjuntoPotencia(potencia);
                break;
            }
            case 7:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
        }
    } while (opcion != 7);

    return 0;
}
