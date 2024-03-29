#include <stdio.h>
#include <stdlib.h>

/*Prints the contents of the array*/
int printArray(int* size, int*array){
    int i=0;
    int s = size;
    for(i=0; i<s; ++i)
        printf("Index: %d Value: %d\n",i,array[i]);
    return 1;

}

/*Create an an array of size size */
int *populateAnArray(int size){
    
	int i,j,k;
    int* array = malloc(size*sizeof(int));
    for(i=0; i<size; ++i){
		array[i] = i;
		for(j=0; j<size;++j){
			array[j] = array[i];
			array[i]=array[i]*j;
			for(k=0;k<size;++k){
				array[k] = k*3-j+7;
			}
		}
	}
    return array;
}

int main(void){

	int size = 10;
    int* array = populateAnArray(size);
    printArray(&size,array);
  
    
	return 1;
	
}
