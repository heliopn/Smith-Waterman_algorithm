#include <algorithm>
#include <iostream>
#include <thrust/host_vector.h>
#include <thrust/device_vector.h>
#include <thrust/generate.h>
#include <thrust/functional.h>
#include <thrust/transform.h>
#include <thrust/copy.h>
#include <cstdlib>
#include <iomanip>
#include <tuple>

using namespace std;

struct up_comp
{
    int up, l_up;
    char chr;
    up_comp(int chr_) : chr(chr_){};
    __host__ __device__ int operator()(const thrust::tuple<char, int, int> &tup)
    {
        int act_val = thrust::get<0>(tup);

        if (chr == thrust::get<2>(tup))
        {
            l_up = act_val + 2;
        }
        else
        {
            l_up = act_val - 1;
        }
        up = thrust::get<1>(tup) - 1;
        if (l_up > up && l_up > 0)
        {
            return l_up;
        }
        else if (up >= l_up && up > 0)
        {
            return up;
        }
        return act_val;
    }
};

struct left_comp
{
    __host__ __device__ int operator()(const int &x, const int &y)
    {
        int left, act;
        left = x;
        act = y;

        if (act >= left && act > 0)
        {
            return act;
        }
        else if (left > act && left > 0)
        {
            return left;
        }
        return 0;
    }
};

int main()
{
    int m, n;
    int as, bs, max, fixMax;
    string seq1, seq2;

    cin >> m;
    cin >> n;

    bs = -(m + n);

    cin >> seq1;
    cin >> seq2;

    seq1 = '_' + seq1;
    seq2 = '_' + seq2;

    thrust::device_vector<char> seq1_GPU(m + 1);
    thrust::device_vector<char> seq2_GPU(n + 1);
    thrust::device_vector<int> res1(n + 1);
    thrust::device_vector<int> copy_res1(n + 1);

    if (m > n)
    {
        max = n;
     fixMax = n;
    }
    else
    {
        max = m;
     fixMax = m;
    }

    for (int i = 0; i < m + 1; i++)
    {
        seq1_GPU[i] = seq1[i];
    }
    for (int j = 0; j < n + 1; j++)
    {
        seq2_GPU[j] = seq2[j];
    }

    thrust::fill(copy_res1.begin(), copy_res1.end(), 0);

    while (max > 0)
    {
        for (int i = 0; i <= (m + 1 - max); i++)
        {
            for (int j = 0; j <= (n + 1 - max); j++)
            {
                thrust::fill(res1.begin(), res1.end(), 0);
                for (int k = 0; k <= max; k++)
                {
                    thrust::transform(thrust::make_zip_iterator(thrust::make_tuple(res1.begin(),
                                                                                   res1.begin() + 1,
                                                                                  seq2_GPU.begin() + 1 + j)),
                                      thrust::make_zip_iterator(thrust::make_tuple(res1.begin() + max,
                                                                                   res1.begin() + 1 + max,
                                                                                    seq2_GPU.end() + 1 + j + max)),
                                      copy_res1.begin() + 1,
                                      up_comp(seq1_GPU[k]));

                    thrust::inclusive_scan(copy_res1.begin(), copy_res1.begin() + max, res1.begin(), left_comp());

                    as = thrust::reduce(res1.begin(), res1.end(), 0, thrust::maximum<int>());

                    if (as > bs)
                    {
                        bs = as;
                    }
                }
            }
        }
        max -= 1;
    }
    if(seq1[1]==seq2[1]) bs += 2;
    cout << bs << endl;
    return 0;
}