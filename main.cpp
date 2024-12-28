#include <iostream>
#include <chrono>
#include "PI.hpp"

int main() {
    long long numDivisions = 1000000000;  // Liczba podziałów przedziału całki
    int numThreads = 8;  // Liczba wątków, które chcemy uruchomić

    // Stworzenie obiektu kalkulatora PI
    PI calculator(numDivisions, numThreads);

    // Mierzymy czas obliczeń
    auto start = std::chrono::high_resolution_clock::now();
    double pi = calculator.computePI();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    // Wyświetlenie wyniku
    std::cout << "Przybliżona wartość liczby PI: " << pi << std::endl;
    std::cout << "Czas obliczeń: " << duration.count() << " sekund" << std::endl;

    return 0;
}
