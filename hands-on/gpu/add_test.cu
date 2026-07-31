#include <iostream>

// add two vectors 
__global__ void add(const int *a, const int *b, int *c){
    c[blockIdx.x] = a[blockIdx.x] + b[blockIdx.x];
}

int main(){

}