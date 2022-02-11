// Lab3-3 example_2_main.c

#include <stdio.h>
#include <stdlib.h>

int formula(int n){
  return (1+n)*n/2; 
}

int sum_c(int n){
  return formula(n);
}

int sum_asm(int n);

int main(){
  int n = 5;
  int out = 0;
  out = sum_c(n);
  printf("C code sum_c(%d)=%d\n", n, out);  
  out = sum_asm(n);
  printf("ASM code sum_asm(%d)=%d\n", n, out);
  return 0;
}