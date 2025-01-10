#ifndef PI_HPP
#define PI_HPP

#include <vector>
#include <thread>

/**
 * @class PI
 * @brief A class to compute the value of PI using multiple threads.
 *
 * This class provides functionality to compute the value of PI by dividing the
 * computation into multiple divisions and using multiple threads to perform the
 * calculations in parallel.
 */

 /**
  * @brief Constructs a new PI object.
  *
  * @param numDivisions The number of divisions to split the computation into.
  * @param numThreads The number of threads to use for the computation.
  */

  /**
   * @brief Computes the value of PI.
   *
   * This function computes the value of PI using the specified number of divisions
   * and threads.
   *
   * @return The computed value of PI.
   */

   /**
    * @brief Calculates a partial value of PI for a given thread.
    *
    * This function is used internally to calculate a partial value of PI for a
    * specific thread. The results are stored in the provided vector.
    *
    * @param threadId The ID of the thread performing the calculation.
    * @param partialResults A reference to a vector where the partial results will be stored.
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