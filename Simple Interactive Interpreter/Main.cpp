#include <iostream>
#include <string>
#include <vector>
#include "UserStringRedactor.h"
#include "Parser.h"
#include "Calculate.h"

int main() {
	setlocale(LC_ALL, "RU");

	cout << "Enter mathematic expression: ";

	std::string UserStr = "ce=64=67=23=86=h=shu=5e=e";
//	getline(cin, UserStr);
	int InputClock = clock();

	if (UserStr.find(' ')) {
		Redactor redactedStr(UserStr);
		UserStr = redactedStr.RedactedString();
	}

	Parser parseUserString(UserStr);
	parseUserString.Parse();

/*	vector<string> values = parseUserString.GetValues();


	Calculate calculate;
	double solve = calculate.TheSolve(values[0], values[1], parseUserString.GetMathAction());
	cout << "Solve: " << solve << endl; */

	cout << clock() - InputClock << " мс" << endl;
}