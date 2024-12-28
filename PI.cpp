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
}

