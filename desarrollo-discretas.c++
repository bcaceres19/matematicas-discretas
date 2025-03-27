#include <iostream>
#include <list>
#include <map>
#include <string>
#include <regex>
#include <vector>
#include <cmath>
#include <sstream>
#include <algorithm>
#include <functional>  // Para funciones lambda (si se requieren)
#include <random>      // Para std::shuffle y generar números aleatorios
#include <limits>
using namespace std;

/*------------------------------------------------------------------------------
   Funciones de Utilidad para Manejo de Conjuntos
------------------------------------------------------------------------------*/

// Elimina elementos duplicados y ordena el vector.
// Parámetro: conjunto - vector de strings a procesar.
void eliminarDuplicados(vector<string>& conjunto) {
    sort(conjunto.begin(), conjunto.end());
    conjunto.erase(unique(conjunto.begin(), conjunto.end()), conjunto.end());
}

// Convierte una cadena separada por comas en un vector de strings.
// Ejemplo: "a,b,c" → { "a", "b", "c" }.
// Se eliminan duplicados al final.
// Parámetro: str - cadena de entrada.
vector<string> convertirALista(const string& str) {
    vector<string> resultado;
    stringstream ss(str);
    string temp;
    while (getline(ss, temp, ',')) {
        if (!temp.empty()) { // Evita agregar cadenas vacías
            resultado.push_back(temp);
        }
    }
    eliminarDuplicados(resultado);
    return resultado;
}

// Obtiene los elementos que están en el conjunto universal pero no en el subconjunto.
// Parámetros:
//   universal: vector con el conjunto universal.
//   subconjunto: vector con el subconjunto a comparar.
// Retorna: vector con los elementos faltantes.
vector<string> obtenerSubconjuntosFaltantes(const vector<string>& universal, const vector<string>& subconjunto) {
    vector<string> faltantes;
    for (const string &elem : universal) {
        if (find(subconjunto.begin(), subconjunto.end(), elem) == subconjunto.end()) {
            faltantes.push_back(elem);
        }
    }
    return faltantes;
}

// Imprime un vector de strings en formato { elem1, elem2, ... }.
// Parámetro: conjunto - vector a imprimir.
void imprimirConjunto(const vector<string>& conjunto) {
    cout << "{ ";
    for (size_t i = 0; i < conjunto.size(); i++) {
        if (i > 0) cout << ", ";
        cout << conjunto[i];
    }
    cout << " }" << endl;
}

/*------------------------------------------------------------------------------
   Funciones para la Generación de Subconjuntos (Power Set)
------------------------------------------------------------------------------*/

// Genera y muestra todos los subconjuntos (power set) de un conjunto dado.
// Parámetro: conjunto - vector que representa el conjunto.
void generarSubconjuntos(const vector<string>& conjunto) {
    int n = conjunto.size();
    int totalSubconjuntos = pow(2, n);
    cout << "Total de subconjuntos: " << totalSubconjuntos << endl;
    cout << "Los subconjuntos son:" << endl;
    // Itera sobre todas las posibles máscaras (de 0 a 2^n - 1)
    for (int mascara = 0; mascara < totalSubconjuntos; mascara++) {
        cout << "{ ";
        bool primero = true;
        for (int j = 0; j < n; j++) {
            // Verifica si el j-ésimo bit de la máscara está activado
            if (mascara & (1 << j)) {
                if (!primero) cout << ", ";
                cout << conjunto[j];
                primero = false;
            }
        }
        cout << " }" << endl;
    }
}

