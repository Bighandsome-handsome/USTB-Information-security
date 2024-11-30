#include <iostream>  
#include <vector>  
#include <algorithm>  
#include <sstream>  
#include <string>  
using namespace std;  
int main() 
{  
    string line;  
    getline(cin, line);  
    istringstream iss(line);  
    vector<int> books;  
    int id;  
    // ��ȡ���洢��ʼ�鼮ID  
    while (iss >> id) {  
        books.push_back(id);  
    }    
    unsigned int m;  
    cin >> m;  
    string result;  
    // ִ�в������ۻ����  
    for (unsigned int i = 0; i < m; ++i) {  
        char operation;  
        cin >> operation >> id;  
        // ʹ��lower_bound���ж��ֲ���  
        auto it = lower_bound(books.begin(), books.end(), id);  
        bool found = (it != books.end() && *it == id);  
          
        if (operation == '1') 
		{ 
		    // ��ѯ����  
            result += (found ? "1" : "0");  
        } 
		else if (operation == '2') { 
		// �������  
            if (found) 
			{  
                books.erase(it);  
                result += "1";   
                //sort(books.begin(), books.end());  
            } else {  
                result += "0";  
            }  
        } 
		else if (operation == '3') { 
            if (!found) {  
                books.insert(it, id);  
                result += "1";  
            } else {          
                result += "0";  
            }  
        }  
    }  
    cout << result << endl;  
    return 0;  
}
