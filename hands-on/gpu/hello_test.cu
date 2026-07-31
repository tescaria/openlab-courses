#include <iostream>

__global__ void mykernel() {}

int main(){
    cudaStream_t stream; cudaStreamCreate(&stream);
    mykernel<<<1, 1, 0, stream>>>();
    std::cout << "Hello World! \n";
    cudaStreamSynchronize(stream);
    cudaStreamDestroy(stream);
}