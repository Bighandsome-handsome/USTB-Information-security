#include <iostream>
#include<stdio.h>
#include<stdlib.h>
int main(){
	int n;
	char* lower_str;
	char* upper_str;  
           scanf("%d", &n);  
           getchar(); 
           upper_str = (char*)malloc((n + 1) * sizeof(char));  
            lower_str = (char*)malloc((n + 1) * sizeof(char));  
       fgets(lower_str, n + 1, stdin);  
           lower_str[n] = '\0';  
           for (int i = 0; i < n; ++i) {  
               if (lower_str[i] >= 'a' && lower_str[i] <= 'z') {  
                   lower_str[i] = lower_str[i] - 'a' + 'A';  
               }  
           }  
           printf("%s\n", lower_str);  
         
           fgets(upper_str, n + 1, stdin);  
           upper_str[n] = '\0';   

           for (int i = 0; i < n; ++i) {  
               if (upper_str[i] >= 'A' && upper_str[i] <= 'Z') {  
                   upper_str[i] = upper_str[i] - 'A' + 'a';  
               }  
           }  
           printf("%s\n", upper_str);  
           free(lower_str);  
           free(upper_str);  
         
	
       return 0;
}

