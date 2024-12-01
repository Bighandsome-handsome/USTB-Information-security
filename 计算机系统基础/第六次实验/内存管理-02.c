#include <stdio.h>
#include<stdlib.h>
int main() {

    int a[5];
    scanf("%d", &a[0]);
    scanf("%d", &a[1]);
    scanf("%d", &a[2]);
    scanf("%d", &a[3]);
    scanf("%d", &a[4]);

    int*b = (int*)malloc(2*sizeof(int));
   b[0]=0;
	b[1]=1;
    for (int i = 0; i < 5; ++i)
        b[0] += a[i];
    for (int i = 0; i < 5; ++i)
        b[1] *= a[i];

    printf("%d\n", b[0]);
    printf("%d\n", b[1]);


    return 0;
}

