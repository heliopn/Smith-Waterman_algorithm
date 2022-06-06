#include <chrono>
#include <iostream>
#include <omp.h>
#include <vector>
using namespace std::chrono;

using namespace std;

int main() {
  auto start = high_resolution_clock::now();
  int result = 0;
  omp_set_num_threads(4);
#pragma omp parallel shared(result)
  {
#pragma omp critical
    result += 1;
  }
  auto stop = high_resolution_clock::now();
  cout << result << endl;
  auto duration = duration_cast<microseconds>(stop - start);
  cout << "Seconds: " << duration.count() << endl;
  result = 0;
  start = high_resolution_clock::now();
#pragma omp parallel reduction(+ : result)
  { result++; }
  stop = high_resolution_clock::now();
  cout << result << endl;
  duration = duration_cast<microseconds>(stop - start);
  cout << "Seconds: " << duration.count() << endl;
  return 0;
}