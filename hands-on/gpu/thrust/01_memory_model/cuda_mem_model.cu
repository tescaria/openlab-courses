// C++ standard headers
#include <cassert>
#include <iostream>
#include <ranges>
#include <thrust/copy.h>
#include <thrust/device_vector.h>
#include <thrust/execution_policy.h>
#include <thrust/host_vector.h>
#include <thrust/sequence.h>

// CUDA headers
#include <cuda_runtime.h>

// local headers
#include "cuda_check.h"

// Here you can set the device ID that was assigned to you
#define MYDEVICE 0

///////////////////////////////////////////////////////////////////////////////
// Program main
///////////////////////////////////////////////////////////////////////////////
int main() {
  // Choose one CUDA device
  CUDA_CHECK(cudaSetDevice(MYDEVICE));

  // Pointer and dimension for host memory
  int dim = 1024;
  // Part 1 of 6: allocate a buffer in host memory with increasing values from 0
  // to dimA - 1
  auto h_buffer = thrust::host_vector<int>(dim);
  thrust::sequence(h_buffer.begin(), h_buffer.end());

  // Part 2 of 6: allocate two buffers in device memory
  auto d_buffer1 = thrust::device_vector<int>(dim);
  auto d_buffer2 = thrust::device_vector<int>(dim);

  // BONUS: use at least two different methods for copying the data
  // Part 3 of 6: copy the content of the host buffer to the first device buffer
  d_buffer1 = h_buffer;

  // Part 4 of 6: copy the content of the first device buffer to the second
  // device buffer
  d_buffer2 = d_buffer1;

  // Part 5 of 6: set all the values in the host buffer to zero
  thrust::fill(h_buffer.begin(), h_buffer.end(), 0);

  // Part 6 of 6: copy the contant back to the host buffer
  h_buffer = d_buffer2;


  // Verify the data on the host is correct
  assert(std::ranges::equal(h_buffer, std::views::iota(0, dim)));

  // If the program makes it this far, then the results are correct and
  // there are no run-time errors.  Good work!
  std::cout << "Correct!" << std::endl;

  return 0;
}
