#ifndef PI_H
#define PI_H

#include <vector>
#include <thread>
#include <atomic>
#include <chrono>

class PiCalculator {
    private:
    // Liczba podziałów przedziału
    unsigned long long numDivisions;
    // Liczba wątków
    unsigned int numThreads;
    // Wynik końcowy (częściowe wyniki z wątków)
    std::atomic<double> result;

    // Funkcja dla wątku: obliczanie części całki
    void calculatePartial(unsigned long long start, unsigned long long end);

    public:
    // Konstruktor
    PiCalculator(unsigned long long numDivisions, unsigned int numThreads);

    // Funkcja obliczająca PI
    double calculate();

    // Funkcja pomiaru czasu obliczeń
    double measureExecutionTime(double& piResult);
};

#endif // PI_H