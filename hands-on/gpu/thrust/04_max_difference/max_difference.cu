
#include <thrust/device_vector.h>
#include <thrust/host_vector.h>
#include <thrust/tuple.h>

#include <thrust/execution_policy.h>
#include <thrust/iterator/zip_iterator.h>
#include <thrust/iterator/transform_iterator.h>
#include <thrust/extrema.h>
#include <iostream>

int main() {
  auto h_v1 = thrust::host_vector<int>{1, 7, 2, 8, -1, 0};
  auto h_v2 = thrust::host_vector<int>{5, 2, 6, -3, 9, 4};

  thrust::device_vector<int> d_v1 = h_v1;
  thrust::device_vector<int> d_v2 = h_v2;

  // Part 1 of 1: Compute the maximum difference between the two vectors
  // Hint: use transform and zip iterators
  auto begin = thrust::make_zip_iterator(thrust::make_tuple(d_v1.begin(), d_v2.begin()));
  auto end = begin + 6;
  auto difference = [] __host__ __device__ (thrust::tuple<int, int> x){
    return abs(thrust::get<0>(x) - thrust::get<1>(x));
  };

  auto transf_begin = thrust::make_transform_iterator(begin, difference);
  auto transf_end = transf_begin + 6;

  auto max_difference = thrust::reduce(thrust::device, transf_begin, transf_end, 0, thrust::maximum<int>());

  std::cout << "The max difference is " << max_difference << std::endl;
}
