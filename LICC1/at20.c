#include<stdio.h>

#define MAX 500000
void bubblesort(int[], int);

int main (void) {
    int n;
    scanf("%d",&n);

    int nums[n+1];
    for(int i = 0; i < n; ++i) {
        scanf("%d",&nums[i]);
    }
    bubblesort(nums,n);
    for(int i = 0; i < n; ++i) {
        printf("%d ",nums[i]);
    }
    printf("\n");
}

void bubblesort(int nums[MAX], int n) {
    int ord;
    do {
        ord = 1;
        for (int i = 0; i < n-1; ++i) {
            if(nums[i] > nums[i+1]) {
                int swap = nums[i];
                nums[i] = nums[i+1];
                nums[i+1] = swap;
                ord = 0;
            }
        }
    } while(ord==0);
}