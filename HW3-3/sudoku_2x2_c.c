#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
bool check(char *test_c_data,int index){
	int i;
	//check column
	for(i=(index%4);i<=15;i+=4){
		if(i==index){
			continue;
		}
		else if(*(test_c_data+i)==*(test_c_data+index)){
			return false;
		}
	}

	//check row
	for(i=4*(index/4);i<=4*(index/4)+3;i++){
		if(i==index){
			continue;
		}
		else if(*(test_c_data+i)==*(test_c_data+index)){
		        return false;
		}
	}
	//check sub area
	if(index%8==0 || index%8==2){
		if(*(test_c_data+index)==*(test_c_data+index+5)){
			return false;
		}
	}
	if(index%8==1 || index%8==3){
		if(*(test_c_data+index)==*(test_c_data+index+3)){
			return false;
		}
	}
	if(index%8==4 || index%8==6){
		if(*(test_c_data+index)==*(test_c_data+index-3)){
			return false;
		}
	}
	if(index%8==5 || index%8==7){
		if(*(test_c_data+index)==*(test_c_data+index-5)){
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
		//if the block is not 0,skip this block
		return solve(test_c_data,index+1);
	}
	else{
		//check which number can set in the block
		for(i=1;i<=4;i++){
			*(test_c_data+index)=i;
			if(check(test_c_data,index)&& solve(test_c_data,index+1)){
				return true;
			}
		}
	}
	*(test_c_data+index)=0;
	return false;
}


void sudoku_2x2_c(char *test_c_data){

// TODO
// Finish your sudoku algorithm in c language
   solve(test_c_data,0);
   
   

}





