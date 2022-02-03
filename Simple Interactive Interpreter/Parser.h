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
	
	string value_1;
	string value_2;
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
		PLUS,
		MINUS,
		MULTIPLE,
		DIVISION,
		EQUALS
	};

	void ParseStringToExpressions(string expression, int numExpression, char element);
	void DividingStringIntoParts(); 
	void ParseCharToChar(string* nameOrExpression, string expression, int end);
	vector<int> FindElements(char element, string expression);
//	void CreateNewValue();
	void IfInvalidSintaxis();
};