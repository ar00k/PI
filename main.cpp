#include <iostream>
#include <chrono>
#include <cstdlib> // Dla std::atoi
#include "PI.hpp"

int main(int argc, char* argv[]) {
    // Sprawdzamy, czy podano wystarczającą liczbę argumentów
    if (argc < 3) {
        std::cerr << "Użycie: " << argv[0] << " <numDivisions> <numThreads>" << std::endl;
        return 1; // Kod błędu
    }

    // Pobieramy argumenty z linii poleceń
    long long numDivisions = std::atoll(argv[1]);
    int numThreads = std::atoi(argv[2]);

    // Stworzenie obiektu kalkulatora PI
    PI calculator(numDivisions, numThreads);

    // Mierzymy czas obliczeń
    auto start = std::chrono::high_resolution_clock::now();
    double pi = calculator.computePI();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    // Zwracamy wyniki w standardowym wyjściu
    std::cout << "PI: " << pi << std::endl;
    std::cout << "Czas: " << duration.count() << " sekund" << std::endl;

    return 0; // Kod sukcesu
}