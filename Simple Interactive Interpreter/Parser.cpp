#include "Parser.h"
#include "Calculate.h"
#include "Data.h" 
#include <vector>
#include <iostream>

// отыскивает название и выражение переменной/функции
void Parser::ParseStringToExpressions(string _exp, int numExpression, char element)
{
	for (int i = 0; i < _exp.length(); i++) {
		if (_exp[i] == element) {
			if (numExpression == 0) { // если это переменная
				ParseCharToChar(&expression, _exp, i);
				key = VALUE;
			}
			else {
				expression = expression;
			}

			position = i + 1;

			if (_exp[i] != position && _exp[i] == element) { // будем брать ссылку на другую переменную/функцию или мат.выражение
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


// спарсить название функции или переменной
void Parser::ParseCharToChar(string* nameOrExpression, string expression, int count) 
{ *nameOrExpression = expression.substr(position, count); }

// находит все определенные элементы типа char и возвращает как массив их индексов
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

// приоритет математических операций
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

// помещаем названия переменных и функций во временную базу данных
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

// разбивает пользовательский ввод на части (x=y=z  =>  x=y и y=z)
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
