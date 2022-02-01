using namespace std;

class Redactor
{
public:
	Redactor(string userString) : userString(userString) {}

	string RedactedString(); // приведение строки к нужному виду

private:
	string userString;

	void DeleteSpaces();// удаление всех пробелов
	void StringToLower();// приведение к нижнему регистру
};