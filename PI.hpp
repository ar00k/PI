#ifndef PI_HPP
#define PI_HPP

#include <vector>
#include <thread>

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