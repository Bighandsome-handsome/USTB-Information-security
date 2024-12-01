#include<iostream>  
#include<stack>  
#include<vector>  
#include<string>  
using namespace std;
class ExpressionParser 
{
private:
	struct Formula
	{
		string expression;              
		int level;                     
	};
	stack <char> sta;                  
	vector<Formula> answer;            
	string s; 
	int i = 0;
	int ans_level = 0;
	Formula Parse() 
	{
		vector<Formula> childexpression;
		Formula currentposition;
		for (; i < s.size(); i++) 
		{
			if (s[i] == '(') {
				sta.push(s[i]);
				i++;
				childexpression.push_back(Parse());
			}
			else if (s[i] == ')' || s[i] == ',') 
			{
				if (sta.top() != '(') {
					Formula temp;
					temp.level = 0;
					temp.expression = string(1, sta.top());
					childexpression.push_back(temp);
					answer.push_back(temp);
					sta.pop();
				}
				if (s[i] == ')') {
					sta.pop();
					currentposition.expression = sta.top();
					currentposition.expression += "(";
					sta.pop();
					int max_level = 0;
					for (int j = 0; j < childexpression.size(); j++) 
					{
						max_level = max(childexpression[j].level, max_level);
						currentposition.expression += childexpression[j].expression;
						if (j != childexpression.size() - 1) 
							currentposition.expression += ",";
					}
					currentposition.expression += ")";
					childexpression.clear();
					currentposition.level = max_level + 1;
					ans_level = max(ans_level, currentposition.level);
					answer.push_back(currentposition);
					return currentposition;
				}
			}
			else sta.push(s[i]);
		}
		return currentposition;
	}
public:  
	ExpressionParser(string expression) : s(expression) {}
	void GetAnswer()
	{
		if (s.size() == 1) {
			cout << 0 << endl;
			cout<< s << endl;
			return;
		}
		Parse();
		printResults();
	}
	void printResults() 
	{
		cout << ans_level << endl;
		for (int j = 0; j <= ans_level; j++) 
		{
			int flag = 0;
			for (int n = 0; n < answer.size(); n++) 
			{
				if (answer[n].level == j) 
				{
					if (!flag) 
					{
						cout << answer[n].expression;
						flag = 1;
					}
					else 
						cout << ";" << answer[n].expression;
				}
			}
			cout << endl;
		}
	}
};
int main() 
{
	string input;
	cin >> input;
	ExpressionParser parser(input);
	parser.GetAnswer();
	return 0;
}


