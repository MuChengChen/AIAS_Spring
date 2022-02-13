#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void lfsr_calculate(uint8_t *reg) {

  *reg = *reg << 4;
  unsigned bit = (*reg >> 4) ^ (*reg >> 5) & 1;
  *reg = (*reg >> 1) | (bit << 7);
  *reg = *reg >> 4;

}

int main() {
  int8_t *numbers = (int8_t*) malloc(sizeof(int8_t) * 15);
  if (numbers == NULL) {
    printf("Memory allocation failed!");
    exit(1);
  }

  memset(numbers, 0, sizeof(int8_t) * 15);
  uint8_t reg = 0x0;
  uint32_t count = 0;
  int i;

  do {
    count++;
    numbers[reg] = 1;
    if (count < 16) {
      printf("My number is: %u\n", reg);
    } else if (count == 15) {
      printf(" ... etc etc ... \n");
    }
      lfsr_calculate(&reg);
  } while (numbers[reg] != 1);

  printf("Got %u numbers before cycling!\n", count);


  free(numbers);
  

  return 0;
}