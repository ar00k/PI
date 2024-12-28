#include <iostream>
#include <cmath>
#include <vector>
#include <thread>
#include <chrono>
#include <atomic>
#include "PI.hpp"


#include <iostream>
#include <cmath>

// Konstruktor
PI::PI(unsigned long long numDivisions, unsigned int numThreads)
    : numDivisions(numDivisions), numThreads(numThreads), result(0.0) {
}

// Funkcja dla wątku: obliczanie części całki
void PI::calculatePartial(unsigned long long start, unsigned long long end) {
    double localResult = 0.0;
    for (unsigned long long i = start; i < end; ++i) {
        double x = (i + 0.5) / numDivisions;
        localResult += 4.0 / (1.0 + x * x);
    }
    result.fetch_add(localResult); // Dodawanie częściowego wyniku do wyniku globalnego
}

// Główna funkcja obliczająca PI
double PI::calculate() {
    result = 0.0; // Resetowanie wyniku
    std::vector<std::thread> threads;

    // Liczba iteracji na wątek
    unsigned long long iterationsPerThread = numDivisions / numThreads;

    // Uruchamianie wątków
    for (unsigned int t = 0; t < numThreads; ++t) {
        unsigned long long start = t * iterationsPerThread;
        unsigned long long end = (t == numThreads - 1) ? numDivisions : start + iterationsPerThread;
        threads.emplace_back(&PI::calculatePartial, this, start, end);
    }

    // Czekanie na zakończenie wątków
    for (auto& thread : threads) {
        thread.join();
    }

    // Skalowanie wyniku do ostatecznej wartości
    return result / numDivisions;
}

// Funkcja pomiaru czasu obliczeń
double PI::measureExecutionTime(double& piResult) {
    auto startTime = std::chrono::high_resolution_clock::now();
    piResult = calculate();
    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsedTime = endTime - startTime;
    return elapsedTime.count();
}
