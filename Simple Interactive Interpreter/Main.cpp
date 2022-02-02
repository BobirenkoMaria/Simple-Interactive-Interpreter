#include <iostream>
#include <string>
#include "UserStringRedactor.h"
#include "Parser.h"


int main() {
	setlocale(LC_ALL, "RU");

	cout << "������� �������������� ���������: xxx =qqqqq+1234 =ooooooo = w=pp";

	std::string UserStr = "xxx =qqqqq+1234 =ooooooo = w=pp";
//	getline(cin, UserStr);
	int InputClock = clock();

	Redactor redactedStr(UserStr);
	UserStr = redactedStr.RedactedString();

	Parser parseUserString(UserStr);
	parseUserString.Parse();

	vector<string> names = parseUserString.GetName();
	vector<string> mathExpressions = parseUserString.GetMathExpression();

	for (int i = 0; i < names.size(); i++) {
		cout << "�������� ����������: " << names[i] << endl;
		cout << "���������� ��������� � ����������: " << mathExpressions[i] << endl << endl;
	}
	cout << clock() - InputClock << " ��" << endl;

}