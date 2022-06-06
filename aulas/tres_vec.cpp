#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
  vector<int> X;
  vector<int> Z;
  int n;
  int Y;
  cin >> n;
  for (int i = 0; i < n; i++) {
    X.push_back(i);
  }
  for (auto &e : X) {
    Y = e;
  }
  for (int i = 0; i < n; i++) {
    Z.push_back(2);
  }
  for (int i = 0; i < n; i++) {
    Y = X[i] % Z[i];
  }
  return 0;
}