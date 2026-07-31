#include <algorithm>
#include <cassert>
#include <chrono>
#include <execution>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

using Clock = std::chrono::steady_clock;
using Duration = std::chrono::duration<float>;

int main() {
  // define a pseudo-random number generator engine and seed it using an actual
  // random device
  std::random_device rd;
  std::default_random_engine eng{rd()};

  int const MAX_N = 100;
  std::uniform_int_distribution<int> uniform_dist{1, MAX_N};

  // fill a vector with SIZE random numbers
  int const SIZE = 10'000'000;
  std::vector<int> v;
  v.reserve(SIZE);
  std::generate_n(std::back_inserter(v), SIZE,
                  [&] { return uniform_dist(eng); });

  {
    std::cout << "Sum with accumulate:" << '\n';
    auto t0 = Clock::now();
    // sum all the elements of the vector with std::accumulate
    auto sum = std::accumulate(v.begin(), v.end(), 0);
    std::cout << sum << '\n';
    auto t1 = Clock::now();
    Duration d = t1 - t0;
    std::cout << " in " << d.count() << " s\n";
  }

  {
    std::cout << "Sum with reduce, sequential policy:" << '\n';
    auto t0 = Clock::now();
    // sum all the elements of the vector with std::reduce, sequential policy
    // NB you need to pass the initial value
    auto sum = std::reduce(std::execution::seq, v.begin(), v.end());
    std::cout << sum << '\n';
    auto t1 = Clock::now();
    Duration d = t1 - t0;
    std::cout << " in " << d.count() << " s\n";
  }

  {
    std::cout << "Sum with reduce, parallel policy:" << '\n';
    auto t0 = Clock::now();
    // sum all the elements of the vector with std::reduce, parallel policy
    // NB you need to pass the initial value
    auto sum = std::reduce(std::execution::par, v.begin(), v.end());
    std::cout << sum << '\n';
    auto t1 = Clock::now();
    Duration d = t1 - t0;
    std::cout << " in " << d.count() << " s\n";
  }

  {
    std::cout << "Sort:" << '\n';
    auto copy1 = v;
    auto t0 = Clock::now();
    // sort the vector with std::sort
    std::sort(copy1.begin(), copy1.end());
    auto t1 = Clock::now();
    Duration d = t1 - t0;
    std::cout << " in " << d.count() << " s\n";
  }

  {
    std::cout << "Sort, sequential policy:" << '\n';
    auto copy2 = v;
    auto t0 = Clock::now();
    // sort the vector with std::sort, sequential policy
    std::sort(std::execution::seq, copy2.begin(), copy2.end());
    auto t1 = Clock::now();
    Duration d = t1 - t0;
    std::cout << " in " << d.count() << " s\n";
  }

  {
    std::cout << "Sort, parallel policy:" << '\n';
    auto copy3 = v;
    auto t0 = Clock::now();
    // sort the vector with std::sort, parallel policy
    std::sort(std::execution::par, copy3.begin(), copy3.end());
    auto t1 = Clock::now();
    Duration d = t1 - t0;
    std::cout << " in " << d.count() << " s\n";
  }
}
