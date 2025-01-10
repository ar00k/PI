#ifndef PI_HPP
#define PI_HPP

#include <vector>
#include <thread>

/**
 * @class PI
 * @brief Klasa do obliczania wartości PI za pomocą wielu wątków.
 *
 * Ta klasa zapewnia funkcjonalność obliczania wartości PI poprzez podzielenie
 * obliczeń na wiele podziałów i użycie wielu wątków do wykonywania obliczeń
 * równolegle.
 */

 /**
    * @brief Konstruktor nowego obiektu PI.
    *
    * @param numDivisions Liczba podziałów, na które zostaną podzielone obliczenia.
    * @param numThreads Liczba wątków używanych do obliczeń.
    */

    /**
     * @brief Oblicza wartość PI.
     *
     * Ta funkcja oblicza wartość PI, używając określonej liczby podziałów
     * i wątków.
     *
     * @return Obliczona wartość PI.
     */

     /**
        * @brief Oblicza częściową wartość PI dla danego wątku.
        *
        * Ta funkcja jest używana wewnętrznie do obliczania częściowej wartości PI
        * dla konkretnego wątku. Wyniki są przechowywane w podanym wektorze.
        *
        * @param threadId ID wątku wykonującego obliczenia.
        * @param partialResults Referencja do wektora, w którym będą przechowywane częściowe wyniki.
        */
class PI {
    public:
    PI(long long numDivisions, int numThreads);
    double computePI();

    private:
    long long numDivisions;
    int numThreads;

    void calculatePartialPI(int threadId, std::vector<double>& partialResults);
};

#endif // PI_HPP