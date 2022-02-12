//main.c
#include <stdio.h>
#include <stdlib.h>
#define SIZE 16

char test_c_data[16] = { 0, 0, 2, 0, 
                         0, 0, 0, 4,
                         2, 3, 0, 0, 
                         0, 4, 0, 0 };
                      
char test_asm_data[16] = { 0, 0, 2, 0, 
                           0, 0, 0, 4,
                           2, 3, 0, 0, 
                           0, 4, 0, 0 };

void print_sudoku_result() {
    int i;
    printf("\nutput c & assembly function result\n");
    printf("c result :\n");
    for( i=0 ; i<SIZE ; i++) {   
        printf("%d ", *(test_c_data+i));
    }

    printf("\nassembly result :\n");
    for( i=0 ; i<SIZE ; i++) {
        printf("%d ", *(test_asm_data+i));
    }

    int flag = 0;
    for( i=0 ; i<SIZE ; i++) {
        if (*(test_c_data+i) != *(test_asm_data+i)) {
            flag = 1;
            break;
        }
    }

    if (flag == 1){
        printf("\nyour c & assembly got different result!\n");
    }
}


void sudoku_2x2_c(char *test_c_data){

// TODO
// Finish your sudoku algorithm in c language

}

void sudoku_2x2_asm(char *test_asm_data); // TODO, sudoku_2x2_asm.S

                        
int main() {
    sudoku_2x2_c(test_c_data);
    sudoku_2x2_asm(test_asm_data);
    print_sudoku_result();
    return 0;
}