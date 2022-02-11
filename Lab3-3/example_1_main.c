// Lab3-3 - example_1_main.c

#include <stdio.h>
#include <stdlib.h>

int sum_c(int n){
  int temp = 0;
  for (int i = 1; i <= n; i++) {
    temp = temp + i;
  }
  return temp;
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