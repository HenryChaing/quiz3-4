#include <stdlib.h>
#include <stdio.h>

int total_hamming_distance(int* nums, int numsSize)
{
    int total = 0;;
    for (int i = 0;i < numsSize;i++)
        for (int j = 0; j < numsSize;j++)
            total += __builtin_popcount(nums[i] ^ nums[j]); 
    return total >> 1;
}

int hamming_distance_linear(int* nums, int numsSize){
    int iteration = 0, distance = 0;
    for (__uint32_t i = 1; iteration < 32; i<<=1)
    {
        int ones = 0;
        for (int j = 0; j < numsSize; j++)
        {
            __uint32_t bin = nums[j];
            if((bin & i) == i){
                ones++;
            }
        }

        distance += ones*(numsSize-ones);

        iteration++;
    }
    
    return distance;
}

int main(){
    int arr[3] = {2,4,14};
    printf("%d\n",hamming_distance_linear(arr,sizeof(arr)/sizeof(arr[0])));
}

