#include <string>
using namespace std;

class Values {
public:
	Values(string name, string mathExpression) : name(name), mathExpression(mathExpression) {}

	string name;
	string mathExpression;
};