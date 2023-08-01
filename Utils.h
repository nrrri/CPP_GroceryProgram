#ifndef SDDS_UTILS_H_
#define SDDS_UTILS_H_

namespace sdds {
	class Utils {
	public:
		// cstring functions ---------------------
		int strlen(const char* src) const;
		char* strcpy(char* res, const char* src) const;
		char* strcpy(char* res, const char* src, int len) const;
		char* strcat(char* res, const char* src) const;
		bool strcmp(char* res, const char* src)const;
		int strcmp(const char* s1, const char* s2)const;
		//char* aloCopy(size_t length, const char* src)const;
		//----------------------------------------

		int getInt();
		int getInt(int min, int max, const char* prompt);

	};

	extern Utils U;
	//-----------------------------------------------------------------------------------
	// date system
	void getSystemDate(int& year, int& mon, int& day, int& hour, int& min, bool dateOnly);

	// unique date value
	int uniqueDateValue(int year, int mon, int day, int hour, int min);

	//-----------------------------------------------------------------------------------


}

#endif // !SDDS_UTILS_H_
