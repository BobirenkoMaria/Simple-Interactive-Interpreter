#include <vector>
#include <sstream>
#include "Calculate.h"
using namespace std;


double Calculate::TheSolve(string _value1, string _value2, char _mathAction)
{
	value1 = stod(_value1);
	value2 = stod(_value2);
	mathAction = _mathAction;

	FigureOut();

	return solution;
}

void Calculate::FigureOut()
{
	switch (mathAction)
	{
	case '+':
		solution = value1 + value2;
		break;
	case '-':
		solution = value1 - value2;
		break;
	case '*':
		solution = value1 * value2;
		break;
	case '/':
		solution = value1 / value2;
		break;
	default:
		break;
	}
}