#include <string>
#include <vector>
using namespace std;

class Parser {
public:
	Parser(string userString) : userString(userString) {}
	
	void Parse();

	vector<string> GetName();
	vector<string> GetMathExpression();

private:
	string userString;
	
	string name;
	string mathExpression;

	vector<string> names;
	vector<string> mathExpressions;

	vector<string> DividedExpression; //������ ��� ���������� ����� 

	int key; // ���� ����, ��� �������� ������� �� KeyWords
	int position = 0; //������� ���������� �����

	enum KeyWords {
		VALUE,
		FUNCTION,
		STANDART_FUNCTION,
		PLUS,
		MINUS,
		MULTIPLE,
		DIVISION,
		EQUALS
	};

	void ParseStringToExpressions(string expression, int numExpression);
	void DividingStringIntoParts(); 
	void ParseCharToChar(string* nameOrExpression, string expression, int end);
	vector<int> FindElements(char element, string expression);
	void CreateNewValue();
};