#include <algorithm>
#include <iostream>
#include <thrust/transform.h>
#include <thrust/functional.h>
#include <thrust/fill.h>
#include <thrust/device_vector.h>
#include <thrust/sequence.h>
using namespace std;

int main()
{
    thrust::device_vector<int> X(99999999, 0);
    thrust::device_vector<int> Y(99999999, 0);
    thrust::device_vector<int> Z(99999999, 0);
    thrust::sequence(X.begin(), X.end());
    thrust::transform(X.begin(), X.end(), Y.begin(), thrust::negate<int>());
    thrust::fill(Z.begin(), Z.end(), 2);
    thrust::transform(X.begin(), X.end(), Z.begin(), Y.begin(), thrust::modulus<int>());
    return 0;
}