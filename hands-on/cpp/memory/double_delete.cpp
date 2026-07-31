#include <memory>
#include <iostream>

std::unique_ptr<int> factory();

int main() {
  auto t = factory();
}

std::unique_ptr<int> factory() { return std::make_unique<int>(); }
