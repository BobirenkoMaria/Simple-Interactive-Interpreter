#include "Parser.h"
#include "Data.h"
#include "Calculate.h"
#include <vector>
#include <iostream>

// ���������� �������� � ��������� ����������/�������
void Parser::ParseStringToExpressions(string expression, int numExpression, char element)
{
	for (int i = 0; i < expression.length(); i++) {
		if (expression[i] == element) {
			if (numExpression == 0) { // ���� ��� ����������
				ParseCharToChar(&value_1, expression, i);
				key = VALUE;
			}
			else {
				value_1 = value_2;
			}

			position = i + 1;

			if (expression[i] != position && expression[i] == element) { // ����� ����� ������ �� ������ ����������/������� ��� ���.���������
				ParseCharToChar(&value_2, expression, expression.size() - (i - 1));
			}
		}
	}
	mathAction = element;

	position = 0;
//	CreateNewValue();
}

void Parser::Parse()
{
	DividingStringIntoParts();
	if (error == false) {
		for (int i = 0; i < DividedExpression.size(); i++) {
			ParseStringToExpressions(DividedExpression[i], i, '=');
			ParseStringToExpressions(value_2, i, '+');

			values.push_back(value_1);
			values.push_back(value_2);
		}
	}
}

vector<string> Parser::GetValues()
{
	return values;
}

char Parser::GetMathAction()
{
	return mathAction;
}


// �������� �������� ������� ��� ����������
void Parser::ParseCharToChar(string* nameOrExpression, string expression, int count) 
{ *nameOrExpression = expression.substr(position, count); }

// ������� ��� ������������ �������� ���� char � ���������� ��� ������ �� ��������
vector<int> Parser::FindElements(char element, string expression) {
	vector<int> elementsIndex;
	
	for (int i = 0; i < expression.length(); i++) {
		if (expression[i] == element) elementsIndex.push_back(i);
	}

	return elementsIndex;
}

// �������� �������� ���������� � ������� �� ��������� ���� ������
/*void Parser::CreateNewValue()
{
	switch (key)
	{
	case VALUE: _Expressions.push_back(name, mathExpression); break;
	default: break;
	}
}*/

void Parser::IfInvalidSintaxis()
{
	cerr << endl << "You have invalid sintax" << endl;
}

// ��������� ���������������� ���� �� ����� (x=y=z  =>  x=y � y=z)
void Parser::DividingStringIntoParts()
{
	vector<int> indexes;
	indexes = FindElements('=', userString);

	if (indexes.size() == 2) {
		for (int i = 0; i < indexes.size(); i++) {
			if (i == 0) {
				DividedExpression.push_back(userString.substr(0,
					(i == indexes.size() - 1) ? (userString.length() - 1) : indexes[1]));
			}
			else DividedExpression.push_back(userString.substr(indexes[i - 1] + 1,
				(i == indexes.size() - 1) ? (userString.length() - 1) : indexes[i + 1]));
		}
	}
	else if (indexes.size() == 1) {
		DividedExpression.push_back(userString);
	}
	else {
		IfInvalidSintaxis();
	}
}
