// HW2 main function

int fibonacci_c(int n) { 
    if(n == 0) {
        return 0;
    }
        
    else if(n == 1) {
        return 1;
    }
        
    else {
        return fibonacci(n-1)+fibonacci(n-2);        
    }
}

int fibonnaci_asm(int n);

int main() {
    int n = 6    // setup input value n
    int out = 0; // setup output value fibonacci(n)
    out = fibonacci_c(n);
    printf("C code fibonnaci_c(%d)=%d\n", n, out);  
    out = fibonnaci_asm(n);
    printf("ASM code fibonnaci_asm(%d)=%d\n", n, out);
    return 0;
}