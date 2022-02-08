#include <string>
#include <vector>

using namespace std;

class Parser {
public:
	Parser(string userString) : userString(userString) {}
	
	void Parse();

	vector<string> GetValues();
	char GetMathAction();

private:
	string userString;
	
	string expression;
	char mathAction;

	vector<string> values;

	vector<string> AllParsedString;

	vector<string> DividedExpression; //массив уже поделенных строк 

	int key; // ключ того, чем является элемент по KeyWords
	int position = 0; //позиция последнего равно

	bool error = false;

	enum KeyWords {
		VALUE,
		FUNCTION,
		STANDART_FUNCTION,
		_LASTELEMENT
	};

	enum PriorityOfMathOperations {
		EQUALS,
		MULTIPLE,
		DIVISION,
		PLUS,
		MINUS,
		_LASTELEMENT
	};

	void ParseStringToExpressions(string _exp, int numExpression, char element);
	void DividingStringIntoParts(char element);
	void ParseCharToChar(string* nameOrExpression, string expression, int end);
	vector<int> FindElements(char element, string expression);
	vector<int> FindElements(vector<char> element, string expression);
	int EnumOfMathOperation(char element);
	void CreateNewValue();
	void IfInvalidSintaxis();
};