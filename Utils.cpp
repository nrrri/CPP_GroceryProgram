#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include "Utils.h"

using namespace std;
namespace sdds {
	Utils U;

	// cstring functions ---------------------
	int Utils::strlen(const char* src) const {
		if (src == nullptr) {
			return 0;
		}
		int i = 0;
		while (src[i] != '\0') {
			i++;
		}
		return i;
	}

	char* Utils::strcpy(char* res, const char* src) const {
		int i;
		for (i = 0; i < strlen(src); i++) {
			res[i] = src[i];
		}
		res[i] = '\0'; // null terminater
		return res;
	}

	char* Utils::strcpy(char* res, const char* src, int len) const {
		int i;
		for (i = 0; i < len && src[i]; i++) {
			res[i] = src[i];
		}
		res[i] = '\0'; // null terminater
		return res;
	}

	char* Utils::strcat(char* res, const char* src) const {
		int i = 0;
		int length = strlen(res);
		while (src[i]) {
			res[length + i] = src[i];
			i++;
		}
		res[length + i] = '\0';
		return res;
	}

	bool Utils::strcmp(char* res, const char* src)const {
		int i = 0;
		while (res[i] && src[i] && res[i] == src[i]) {
			i++;
		}
		return res[i] == src[i];
	}

	int Utils::strcmp(const char* s1, const char* s2)const {
		int i;
		for (i = 0; s1[i] && s2[i] && s1[i] == s2[i]; i++);
		return s1[i] - s2[i];
	}

	/*char* Utils::aloCopy(size_t length, const char* src)const {
		char* ret{};

		length = 0u;
		if (src) {
			length = U.strlen(src);
			ret = new char[length + 1];
			U.strcpy(ret, src);
		}
		return ret;*/
	
	//----------------------------------------
		// date & time functions
	void getSystemDate(int& year, int& mon, int& day, int& hour, int& min, bool dateOnly) {
		time_t t = time(NULL);
		tm lt = *localtime(&t);
		day = lt.tm_mday;
		mon = lt.tm_mon + 1;
		year = lt.tm_year + 1900;
		if (dateOnly) {
			hour = min = 0;
		}
		else {
			hour = lt.tm_hour;
			min = lt.tm_min;
		}
	}

	// unique date value
	int uniqueDateValue(int year, int mon, int day, int hour, int min) {
		return year * 535680 + mon * 44640 + day * 1440 + hour * 60 + min;
	}

	//----------------------------------------
	// get int
	int Utils::getInt() {
		int value{};
		bool done{};
		do {
			done = false;
			cin >> value;
			if (cin) {  // if(!cin.fail()){
				if (cin.get() != '\n') { // if the next char after int is not newline
					cout << "Only an integer please, retry: ";
				}
				else {
					done = true;
				}
			}
			else {
				cin.clear(); // clear the fail state
				cout << "Invalid Integer, try again: ";
			}
			(!done) && cin.ignore(10000, '\n');
		} while (!done);
		return value;
	}

	int Utils::getInt(int min, int max, const char* prompt) {
		int value{};
		if (prompt) cout << prompt;
		do {
			value = getInt();
		} while ((value < min || value > max) &&
			cout << "[" << min << "<=value<=" << max << "], retry: " << prompt);
		return value;
	}

}