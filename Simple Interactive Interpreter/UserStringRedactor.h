using namespace std;

class Redactor
{
public:
	Redactor(string userString) : userString(userString) {}

	string RedactedString(); // ���������� ������ � ������� ����

private:
	string userString;

	void DeleteSpaces();// �������� ���� ��������
	void StringToLower();// ���������� � ������� ��������
};