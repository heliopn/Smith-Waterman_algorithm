#include <algorithm>
#include <cctype>
#include <iostream>
#include <random>
#include <vector>

using u32 = uint_least32_t;
using engine = std::mt19937;
using namespace std;

struct cell {
  int value;
  int origin_j;
  int origin_i;
};

int Smith(int m, int n, string seq1, string seq2) {
  seq1 = " " + seq1;
  seq2 = " " + seq2;
  cell cell_t;
  cell_t.value = 0;
  cell max_cell;
  max_cell.value = 0;
  vector<vector<cell>> matrix(seq2.length(),
                              vector<cell>(seq1.length(), cell_t));
  for (int j = 0; (unsigned)j < seq2.length(); j++) {
    for (int i = 0; (unsigned)i < seq1.length(); i++) {
      if (j > 0 && i > 0) {
        cell ref;
        ref.value = 0;
        if (seq1[i] == seq2[j]) {
          ref.value += 2;
        } else {
          ref.value -= 1;
        }
        if (matrix[j - 1][i - 1].value + ref.value >= matrix[j][i - 1].value &&
            matrix[j - 1][i - 1].value + ref.value >= matrix[j - 1][i].value) {
          ref.value += matrix[j - 1][i - 1].value;
          ref.origin_i = i - 1;
          ref.origin_j = j - 1;
        } else if (matrix[j][i - 1].value >
                       matrix[j - 1][i - 1].value + ref.value &&
                   matrix[j][i - 1].value > matrix[j - 1][i].value) {
          // ref.value += matrix[j][i - 1].value;
          ref.value = matrix[j][i - 1].value - 1;
          ref.origin_i = i - 1;
          ref.origin_j = j;
        } else if (matrix[j - 1][i].value >
                       matrix[j - 1][i - 1].value + ref.value &&
                   matrix[j - 1][i].value > matrix[j][i - 1].value) {
          // ref.value += matrix[j - 1][i].value;
          ref.value = matrix[j - 1][i].value - 1;
          ref.origin_i = i;
          ref.origin_j = j - 1;
        }
        if (ref.value < 0) {
          ref.value = 0;
        }

        if (max_cell.value < ref.value) {
          max_cell = ref;
        }
        matrix[j][i] = ref;
      }
    }
  }
  return max_cell.value;
}

int main(void) {
  random_device os_seed;
  const u32 seed = os_seed();
  int max_value = 0;
  int n, m, count;
  count = 10;
  cin >> m;
  cin >> n;
  string seq1, seq2;
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
  while (count > 0) {
    uniform_int_distribution<u32> distributeK(1, m);
    int k = distributeK(generator);
    uniform_int_distribution<u32> distributeJ(0, m - k);
    uniform_int_distribution<u32> distributeI(0, n - k);
    int j = distributeJ(generator);
    int i = distributeI(generator);
    string seqJ = seq1.substr(j, k);
    string seqI = seq2.substr(i, k);
    int actual = Smith(k, k, seqJ, seqI);
    if (actual > max_value) {
      max_value = actual;
      count = 10;
    } else if (actual == max_value) {
      count--;
    }
  }
  cout << max_value << endl;
  return 0;
}
