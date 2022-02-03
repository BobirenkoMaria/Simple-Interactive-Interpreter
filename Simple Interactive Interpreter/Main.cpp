#include <iostream>
#include <string>
#include <vector>
#include "UserStringRedactor.h"
#include "Parser.h"
#include "Calculate.h"

int main() {
	setlocale(LC_ALL, "RU");

	cout << "Enter mathematic expression: ";

	std::string UserStr;
	getline(cin, UserStr);
	int InputClock = clock();

	Redactor redactedStr(UserStr);
	UserStr = redactedStr.RedactedString();

	Parser parseUserString(UserStr);
	parseUserString.Parse();

	vector<string> values = parseUserString.GetValues();


	Calculate calculate;
	double solve = calculate.TheSolve(values[0], values[1], parseUserString.GetMathAction());
	cout << "Solve: " << solve << endl;

	cout << clock() - InputClock << " мс" << endl;
}