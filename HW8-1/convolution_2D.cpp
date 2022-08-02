#include <iostream>
#include <stdio.h>
using namespace std;

#define INPUT_SIZE 8
#define KERNEL_SIZE 3
#define OUTPUT_SIZE 6

void convolution_2D(int N[][INPUT_SIZE], int M[][KERNEL_SIZE], int P[][OUTPUT_SIZE]) {
                            //determine the 2D array width
	// find center position of kernel (half of kernel size)
	int kernel_center_X = KERNEL_SIZE / 2;
	int kernel_center_Y = KERNEL_SIZE / 2;
	
	for (int i = 0; i < OUTPUT_SIZE; ++i)              // rows
	{
	    for (int j = 0; j < OUTPUT_SIZE; ++j)          // columns
	    {
	        for (int m = 0; m < KERNEL_SIZE; ++m)     // kernel rows
	        {
	            for (int n = 0; n < KERNEL_SIZE; ++n) // kernel columns
	            {
					// Calculate index of input signal
	                int ii = i + (m - kernel_center_X) +1; //m n = 0 => i + (m - )
	                int jj = j + (n - kernel_center_Y) +1;
	                    
                    P[i][j] += N[ii][jj] * M[m][n];
                    cout<<N[ii][jj]<<" * "<<M[m][n]<<endl;
	            }
	        }
            cout<<"\n"; 
	    }
	}
	
	// Above is for channel == 1
	// In this case, input and kernel are equal
	// So, we can just do "P[i][j]*=2"
	
	// for(int i = 0; i < OUTPUT_SIZE; ++i)
	// {
	// 	for (int j = 0; j < OUTPUT_SIZE; ++j)          
	//   {
	// 		// result
	// 		P[i][j] = P[i][j] * 2;
	// 	}
	// }
}

int main(){
    int n[8][8];
    int m[8][8];
    int ker[3][3];
    int ans[6][6];
    for(int i=0; i<8;++i){
        for(int j=0;j<8;++j){
            n[i][j] = j;
            m[i][j] = j;
        }
    }

    for(int i=0; i<3;++i){
        for(int j=0;j<3;++j){
            ker[i][j] = j;
        }
    }
     for(int i=0; i<6;++i){
        for(int j=0;j<6;++j){
            ans[i][j] = 0;
        }
    }
    // for(int i=0; i<3;++i){
    //     for(int j=0;j<3;++j){
    //         cout<<" "<<ker[i][j];
    //     }
    //     cout<<"\n";
    // }

    convolution_2D(n,ker,ans);

    //print
    for(int i=0; i<8;++i){
        for(int j=0;j<8;++j){
            cout<<" "<<n[i][j];
        }
        cout<<"\n";
    }

    
    cout<<"ans\n";

    for(int i=0; i<6;++i){
        for(int j=0;j<6;++j){
            cout<<" "<<ans[i][j];
        }
        cout<<"\n";
    }

    return 0;

}