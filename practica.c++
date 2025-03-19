#include <iostream>
#include <list>
#include <map>


int main() {
    int edad = 25;          // Variable entera
    double altura = 1.75;   // Variable de punto flotante
    char inicial = 'A';     // Variable de carácter
    bool esMayor = true;    // Variable booleana

    std::cout << "Edad: " << edad << std::endl;
    std::cout << "Altura: " << altura << std::endl;
    std::cout << "Inicial: " << inicial << std::endl;
    std::cout << "Es mayor de edad: " << esMayor << std::endl;

    int numeros[] = {10, 20, 30, 40, 50};  // Arreglo de enteros

    // Acceder a elementos
    std::cout << "Primer elemento: " << numeros[0] << std::endl;

    // Recorrer el arreglo
    for (int i = 0; i < 5; i++) {
        std::cout << "Elemento " << i << ": " << numeros[i] << std::endl;
    }

    for (int i = 1; i <= 5; i++) {
        std::cout << "Iteración " << i << std::endl;
    }

    int contador = 0;
    while (contador < 5) {
        std::cout << "Valor: " << contador << std::endl;
        contador++;
    }

    int numero;
    do {
        std::cout << "Ingrese un número positivo: ";
        std::cin >> numero;
    } while (numero <= 0);

    std::cout << "Número válido ingresado: " << numero << std::endl;

    edad = 1;
    std::cout << "Ingrese su edad: ";
    std::cin >> edad;

    if (edad >= 18) {
        std::cout << "Eres mayor de edad." << std::endl;
    } else {
        std::cout << "Eres menor de edad." << std::endl;
    }

    int opcion;
    std::cout << "Seleccione una opción (1-3): ";
    std::cin >> opcion;

    switch (opcion) {
        case 1:
            std::cout << "Elegiste la opción 1" << std::endl;
            break;
        case 2:
            std::cout << "Elegiste la opción 2" << std::endl;
            break;
        case 3:
            std::cout << "Elegiste la opción 3" << std::endl;
            break;
        default:
            std::cout << "Opción no válida" << std::endl;
    }

    std::list<int> numerosLista = {10, 20, 30, 40, 50};

    // Agregar elementos
    numerosLista.push_back(60);  // Al final
    numerosLista.push_front(5);  // Al inicio

    // Recorrer la lista
    std::cout << "Elementos de la lista: ";
    for (int num : numerosLista) {
        std::cout << num << " ";
    }
    std::cout << std::endl;


    std::map<int, std::string> estudiantes;

    // Agregar elementos al mapa
    estudiantes[101] = "Juan";
    estudiantes[102] = "María";
    estudiantes[103] = "Carlos";

    // Recorrer el mapa
    std::cout << "Lista de estudiantes:" << std::endl;
    for (const auto& par : estudiantes) {
        std::cout << "ID: " << par.first << " - Nombre: " << par.second << std::endl;
    }

    // Buscar un elemento
    int clave = 102;
    if (estudiantes.find(clave) != estudiantes.end()) {
        std::cout << "Estudiante con ID " << clave << ": " << estudiantes[clave] << std::endl;
    } else {
        std::cout << "Estudiante no encontrado." << std::endl;
    }

    return 0;
}
