#include <iostream>

int main() {
    int n;
    while (std::cin >> n) {
        std::cout << "Leído: " << n << std::endl;
    }

    if (std::cin.eof()) {
        std::cout << "Fin de la entrada." << std::endl;
    } else if (std::cin.fail()) {
        std::cout << "Entrada no válida o error de lectura." << std::endl;
    }

    return 0;
}

