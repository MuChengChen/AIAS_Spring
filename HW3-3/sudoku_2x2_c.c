#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
bool check(char *test_c_data,int index){
	int i;
	for(i=(index%4);i<=15;i+=4){//column
		if(i==index){
			continue;
		}
		else if(*(test_c_data+i)==*(test_c_data+index)){
			return false;
		}
	}


	for(i=4*(index/4);i<=4*(index/4)+3;i++){//row
		if(i==index){
			continue;
		}
		else if(*(test_c_data+i)==*(test_c_data+index)){
		        return false;
		}
	}
	return true;
}
bool solve(char *test_c_data,int index){
	int i;
	if(index>=16){
		return true;
	}
	if(*(test_c_data+index)>0){
		return solve(test_c_data,index+1);
	}
	else{
		for(i=1;i<=4;i++){
			*(test_c_data+index)=i+0;
			if(check(test_c_data,index)&& solve(test_c_data,index+1)){
				return true;
			}
		}
	}
	*test_c_data=0;
	return false;
}


void sudoku_2x2_c(char *test_c_data){

// TODO
// Finish your sudoku algorithm in c language
   do{
	   solve(test_c_data,0);
   }while(!solve(test_c_data,0));

}






