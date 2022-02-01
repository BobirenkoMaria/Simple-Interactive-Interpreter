#include "Parser.h"
#include "Data.h"
#include <vector>

// отыскивает название и выражение переменной/функции
void Parser::ParseStringToExpressions(string expression, int numExpression)
{
	for (int i = 0; i < expression.length(); i++) { //парсит одно равно (то есть если х=y=z, то браться будет только x=y или y=z)
		if (expression[i] == '=') { // если выражение эквивалентно другой переменной/функции или другому выражению
			if (expression[i-1] == ')') { // если выражение является функцией, то берем его название
				ParseCharToChar(&name, expression, expression.size() - expression.find('='));
				// проверка собственная ли это функция или стандартная?
				if (name == "sin" || name == "cos" || name == "asin" || name == "acos" || name == "log" || name == "tan" || name == "cot") { // стандартная функция
					key = STANDART_FUNCTION;
				}
				else key = FUNCTION; // собственная, если таковой не существует, то будет предупреждение
			}
			else if (numExpression == 0) { // если это переменная
				ParseCharToChar(&name, expression, expression.find('='));
				key = VALUE;
			}
			else {
				name = mathExpression;
			}

			position = i+1;

			if (expression[i] != position && expression[i] == '=') { // будем брать ссылку на другую переменную/функцию или мат.выражение
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

// помещаем названия переменных и функций во временную базу данных
void Parser::CreateNewValue()
{
	switch (key)
	{
	case VALUE: value.push_back(Values(name, mathExpression)); break;
	default: break;
	}
}

// разбивает пользовательский ввод на части (x=y=z  =>  x=y и y=z)
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
