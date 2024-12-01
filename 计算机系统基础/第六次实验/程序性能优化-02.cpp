#include <iostream>
#include <string.h>
using namespace std;
#define DIM 200
void lower(char *s) {
  size_t i;
  for (i = 0; i < strlen(s); i++)
    if (s[i] >= 'A' && s[i] <= 'Z')
      s[i] += 'a' - 'A';
}

void lower_optimized(char *s) {
  size_t i;
  size_t length = strlen(s);
    for  (i  =  0;  i  <  length;  i++)
          if  (s[i]  >=  'A'  &&  s[i]  <=  'Z')
              s[i]  +=  'a'  -  'A';
}

int main(){
    char* s1 = new char[DIM];
    char* s2 = new char[DIM];

    for (int i = 0; i < DIM; ++i)
    {
        char ch;
        cin >> ch;
        s1[i] = ch;
        s2[i] = ch;
    }

    lower(s1);
    lower_optimized(s2);
    for (int i = 0; i < DIM; i++)
        if (s1[i] != s2[i]){
            cout << "s1 != s2 after functions" << endl;
            return 0;
        }

    cout << "s1 == s2 after functions" << endl;
}


