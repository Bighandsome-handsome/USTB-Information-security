#include <iostream>
#include <stdio.h>
#include <stdlib.h>
int* i_arr;
int n;
void init_i()
{
    i_arr = (int*) malloc(n*sizeof(int));
    for (int i = 0; i < n; ++i)
        scanf("%d", &i_arr[i]);
}
void find_larger()
{
    int m;
    scanf("%d", &m);
      for(int i=0;i<n;i++)
        if(i_arr[i]>m)   
    	printf("%d ", i_arr[i]);
    printf("\n");
}
void find_smaller()
{
    int m;
    scanf("%d", &m);
        for(int i=0;i<n;i++)
        if(i_arr[i]<m)   
    	printf("%d ", i_arr[i]);
    	free(i_arr);
}
int main() {
    scanf("%d", &n);
    init_i();
    find_larger();
    find_smaller();

    return 0;
}

