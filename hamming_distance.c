#include <stdlib.h>
#include <stdio.h>

int totalHammingDistance(int* nums, int numsSize)
{
    int total = 0;;
    for (int i = 0;i < numsSize;i++)
        for (int j = 0; j < numsSize;j++)
            total += __builtin_popcount(nums[i] ^ nums[j]); 
    return total >> 1;
}

int main(){
    int arr[3] = {4,4,14};
    printf("%d\n",totalHammingDistance(arr,sizeof(arr)/sizeof(arr[0])));
}

