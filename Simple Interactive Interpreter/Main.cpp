#include <iostream>
#include <string>
#include "UserStringRedactor.h"
#include "Parser.h"


int main() {
	setlocale(LC_ALL, "RU");

	cout << "Введите математическое выражение: ";

	std::string UserStr;
	getline(cin, UserStr);

	Redactor redactedStr(UserStr);
	UserStr = redactedStr.RedactedString();

	Parser parseUserString(UserStr);
	parseUserString.Parse();

	vector<string> names = parseUserString.GetName();
	vector<string> mathExpressions = parseUserString.GetMathExpression();

	for (int i = 0; i < names.size(); i++) {
		cout << "Название переменной: " << names[i] << endl;
		cout << "Помещенное выражение в переменную: " << mathExpressions[i] << endl;
	}
	cout << clock() << " миллисекунд" << endl;

}