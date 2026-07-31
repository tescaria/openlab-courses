#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <vector>

std::ostream &operator<<(std::ostream &os, std::vector<int> const &c);
std::vector<int> make_vector(int N);

int main() {
  // create a vector of N elements, generated randomly
  int const N = 10;
  std::vector<int> v = make_vector(N);
  std::cout << v << '\n';

  // sum all the elements of the vector
  // use std::accumulate
  auto sum = std::accumulate(std::begin(v), std::end(v), 0);
  std::cout << sum << '\n';

  // compute the average of the first half and of the second half of the vector
  auto half_size = v.size() / 2;
  auto mid_point = v.begin() + half_size;
  auto sum_first = std::accumulate(v.begin(), mid_point, 0);
  auto avg_first = sum_first / half_size;
  std::cout << "Average first half: " << avg_first << '\n';
  
  auto sum_second = std::accumulate(mid_point, v.end(), 0);
   auto avg_second = sum_second / half_size;
  std::cout << "Average second half: " << avg_second << '\n';

  // remove duplicate elements
  // use std::sort followed by std::unique/unique_copy
  std::sort(v.begin(), v.end());
  std::cout << v << '\n';
  auto new_end = std::unique(v.begin(), v.end());
  v.erase(new_end, v.end());
  std::cout << v << '\n';
  
  // move the three central elements to the beginning of the vector
  // use std::rotate
  auto first_central = v.begin() + (v.size() - 3) / 2;
  std::rotate(v.begin(), first_central, first_central + 3);
  std::cout << v << '\n';
}

std::ostream &operator<<(std::ostream &os, std::vector<int> const &c) {
  os << "{ ";
  std::copy(std::begin(c), std::end(c), std::ostream_iterator<int>{os, " "});
  os << '}';

  return os;
}

std::vector<int> make_vector(int N) {
  std::random_device rd;
  std::default_random_engine eng{rd()};

  int const MAX_N = 100;
  std::uniform_int_distribution<int> dist{1, MAX_N};

  std::vector<int> result;
  result.reserve(N);
  std::generate_n(std::back_inserter(result), N, [&] { return dist(eng); });

  return result;
}
