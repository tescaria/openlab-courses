#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>
#include <cmath>

std::ostream &operator<<(std::ostream &os, std::vector<int> const &c);
std::vector<int> make_vector(int N);

int main() {
  // create a vector of N elements, generated randomly
  int const N = 10;
  std::vector<int> v = make_vector(N);
  std::cout << v << '\n';

  // multiply all the elements of the vector
  // use std::accumulate
  auto product = std::accumulate(v.begin(), v.end(), 1, [](int n, int m){return n * m;} );
  std::cout << product << '\n';
  // compute the mean and the standard deviation
  // use std::accumulate and a struct with two numbers to accumulate both the
  // sum and the sum of squares
  struct temp_struct{
    long sum = 0;
    long sum_squares = 0;
  };
   
  temp_struct results = std::accumulate(v.begin(), v.end(), temp_struct{}, [](temp_struct n, int m){return temp_struct{n.sum + m, n.sum_squares + m*m};});
  auto mean = results.sum / v.size();
  auto dev = std::sqrt(results.sum_squares / v.size() - mean*mean);
  std::cout << "Mean: " << mean << '\n';
  std::cout << "Standard Deviation: " << dev << '\n';

  // sort the vector in descending order
  // use std::sort
  auto copy = v;
  std::sort(copy.begin(), copy.end(), [](int n, int m){return n > m;});
  std::cout << "Sorted in descending order: " << copy << '\n';

  // move the even numbers at the beginning of the vector
  // use std::partition
  auto copy2 = v;
  std::partition(copy2.begin(), copy2.end(), [](int n){return (n % 2) == 0;});
  std::cout << "Even numbers at beginning: " << copy2 << '\n';

  // create another vector with the squares of the numbers in the first vector
  // use std::transform
  auto copy3 = v;
  std::transform(copy3.begin(), copy3.end(), copy3.begin(), [](int n){return n*n;});
  std::cout << "Vector with numbers squared: " << copy3 << '\n';

  // find the first multiple of 3 or 7
  // use std::find_if - returns an iterator not a value
  auto mult_3or7 = std::find_if(v.begin(), v.end(), [](int n){return (n % 3 == 0) || (n % 7 == 0);});
  std::cout << "First multiple of 3 or 7: " << *mult_3or7 << '\n';

  // erase from the vector all the multiples of 3 or 7
  // use std::remove_if followed by vector::erase
  //   or the newer std::erase_if utility (C++20)
  auto new_end = std::remove_if(v.begin(), v.end(),  [](int n){return (n % 3 == 0) || (n % 7 == 0);});
  v.erase(new_end, v.end());
  std::cout << v << '\n';
}

std::ostream &operator<<(std::ostream &os, std::vector<int> const &c) {
  os << "{ ";
  std::copy(std::begin(c), std::end(c), std::ostream_iterator<int>{os, " "});
  os << '}';

  return os;
}

std::vector<int> make_vector(int N) {
  // define a pseudo-random number generator engine and seed it using an actual
  // random device
  std::random_device rd;
  std::default_random_engine eng{rd()};

  int const MAX_N = 100;
  std::uniform_int_distribution<int> dist{1, MAX_N};

  std::vector<int> result;
  result.reserve(N);
  std::generate_n(std::back_inserter(result), N, [&] { return dist(eng); });

  return result;
}
