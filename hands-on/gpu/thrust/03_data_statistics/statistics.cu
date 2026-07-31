
#include <random>
#include <thrust/device_vector.h>
#include <thrust/execution_policy.h>
#include <thrust/host_vector.h>
#include <thrust/reduce.h>
#include <thrust/transform.h>

void generate_data(thrust::host_vector<float> &data) {
  std::mt19937 gen;
  std::uniform_real_distribution<float> dist(0.f, 2.f);
  std::generate(data.begin(), data.end(), [&] { return dist(gen); });
}

int main() {
  int N = 1024;
  // Part 1: Allocate an host vector of floats
  auto h_data = thrust::host_vector<float>(N);

  // generate the dandom data
  generate_data(h_data);

  // Part 2 : Allocate a device buffer and copy data from the host
  auto d_data = thrust::device_vector<float>(N);
  d_data = h_data;

  // Part 3: Compute the mean of the values
  auto mean = thrust::reduce(thrust::device, d_data.begin(), d_data.end()) / N;
  std::cout << "The mean is equal to " << mean << std::endl;

  // Part 4: Create an intermediary buffer and fill it with the squared
  // differences between the data values and the mean
  auto squared_differences = thrust::device_vector<float>(N);
  auto squared_diff = [mean] __host__ __device__ (float x) {return (x-mean)*(x-mean);};
  thrust::transform(thrust::device, d_data.begin(), d_data.end(), squared_differences.begin(), squared_diff);

  // Part 5: Compute the standard deviation
  auto variance = thrust::reduce(thrust::device, squared_differences.begin(), squared_differences.end()) / N;
  auto std = std::sqrt(variance);
  std::cout << "The standard deviation is equal to " << std << std::endl;

  // Part 6: Go back to steps 4 and 5, try to compute the standard deviation
  // without the intermediary buffer
  auto begin = thrust::make_transform_iterator(d_data.begin(), squared_diff);
  auto end = begin + N;
  auto variance2 = thrust::reduce(thrust::device, begin, end) / N;
  auto std2 = std::sqrt(variance2);
  std::cout << "The standard deviation is equal to " << std2 << std::endl;
  
}
