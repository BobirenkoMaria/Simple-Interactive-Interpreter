#include <vector>
#include <string>

using namespace std;

class Calculate {
public:
	double TheSolve(string value1, string value2, char mathAction);

private:
	double value1, value2;

	double solution;
	char mathAction;

	void FigureOut();
};