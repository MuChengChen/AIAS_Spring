// HW2 main function
#include <stdio.h>
#include <stdlib.h>


int fibonacci_c(int n) { 
    if(n == 0) {
        return 0;
    }
        
    else if(n == 1) {
        return 1;
    }
        
    else {
        return fibonacci_c(n-1)+fibonacci_c(n-2);        
    }
}

int fibonacci_asm(int n);

int main() {
    int n = 6;    // setup input value n
    int out = 0; // setup output value fibonacci(n)
    out = fibonacci_c(n);
    printf("C code fibonacci_c(%d)=%d\n", n, out);  
    out = fibonacci_asm(n);
    printf("ASM code fibonacci_asm(%d)=%d\n", n, out);
    return 0;
}