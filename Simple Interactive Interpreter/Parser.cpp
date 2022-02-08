#include "Parser.h"
#include "Calculate.h"
#include "Data.h" 
#include <vector>
#include <iostream>

// ���������� �������� � ��������� ����������/�������
void Parser::ParseStringToExpressions(string _exp, int numExpression, char element)
{
	for (int i = 0; i < _exp.length(); i++) {
		if (_exp[i] == element) {
			if (numExpression == 0) { // ���� ��� ����������
				ParseCharToChar(&expression, _exp, i);
				key = VALUE;
			}
			else {
				expression = expression;
			}

			position = i + 1;

			if (_exp[i] != position && _exp[i] == element) { // ����� ����� ������ �� ������ ����������/������� ��� ���.���������
				ParseCharToChar(&expression, _exp, _exp.size() - (i - 1));
			}
		}
	}
	mathAction = element;

	position = 0;
}

void Parser::Parse()
{
	if (error == false) {
		for (int i = 0; i < DividedExpression.size(); i++) {
			DividingStringIntoParts('=');
			ParseStringToExpressions(DividedExpression[i], i, '=');
			values.push_back(expression);
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
vector<int> Parser::FindElements(vector<char> element, string expression)
{
	vector<int> IndexAndKey;
	vector<vector<int>> elementsIndex;

	for (int i = 0; i < expression.length(); i++) {
		for (int j = 0; j < element.size(); j++) {
			if (expression[i] == element[j]) {
				IndexAndKey.push_back(i);
				IndexAndKey.push_back(EnumOfMathOperation(expression[i]));

				elementsIndex.push_back(IndexAndKey);
				IndexAndKey.clear();
			}
		}
	}
}

// ��������� �������������� ��������
int Parser::EnumOfMathOperation(char element)
{
	int priority;
	switch (element)
	{
	case '=':
		priority = EQUALS;
		break;
	case '*':
		priority = MULTIPLE;
		break;
	case '/':
		priority = DIVISION;
		break;
	case '+':
		priority = PLUS;
		break;
	case '-':
		priority = MINUS;
		break;
	default:
		break;
	}

	return priority;
}

// �������� �������� ���������� � ������� �� ��������� ���� ������
void Parser::CreateNewValue()
{
	switch (key)
	{
	case VALUE: Data_Values.push_back(values); break;
	default: break;
	}
}

void Parser::IfInvalidSintaxis()
{
	cerr << endl << "You have invalid sintax" << endl;
}

// ��������� ���������������� ���� �� ����� (x=y=z  =>  x=y � y=z)
void Parser::DividingStringIntoParts(char element)
{
	vector<int> indexes;
	indexes = FindElements(element, userString);

	for (int i = 0; i < indexes.size(); i++) {
		if (i == 0) DividedExpression.push_back(userString.substr(0,
			(i == indexes.size() - 1) ? (userString.length() - 1) : indexes[1]));

		else DividedExpression.push_back(userString.substr(indexes[i - 1] + 1,
			(i == indexes.size() - 1) ? (userString.length() - 1) : (indexes[i+1] - indexes[i - 1] - 1)));
	}
}
