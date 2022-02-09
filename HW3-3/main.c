//main.c
#include <stdio.h>
#include <stdlib.h>
#define SIZE 4

void print_sudoku(char *data) {
    int i,j;
    for( i=0 ; i<SIZE ; i++) {
        for( j=0 ; j<SIZE ; j++) {
            printf("%d ", *(data+j+4*i));
        }
    }
}


int sudoku_2x2_c(char *data){

// TODO
// Finish your sudoku algorithm in c language

}

int sudoku_2x2_asm(char *data); // TODO, sudoku_2x2_asm.S

 
char *test_c_data = { 0, 0, 2, 0, 
                      0, 0, 0, 4,
                      2, 3, 0, 0, 
                      0, 4, 0, 0 };
                      
char *test_asm_data = { 0, 0, 2, 0, 
                        0, 0, 0, 4,
                        2, 3, 0, 0, 
                        0, 4, 0, 0 };
                        
int main() {
    if (sudoku_2x2_c(test_c_data)) {
        print_sudoku(test_c_data);
    }
    
    if (sudoku_2x2_asm(test_asm_data)) {
        print_sudoku(test_asm_data);
    }
    return 0;
} 