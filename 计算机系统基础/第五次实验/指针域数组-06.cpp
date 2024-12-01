#include <iostream>
using namespace std;

int array2(int i, int j, int **a) {
    return a[i][j];
}


int main()
{
    int i, j;
    int A[4][3] = {
        {173, 158, 166}, 
        {168, 155, 171}, 
        {163, 164, 165}, 
        {163, 164, 172} };
    int **p; //定义一个指向三个成员的数组的指针，这是一个二级的指针
    cin >> i >> j;
     int *temp[4];
     for(int i=0;i<4;i++) 
    temp[i]=A[i];
           p =temp;
    cout << array2(i, j, p) <<endl;
    return 0;
}

