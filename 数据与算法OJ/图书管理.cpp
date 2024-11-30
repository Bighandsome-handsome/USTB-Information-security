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
    // 读取并存储初始书籍ID  
    while (iss >> id) {  
        books.push_back(id);  
    }    
    unsigned int m;  
    cin >> m;  
    string result;  
    // 执行操作并累积结果  
    for (unsigned int i = 0; i < m; ++i) {  
        char operation;  
        cin >> operation >> id;  
        // 使用lower_bound进行二分查找  
        auto it = lower_bound(books.begin(), books.end(), id);  
        bool found = (it != books.end() && *it == id);  
          
        if (operation == '1') 
		{ 
		    // 查询操作  
            result += (found ? "1" : "0");  
        } 
		else if (operation == '2') { 
		// 借出操作  
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
