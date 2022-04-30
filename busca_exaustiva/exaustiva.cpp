#include <algorithm>
#include <cctype>
#include <iostream>
#include <random>
#include <set>
#include <string>

using namespace std;

struct cell {
  int value;
  int origin_j;
  int origin_i;
};

void allCombinations(auto& subSeqs,auto& dna){
    int dna_size = dna.size();
    for(int i=0;i<dna_size;i++){
        for(int j=0;j<dna_size+1;j++){
          subSeqs.insert(dna.substr(i,j));
        }
    }
}

int AlgoGen(int m, int n, auto& seq1, auto& seq2) {
  m--;
  n--;
  if (m < 0) {
    return 0;
  }
  int result = AlgoGen(m - 1, n - 1, seq1, seq2);
  if (seq1[m] == seq2[n]) {
    return result + 2;
  } else {
    return result - 1;
  }
}

int Smith(auto& matrix,auto& seq2, auto& seq1){
  cell max_cell;
  max_cell.value = 0;
  for (int j = 0; (unsigned)j < seq2.size(); j++) {
    for (int i = 0; (unsigned)i < seq1.size(); i++) {
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
        }
        matrix[j][i] = ref;
      }
    }
  }
  return max_cell.value;
}

int main(void){
    int dnaA_size, dnaB_size;
    string dnaA, dnaB;

    cin >> dnaA_size >> dnaB_size;
    cin >> dnaA >> dnaB;

    set<string> subseq_A = {};
    set<string> subseq_B = {};

    allCombinations(subseq_A,dnaA);
    allCombinations(subseq_B,dnaB);

    // for (set<string>::iterator i = subseq_A.begin(); i != subseq_A.end(); i++) {
    //   string element = *i;
    //   cout << element << endl;
    // }
    int max = 0;
    int count = 0;
    string subBig, subSmall;
    string maxSA,maxSB;
    for(auto& subA : subseq_A){
        for(auto& subB : subseq_B){
          if(subA == "" || subB == ""){
            continue;
          } else {
            if(subA.length() == subB.length()){
              count = AlgoGen(subA.size(),subB.size(),subA, subB);
              if(count > max){
                maxSA = subA;
                maxSB = subB;
                max = count;
              }
            } 
            else {
              subBig = " "+subA;
              subSmall = " "+subB;
              if (subB.size() > subA.size()) {
                  string tempS = " "+subA;
                  subBig = " "+subB;
                  subSmall = tempS;
              }
              cell cell_t;
              cell_t.value = 0;
              vector<vector<cell>> matrix(subBig.size(),
                            vector<cell>(subSmall.size(), cell_t));
              count = Smith(matrix,subBig,subSmall);
              if(count > max){
                maxSA = subA;
                maxSB = subB;
                max = count;
              } 
            }
          }
        }
    }
    cout << max << endl;
    // cout << "Sequencia 1: " << maxSA << endl;
    // cout << "Sequencia 2: " << maxSB << endl;
    return 0;
}