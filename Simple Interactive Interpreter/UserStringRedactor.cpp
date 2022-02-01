#include <string>
#include <algorithm>
#include <cctype>
#include "UserStringRedactor.h"

using namespace std;

string Redactor::RedactedString() {
	Redactor::DeleteSpaces();
	Redactor::StringToLower();
	return userString;
}

void Redactor::DeleteSpaces() {
		if (strchr(userString.c_str(), ' ')) {
			for (int i = 0; i < userString.length(); i++) {
				if (userString[i] == ' ') {
					for(int j = i; j < userString.length(); j++) userString[j] = userString[j + 1];
				}
			}
		}
	}
void Redactor::StringToLower() {
		std::transform(userString.begin(), userString.end(), userString.begin(), tolower);
	}