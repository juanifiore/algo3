#include <iostream>
#include <string>

int main() {
    std::string line;
    while (!std::getline(std::cin, line).fail()) {
        std::cout << "Leído: " << line << std::endl;
    }

    std::cout << "Fin de la entrada o línea vacía encontrada." << std::endl;
    return 0;
}

