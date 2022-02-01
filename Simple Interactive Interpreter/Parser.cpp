#include "Parser.h"
#include "Data.h"
#include <vector>

// ���������� �������� � ��������� ����������/�������
void Parser::ParseStringToExpressions(string expression, int numExpression)
{
	for (int i = 0; i < expression.length(); i++) { //������ ���� ����� (�� ���� ���� �=y=z, �� ������� ����� ������ x=y ��� y=z)
		if (expression[i] == '=') { // ���� ��������� ������������ ������ ����������/������� ��� ������� ���������
			if (expression[i-1] == ')') { // ���� ��������� �������� ��������, �� ����� ��� ��������
				ParseCharToChar(&name, expression, expression.size() - expression.find('='));
				// �������� ����������� �� ��� ������� ��� �����������?
				if (name == "sin" || name == "cos" || name == "asin" || name == "acos" || name == "log" || name == "tan" || name == "cot") { // ����������� �������
					key = STANDART_FUNCTION;
				}
				else key = FUNCTION; // �����������, ���� ������� �� ����������, �� ����� ��������������
			}
			else if (numExpression == 0) { // ���� ��� ����������
				ParseCharToChar(&name, expression, expression.find('='));
				key = VALUE;
			}
			else {
				name = mathExpression;
			}

			position = i+1;

			if (expression[i] != position && expression[i] == '=') { // ����� ����� ������ �� ������ ����������/������� ��� ���.���������
				ParseCharToChar(&mathExpression, expression, expression.size() - (expression.find('=') - 1));
			}
			
		}
	}

	CreateNewValue();
}

void Parser::Parse()
{
	DividingStringIntoParts();
	for (int i = 0; i < DividedExpression.size(); i++) { 
		if(i > 0)
		ParseStringToExpressions(DividedExpression[i], i); 
		names.push_back(name);
		mathExpressions.push_back(mathExpression);

		position = 0;
		
	}
}

vector<string> Parser::GetName()
{
	return names;
}

vector<string> Parser::GetMathExpression()
{
	return mathExpressions;
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
void Parser::CreateNewValue()
{
	switch (key)
	{
	case VALUE: value.push_back(Values(name, mathExpression)); break;
	default: break;
	}
}

// ��������� ���������������� ���� �� ����� (x=y=z  =>  x=y � y=z)
void Parser::DividingStringIntoParts()
{
	vector<int> indexes;
	indexes = FindElements('=', userString);

	for (int i = 0; i < indexes.size(); i++) {
		if (i == 0) {
			DividedExpression.push_back(userString.substr(0, indexes[1]));
		}
		else DividedExpression.push_back(userString.substr(indexes[i - 1] + 1, 
			(i == indexes.size()-1) ? (userString.length()-1) : indexes[i + 1]));
	}
}
