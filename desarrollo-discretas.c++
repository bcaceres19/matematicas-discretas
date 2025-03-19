#include <iostream>
#include <list>
#include <map>
#include <string>
#include <regex>
#include <vector>
#include <cmath>
#include <sstream>

// Función para generar todos los subconjuntos de un conjunto
void generarSubconjuntos(const std::vector<int>& conjunto) {
    int n = conjunto.size();
    int totalSubconjuntos = pow(2, n); // 2^n subconjuntos

    std::cout << "Total de subconjuntos: " << totalSubconjuntos << std::endl;
    std::cout << "Los subconjuntos son:\n";

    for (int mascara = 0; mascara < totalSubconjuntos; mascara++) {
        std::cout << "{ ";
        bool primero = true;
        for (int j = 0; j < n; j++) {
            if (mascara & (1 << j)) {  // Verifica si el bit está encendido
                if (!primero) std::cout << ", ";
                std::cout << conjunto[j];
                primero = false;
            }
        }
        std::cout << " }\n";
    }
}

// Función para generar y mostrar los subconjuntos propios (sin el vacío y el conjunto completo)
void generarSubconjuntosPropios(const std::vector<int>& conjunto) {
    int n = conjunto.size();
    int totalSubconjuntos = pow(2, n); // 2^n subconjuntos en total

    std::cout << "Subconjuntos propios:\n";
    
    for (int mascara = 1; mascara < totalSubconjuntos - 1; mascara++) { // Evita el vacío y el conjunto completo
        std::cout << "{ ";
        bool primero = true;
        for (int j = 0; j < n; j++) {
            if (mascara & (1 << j)) {  // Verifica si el bit está encendido
                if (!primero) std::cout << ", ";
                std::cout << conjunto[j];
                primero = false;
            }
        }
        std::cout << " }\n";
    }
}

std::vector<int> convertirALista(const std::string& str) {
    std::vector<int> resultado;
    std::stringstream ss(str);
    std::string temp;
    
    while (std::getline(ss, temp, ',')) { 
        if (!temp.empty()) { // Evita el último carácter si hay una coma final
            resultado.push_back(std::stoi(temp)); 
        }
    }

    return resultado;
}

int main() {

    std::string modeloUnivesal;
    std::string regex;

    while (true)
    {
        std::cout << "Ingrese el modelo universal: ";
        std::cin >> modeloUnivesal;

        std::regex patron(R"(^[0-9]+(,[0-9]+)*$)");

        if (std::regex_match(modeloUnivesal, patron)) {
            std::cout << "Cadena válida" << std::endl;
            const std::vector<int> conjuntoUniversal = convertirALista(modeloUnivesal);
            generarSubconjuntos(conjuntoUniversal);
            generarSubconjuntosPropios(conjuntoUniversal);
            break;
        } 
    }
    
}