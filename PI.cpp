#include <iostream>
#include <cmath>
#include <vector>
#include "PI.hpp"


#include <iostream>
#include <cmath>


// Konstruktor klasy PI
PI::PI(long long numDivisions, int numThreads)
    : numDivisions(numDivisions), numThreads(numThreads) {
}

// Metoda obliczająca wartość liczby PI
double PI::computePI() {
    // Tablica na wyniki częściowe obliczone przez każdy wątek
    std::vector<double> partialResults(numThreads, 0.0);
    std::vector<std::thread> threads;

    // Rozpoczynamy wątki
    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(&PI::calculatePartialPI, this, i, std::ref(partialResults));
    }

    // Czekamy na zakończenie pracy wszystkich wątków
    for (auto& thread : threads) {
        thread.join();
    }

    // Sumowanie wyników z wszystkich wątków
    double totalResult = 0.0;
    for (const auto& partial : partialResults) {
        totalResult += partial;
    }

    return totalResult;
}

// Funkcja obliczająca część całki przypisaną do danego wątku
void PI::calculatePartialPI(int threadId, std::vector<double>& partialResults) {
    double localResult = 0.0;
    long long start = threadId * (numDivisions / numThreads);
    long long end = (threadId + 1) * (numDivisions / numThreads);

    // Obliczamy część całki dla tego wątku
    for (long long i = start; i < end; ++i) {
        double x = (i + 0.5) / numDivisions;  // Środek podprzedziału
        localResult += 4.0 / (1.0 + x * x);   // Funkcja dla całki
    }

    // Zapisujemy wynik w odpowiedniej pozycji w tablicy
    partialResults[threadId] = localResult / numDivisions;
}