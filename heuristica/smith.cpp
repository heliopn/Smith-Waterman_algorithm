#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct cell {
  int value;
  int origin_j;
  int origin_i;
};

struct resVault {
  string v1, v2, v3;
  int min_i, min_j;
  int includ_i = 0, includ_j = 0;
};

resVault seq_construct(vector<vector<cell>>& matrix, cell celula, string seq1,
                       string seq2, string seq3, int ati, int atj) {
  cell anterior;
  resVault resp;
  if (celula.value == 2) {
    resp.v1 = seq1;
    resp.v2 = seq2;
    resp.v3 += "*";
    resp.min_i = celula.origin_i;
    resp.min_j = celula.origin_j;
    return resp;
  }
  anterior = matrix[celula.origin_j][celula.origin_i];
  resp = seq_construct(matrix, anterior, seq1, seq2, seq3, celula.origin_i,
                       celula.origin_j);
  int in_i = ati - celula.origin_i;
  int in_j = atj - celula.origin_j;
  if (in_i == 0 && in_j) {
    resp.v1.insert(celula.origin_i + 1, 1, '_');
    resp.v3 += " ";
    // resp.includ_i += 1;
  } else if (in_i && in_j == 0) {
    resp.v2.insert(celula.origin_j + 1, 1, '_');
    resp.v3 += " ";
    // resp.includ_j += 1;
  } else {
    if (abs(anterior.value-celula.value)==1){
      resp.v3 += "|";
    }else{
      resp.v3 += "*";
    }
  }

  return resp;
}

int main() {
  int max_i = 0;
  int max_j = 0;
  int n;
  cin >> n;
  int m;
  cin >> m;
  string seq1;
  cin >> seq1;
  string seq2;
  cin >> seq2;
  seq1 = " " + seq1;
  seq2 = " " + seq2;
  string seq3;
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
        if (matrix[j - 1][i - 1].value + ref.value >= matrix[j][i - 1].value -1 &&
            matrix[j - 1][i - 1].value + ref.value >= matrix[j - 1][i].value -1) {
          ref.value += matrix[j - 1][i - 1].value;
          ref.origin_i = i - 1;
          ref.origin_j = j - 1;
        } else if (matrix[j][i - 1].value -1 >
                       matrix[j - 1][i - 1].value + ref.value && 
                   matrix[j][i - 1].value > matrix[j - 1][i].value) {
          // ref.value += matrix[j][i - 1].value;
          ref.value = matrix[j][i - 1].value - 1;
          ref.origin_i = i - 1;
          ref.origin_j = j;
        } else if (matrix[j - 1][i].value -1 >
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
          max_i = i;
          max_j = j;
        }
        matrix[j][i] = ref;
      }
    }
  }
  // cout << seq1 << endl;
  // cout << seq2 << endl;
  // for (int j = 0; (unsigned)j < seq2.length(); j++) {
  //   for (int i = 0; (unsigned)i < seq1.length(); i++) {
  //     cout << matrix[j][i].value << " ";
  //     // if (j == 3 and i == 1)
  //     //   cout << matrix[j][i].origin_i << "." << matrix[j][i].origin_j;
  //   }
  //   cout << endl;
  // }
  resVault result;
  result = seq_construct(matrix, max_cell, seq1, seq2, seq3, max_i, max_j);
  result.v1.erase(0, 1);
  result.v2.erase(0, 1);
  result.v1.erase(0, result.min_i);
  result.v2.erase(0, result.min_j);

  // int r2 = max_cell.origin_j + 1 + result.includ_j;
  // int r1 = max_cell.origin_i + 1 + result.includ_i;
  // cout << r2 << "lengh: " << result.v2.length() << endl;
  // cout << r1 << "lengh: " << result.v1.length() << endl;
  if (result.v1.length() < result.v2.length()) {
    result.v1.erase(result.v1.length(), result.v1.length());
    result.v2.erase(result.v1.length(), result.v2.length());
  } else {
    result.v1.erase(result.v2.length(), result.v1.length());
    result.v2.erase(result.v2.length(), result.v2.length());
  }
  cout << result.v2 << endl;
  cout << result.v3 << endl;
  cout << result.v1 << endl;
  cout<<"Max: "<<max_cell.value<<endl;
}
