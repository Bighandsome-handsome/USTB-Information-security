#include <iostream>

using namespace std;
#define DIM 200
int a1[DIM][DIM];
int b1[DIM][DIM];
int c1[DIM][DIM];
int a2[DIM][DIM];
int b2[DIM][DIM];
int c2[DIM][DIM];

void productIJK(int a[DIM][DIM], int b[DIM][DIM], int c[DIM][DIM])
{
    int i=0,j=0,k=0;
    for (i=0; i<DIM; i++) {
        for (j=0; j<DIM; j++) {
            for (k=0; k<DIM; k++) 
                c[i][j] += a[i][k] * b[k][j];
        }
    }
}

void productOptimizedIJK(int a[DIM][DIM], int b[DIM][DIM], int c[DIM][DIM])
{
    int i=0,j=0,k=0;
    for (i=0; i<DIM; i++) {
        for (j=0; j<DIM; j++) {
        	 int sum = 0;
	         for (k=0; k<DIM; k++) 
	        {  sum += a[i][k] * b[k][j]; }  
	         c[i][j] = sum;
        }
    }
}

void productKIJ(int a[DIM][DIM], int b[DIM][DIM], int c[DIM][DIM])
{
    int i=0,j=0,k=0;
    for (k=0; k<DIM; k++) {
        for (i=0; i<DIM; i++) {
            for (j=0; j<DIM; j++)
                c[i][j] += a[i][k] * b[k][j];   
        }
    }
}

void productOptimizedKIJ(int a[DIM][DIM], int b[DIM][DIM], int c[DIM][DIM])
{
    int i=0,j=0,k=0;
    for (k=0; k<DIM; k++) {
        for (i=0; i<DIM; i++) {
        	for (j = 0; j < DIM; j++) 
	         c[i][j] += a[i][k] * b[k][j]; 
        }
    }
}

void productJKI(int a[DIM][DIM], int b[DIM][DIM], int c[DIM][DIM])
{
    int i=0,j=0,k=0;
    for (j=0; j<DIM; j++) {
        for (k=0; k<DIM; k++) {
            for (i=0; i<DIM; i++)
                c[i][j] += a[i][k] * b[k][j];
        }
    }
}

void productOptimizedJKI(int a[DIM][DIM], int b[DIM][DIM], int c[DIM][DIM])
{
    int i=0,j=0,k=0;
    for (j=0; j<DIM; j++) {
        for (k=0; k<DIM; k++) {
        	int temp[DIM] = {0}; 
	                    for (int i = 0; i < DIM; ++i) {  
	                        temp[i] += a[i][k] * b[k][j]; 
	                    }  
	                    for (i = 0; i < DIM; ++i) 
	                        c[i][j] += temp[i];
        }
    }
}

int main() {
    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++)
        {
            a1[i][j] = i+j;
            b1[i][j] = i-j;
            c1[i][j] = 0;
            a2[i][j] = i+j;
            b2[i][j] = i-j;
            c2[i][j] = 0;
        }

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i){
    	int x, y, val;
    	cin >> x >> y >> val;
    	a1[x][y] = val;
    	a2[x][y] = val;
    }

    productIJK(a1, b1, c1);
    productOptimizedIJK(a2, b2, c2);
    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++)
        	if (c1[i][j] != c2[i][j]){
        		cout << "c1 != c2 after productOptimizedIJK()" << endl;
        		return 0;
        	}

    productKIJ(a1, b1, c1);
    productOptimizedKIJ(a2, b2, c2);
    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++)
        	if (c1[i][j] != c2[i][j]){
        		cout << "c1 != c2 after productOptimizedKIJ()" << endl;
        		return 0;
        	}

    productJKI(a1, b1, c1);
    productOptimizedJKI(a2, b2, c2);
    for (int i = 0; i < DIM; i++)
        for (int j = 0; j < DIM; j++)
        	if (c1[i][j] != c2[i][j]){
        		cout << "c1 != c2 after productOptimizedJKI()" << endl;
        		return 0;
        	}

    cout << "c1 == c2 after all functions" << endl;
    return 0;
}



