#include <iostream>
#include <chrono>
#include <cmath>
#include <vector>
#include "PI.hpp"

PI::PI(long long numDivisions, int numThreads)
    : numDivisions(numDivisions), numThreads(numThreads) {
}

double PI::computePI() {
    // Mierzenie czasu
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<double> partialResults(numThreads, 0.0);
    std::vector<std::thread> threads;

    for (int i = 0; i < numThreads; ++i) {
        threads.emplace_back(&PI::calculatePartialPI, this, i, std::ref(partialResults));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    double totalResult = 0.0;
    for (const auto& partial : partialResults) {
        totalResult += partial;
    }

    // Mierzenie końca czasu
    auto end = std::chrono::high_resolution_clock::now();

    // Obliczanie różnicy czasowej
    std::chrono::duration<double> duration = end - start;
    std::cout << "Czas obliczeń (w C++): " << duration.count() << " sekund" << std::endl;

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