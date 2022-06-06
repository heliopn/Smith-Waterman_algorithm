#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
using namespace std;
using ufloat = float;
using engine = std::mt19937;
int main() {
  float sum = 0;
  float N = 0;
  random_device os_seed;

  cin >> N;
  uniform_real_distribution<ufloat> distributeY(0, 1);
  uniform_real_distribution<ufloat> distributeX(0, 1);
#pragma omp parallel for reduction(+ : sum)
  for (int i = 0; i < N; i++) {
    const ufloat seed = i;
    engine generator(seed);
    float x = distributeX(generator);
    float y = distributeX(generator);
    if ((x * x) + (y * y) <= 1) {
      sum++;
    }
  }
  cout << (4 * (sum / N)) << endl;
}