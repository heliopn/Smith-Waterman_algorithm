#include <algorithm>
#include <cctype>
#include <iostream>
#include <random>
#include <vector>

using u32 = uint_least32_t;
using engine = std::mt19937;
using namespace std;

int AlgoGen(int m, int n, string &seq1, string &seq2) {
  m--;
  n--;
  if (m < 0) {
    return 0;
  }
  int result = AlgoGen(m, n, seq1, seq2);
  if (seq1[m] == seq2[n]) {
    return result + 2;
  } else {
    return result - 1;
  }
}

int main(void) {
  random_device os_seed;
  const u32 seed = os_seed();
  int max_value = 0;
  int n, m;
  cin >> m;
  cin >> n;
  string seq1, seq2;
  string maxS1, maxS2;
  cin >> seq1;
  cin >> seq2;
  engine generator(seed);
  if (m > n) {
    int temp = m;
    m = n;
    n = temp;
    string tempS = seq1;
    seq1 = seq2;
    seq2 = tempS;
  }
  // P em função de K
  uniform_int_distribution<u32> distributeK(1, m);
  int k = distributeK(generator);
  int p = 4 * k;
  uniform_int_distribution<u32> distributeJ(0, m - k);
  int j = distributeJ(generator);
  string seqJ = seq1.substr(j, k);
#pragma omp parallel for shared(max_value)
  for (int w = 0; w < p; w++) {
    uniform_int_distribution<u32> distributeI(0, n - k);
    int i = distributeI(generator);
    string seqI = seq2.substr(i, k);
    int actual = AlgoGen(k, k, seqJ, seqI);
#pragma omp critical
    {
      if (actual > max_value) {
        max_value = actual;
        // maxS1 = seqJ;
        // maxS2 = seqI;
      }
    }
  }
  // cout << seq1 << endl;
  // cout << seq2 << endl;
  cout << max_value << endl;
  return 0;
}