// Genera y muestra solo los subconjuntos propios (excluyendo el vacío y el conjunto completo).
// Parámetro: conjunto - vector que representa el conjunto.
void generarSubconjuntosPropios(const vector<string>& conjunto) {
    int n = conjunto.size();
    int totalSubconjuntos = pow(2, n);
    cout << "Subconjuntos propios:" << endl;
    // Se omite la máscara 0 (vacío) y la última (conjunto completo)
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

// Genera y retorna el conjunto potencia (power set) como un vector de subconjuntos.
// Parámetro: conjunto - vector que representa el conjunto.
// Retorna: vector de vectores, cada uno siendo un subconjunto.
vector<vector<string>> obtenerConjuntoPotencia(const vector<string>& conjunto) {
    int n = conjunto.size();
    int totalSubconjuntos = pow(2, n);
    vector<vector<string>> potencia;
    for (int mascara = 0; mascara < totalSubconjuntos; mascara++) {
        vector<string> subset;
        for (int j = 0; j < n; j++) {
            if (mascara & (1 << j)) {
                subset.push_back(conjunto[j]);
            }
        }
        potencia.push_back(subset);
    }
    return potencia;
}

/*------------------------------------------------------------------------------
   Funciones para Generar Subconjuntos de Tamaño n
------------------------------------------------------------------------------*/

// Función recursiva auxiliar que genera y muestra subconjuntos de tamaño n.
// Parámetros:
//   conjunto: vector original.
//   n: tamaño del subconjunto deseado.
//   index: posición actual en el vector.
//   actual: vector que contiene el subconjunto en construcción.
void generarSubconjuntosTamanioNRec(const vector<string>& conjunto, int n, int index, vector<string>& actual) {
    if(n == 0) {
        cout << "{ ";
        bool primero = true;
        for (const string &elem : actual) {
            if (!primero) cout << ", ";
            cout << elem;
            primero = false;
        }
        cout << " }" << endl;
        return;
    }
    for (int i = index; i < conjunto.size(); i++) {
        actual.push_back(conjunto[i]);
        generarSubconjuntosTamanioNRec(conjunto, n - 1, i + 1, actual);
        actual.pop_back();
    }
}

// Genera y muestra los subconjuntos de tamaño n de un conjunto.
// Parámetros:
//   conjunto: vector que representa el conjunto.
//   n: tamaño deseado para los subconjuntos.
void generarSubconjuntosTamanioN(const vector<string>& conjunto, int n) {
    if(n < 0 || n > conjunto.size()) {
         cout << "El tamaño especificado no es válido. Debe ser entre 0 y " << conjunto.size() << "." << endl;
         return;
    }
    vector<string> actual;
    cout << "Subconjuntos de tamaño " << n << ":" << endl;
    generarSubconjuntosTamanioNRec(conjunto, n, 0, actual);
}

/*------------------------------------------------------------------------------
   Función para Calcular la Diferencia Simétrica
------------------------------------------------------------------------------*/

// Calcula la diferencia simétrica entre dos conjuntos: elementos que están en uno
// u otro, pero no en ambos.
// Parámetros:
//   a: primer conjunto (vector de strings).
//   b: segundo conjunto (vector de strings).
// Retorna: vector con la diferencia simétrica.
vector<string> symmetricDifference(const vector<string>& a, const vector<string>& b) {
    vector<string> unionAB = a;
    // Agrega elementos de b que no están en a
    for (const string &elem : b) {
        if (find(unionAB.begin(), unionAB.end(), elem) == unionAB.end()) {
            unionAB.push_back(elem);
        }
    }
    // Calcula la intersección de a y b
    vector<string> interseccion;
    for (const string &elem : a) {
        if (find(b.begin(), b.end(), elem) != b.end()) {
            interseccion.push_back(elem);
        }
    }
    // La diferencia simétrica son los elementos de la unión que no están en la intersección
    vector<string> diff;
    for (const string &elem : unionAB) {
        if (find(interseccion.begin(), interseccion.end(), elem) == interseccion.end()) {
            diff.push_back(elem);
        }
    }
    return diff;
}

/*------------------------------------------------------------------------------
   Función para Procesar Operaciones entre Varios Subconjuntos (Submenú)
------------------------------------------------------------------------------*/

// Permite al usuario ingresar varios subconjuntos y luego seleccionar operaciones
// entre ellos (unión, intersección, diferencia, diferencia simétrica, complemento,
// complemento relativo). Muestra además los elementos faltantes respecto al conjunto universal.
// Parámetro:
//   conjuntoUniversal: vector que contiene el conjunto universal.
// Función para Procesar Operaciones entre Varios Subconjuntos (Submenú)
void procesarOperacionesSubconjuntos(const vector<string>& conjuntoUniversal) {
    int numSubconjuntos;
    cout << "Ingrese la cantidad de subconjuntos a procesar: ";
    cin >> numSubconjuntos;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Limpiar el buffer

    // Patrón para validar el formato: solo letras y dígitos separados por comas.
    string patron = R"(^[A-Za-z0-9]+(,[A-Za-z0-9]+)*$)";
    regex regexPatron(patron);
    
    vector<vector<string>> listaSubconjuntos;
    
    // Se utiliza un bucle que solo avanza cuando el subconjunto ingresado es válido.
    for (int i = 0; i < numSubconjuntos; ) {
        cout << "\nIngrese el subconjunto #" << (i + 1) << " (ejemplo: a,c o 1,3): ";
        string subconjuntoStr;
        getline(cin, subconjuntoStr);
        
        if (!regex_match(subconjuntoStr, regexPatron)) {
            cout << "Formato inválido. Intente nuevamente." << endl;
            continue;  // Se vuelve a pedir el mismo subconjunto
        }
        
        vector<string> subconjunto = convertirALista(subconjuntoStr);
        // Verifica que cada elemento pertenezca al conjunto universal
        bool esSubconjuntoValido = true;
        for (const string &elem : subconjunto) {
            if (find(conjuntoUniversal.begin(), conjuntoUniversal.end(), elem) == conjuntoUniversal.end()) {
                esSubconjuntoValido = false;
                break;
            }
        }
        if (!esSubconjuntoValido) {
            cout << "El subconjunto ingresado contiene elementos que no pertenecen al conjunto universal. Intente nuevamente." << endl;
            continue;  // Se vuelve a pedir el mismo subconjunto
        }
        // Si el subconjunto es válido, se agrega y se pasa al siguiente.
        listaSubconjuntos.push_back(subconjunto);
        i++;  // Solo se incrementa cuando se ingresa un subconjunto válido.
    }
    
    if (listaSubconjuntos.empty()) {
        cout << "No se ingresaron subconjuntos válidos." << endl;
        return;
    }
    
    int operacion;
    do {
        cout << "\nSeleccione la operación a realizar entre los subconjuntos ingresados:" << endl;
        cout << "1. Unión de todos los subconjuntos" << endl;
        cout << "2. Intersección de todos los subconjuntos" << endl;
        cout << "3. Diferencia (primer subconjunto menos la unión de los demás)" << endl;
        cout << "4. Diferencia simétrica de todos los subconjuntos" << endl;
        cout << "5. Conjunto complemento (de un subconjunto respecto al universal)" << endl;
        cout << "6. Complemento relativo (de un subconjunto A respecto a otro B)" << endl;
        cout << "7. Salir de operaciones" << endl;
        cout << "Opción: ";
        cin >> operacion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Limpiar el buffer
        
        vector<string> resultado;
        switch(operacion) {
            case 1: { // Unión de todos los subconjuntos
                for (auto &subconjunto : listaSubconjuntos) {
                    for (const string &elem : subconjunto) {
                        if (find(resultado.begin(), resultado.end(), elem) == resultado.end()) {
                            resultado.push_back(elem);
                        }
                    }
                }
                cout << "\nLa unión de los subconjuntos es: ";
                imprimirConjunto(resultado);
                break;
            }
            case 2: { // Intersección de todos los subconjuntos
                resultado = listaSubconjuntos[0];
                for (size_t i = 1; i < listaSubconjuntos.size(); i++) {
                    vector<string> temp;
                    for (const string &elem : resultado) {
                        if (find(listaSubconjuntos[i].begin(), listaSubconjuntos[i].end(), elem) != listaSubconjuntos[i].end()) {
                            temp.push_back(elem);
                        }
                    }
                    resultado = temp;
                }
                cout << "\nLa intersección de los subconjuntos es: ";
                imprimirConjunto(resultado);
                break;
            }
            case 3: { // Diferencia: primer subconjunto menos la unión de los demás
                if (listaSubconjuntos.size() < 2) {
                    cout << "Para realizar la diferencia se requiere al menos dos subconjuntos." << endl;
                } else {
                    vector<string> unionResto;
                    for (size_t i = 1; i < listaSubconjuntos.size(); i++) {
                        for (const string &elem : listaSubconjuntos[i]) {
                            if (find(unionResto.begin(), unionResto.end(), elem) == unionResto.end()) {
                                unionResto.push_back(elem);
                            }
                        }
                    }
                    for (const string &elem : listaSubconjuntos[0]) {
                        if (find(unionResto.begin(), unionResto.end(), elem) == unionResto.end()) {
                            resultado.push_back(elem);
                        }
                    }
                    cout << "\nLa diferencia (primer subconjunto menos la unión de los demás) es: ";
                    imprimirConjunto(resultado);
                }
                break;
            }
            case 4: { // Diferencia simétrica de todos los subconjuntos
                resultado = listaSubconjuntos[0];
                for (size_t i = 1; i < listaSubconjuntos.size(); i++) {
                    resultado = symmetricDifference(resultado, listaSubconjuntos[i]);
                }
                cout << "\nLa diferencia simétrica de los subconjuntos es: ";
                imprimirConjunto(resultado);
                break;
            }
            case 5: { // Complemento: elementos del universal que no están en el subconjunto seleccionado
                int indice;
                cout << "Ingrese el índice del subconjunto (1 a " << listaSubconjuntos.size() << ") para obtener su complemento respecto al conjunto universal: ";
                cin >> indice;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (indice < 1 || indice > listaSubconjuntos.size()) {
                    cout << "Índice inválido." << endl;
                    break;
                }
                vector<string> complemento = obtenerSubconjuntosFaltantes(conjuntoUniversal, listaSubconjuntos[indice - 1]);
                cout << "\nEl complemento del subconjunto seleccionado es: ";
                imprimirConjunto(complemento);
                resultado = complemento;
                break;
            }
            case 6: { // Complemento relativo: elementos de B que no están en A
                int indiceA, indiceB;
                cout << "Ingrese el índice del subconjunto A (1 a " << listaSubconjuntos.size() << "): ";
                cin >> indiceA;
                cout << "Ingrese el índice del subconjunto B (1 a " << listaSubconjuntos.size() << "): ";
                cin >> indiceB;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (indiceA < 1 || indiceA > listaSubconjuntos.size() ||
                    indiceB < 1 || indiceB > listaSubconjuntos.size()) {
                    cout << "Índices inválidos." << endl;
                    break;
                }
                vector<string> complementoRelativo;
                for (const string &elem : listaSubconjuntos[indiceB - 1]) {
                    if (find(listaSubconjuntos[indiceA - 1].begin(), listaSubconjuntos[indiceA - 1].end(), elem) == listaSubconjuntos[indiceA - 1].end()) {
                        complementoRelativo.push_back(elem);
                    }
                }
                cout << "\nEl complemento relativo (elementos de B que no están en A) es: ";
                imprimirConjunto(complementoRelativo);
                resultado = complementoRelativo;
                break;
            }
            case 7:
                cout << "Saliendo del submenú de operaciones." << endl;
                break;
            default:
                cout << "Opción no válida." << endl;
                break;
        }
        // Muestra los elementos faltantes del conjunto universal respecto al resultado obtenido.
        if (operacion >= 1 && operacion <= 6) {
            vector<string> faltantes = obtenerSubconjuntosFaltantes(conjuntoUniversal, resultado);
            cout << "\nLos elementos faltantes del conjunto universal respecto al resultado de la operación son: ";
            imprimirConjunto(faltantes);
        }
    } while(operacion != 7);
}


/*------------------------------------------------------------------------------
   Función Principal (main)
------------------------------------------------------------------------------*/

// Función main: permite al usuario interactuar con el sistema de generación
// y operaciones sobre conjuntos.
int main() {
    string modeloUniversal;
    // Patrón para validar que la entrada solo contenga letras y números separados por comas.
    string patron = R"(^[A-Za-z0-9]+(,[A-Za-z0-9]+)*$)";
    regex regexPatron(patron);
    
    // Solicita el conjunto universal al usuario.
    vector<string> conjuntoUniversal;
    cout << "Ingrese el conjunto universal (ejemplo: a,b,c,d o 1,2,3,4): ";
    getline(cin, modeloUniversal);
    while (!regex_match(modeloUniversal, regexPatron)) {
        cout << "Entrada inválida. Intente nuevamente: ";
        getline(cin, modeloUniversal);
    }
    conjuntoUniversal = convertirALista(modeloUniversal);
    cout << "Conjunto universal procesado (sin duplicados): ";
    imprimirConjunto(conjuntoUniversal);

    int opcion;
    // Menú principal de opciones
    do {
        cout << "\nMenú de opciones:" << endl;
        cout << "1. Generar todos los subconjuntos" << endl;
        cout << "2. Generar subconjuntos propios" << endl;
        cout << "3. Generar ambos" << endl;
        cout << "4. Ingresar un subconjunto y operar con sus subconjuntos faltantes" << endl;
        cout << "5. Ingresar un nuevo conjunto universal" << endl;
        cout << "6. Mostrar el conjunto potencia" << endl;
        cout << "7. Generar subconjuntos de tamaño n" << endl;
        cout << "8. Ingresar varios subconjuntos y realizar operaciones (submenú)" << endl;
        cout << "9. Salir" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
                cout << "Ingrese el subconjunto (ejemplo: a,c o 1,3): ";
                string subconjuntoStr;
                getline(cin, subconjuntoStr);
                if (regex_match(subconjuntoStr, regexPatron)) {
                    vector<string> subconjunto = convertirALista(subconjuntoStr);
                    bool esSubconjuntoValido = true;
                    for (const string &elem : subconjunto) {
                        if (find(conjuntoUniversal.begin(), conjuntoUniversal.end(), elem) == conjuntoUniversal.end()) {
                            esSubconjuntoValido = false;
                            break;
                        }
                    }
                    if (!esSubconjuntoValido) {
                        cout << "El subconjunto ingresado contiene elementos que no pertenecen al conjunto universal." << endl;
                    } else {
                        vector<string> faltantes = obtenerSubconjuntosFaltantes(conjuntoUniversal, subconjunto);
                        if (faltantes.empty()) {
                            cout << "No hay elementos faltantes en el conjunto universal respecto al subconjunto ingresado." << endl;
                        } else {
                            cout << "Elementos faltantes: ";
                            imprimirConjunto(faltantes);
                        }
                    }
                } else {
                    cout << "Formato inválido." << endl;
                }
                break;
            }
            case 5:
                cout << "Ingrese el nuevo conjunto universal: ";
                getline(cin, modeloUniversal);
                if (regex_match(modeloUniversal, regexPatron)) {
                    conjuntoUniversal = convertirALista(modeloUniversal);
                    cout << "Nuevo conjunto universal actualizado: ";
                    imprimirConjunto(conjuntoUniversal);
                } else {
                    cout << "Entrada inválida. No se actualizó el conjunto." << endl;
                }
                break;
            case 6: {
                vector<vector<string>> potencia = obtenerConjuntoPotencia(conjuntoUniversal);
                cout << "Conjunto potencia:" << endl;
                for (const auto& subset : potencia) {
                    cout << "{ ";
                    bool primero = true;
                    for (const string &elem : subset) {
                        if (!primero) cout << ", ";
                        cout << elem;
                        primero = false;
                    }
                    cout << " }" << endl;
                }
                break;
            }
            case 7: {
                int tam;
                cout << "Ingrese el tamaño deseado para los subconjuntos: ";
                cin >> tam;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                generarSubconjuntosTamanioN(conjuntoUniversal, tam);
                break;
            }
            case 8:
                procesarOperacionesSubconjuntos(conjuntoUniversal);
                break;
            case 9:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción no válida. Intente de nuevo." << endl;
        }
    } while (opcion != 9);

    return 0;
}
