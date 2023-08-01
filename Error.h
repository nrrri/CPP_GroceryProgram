#ifndef SDDS_ERROR_H_
#define SDDS_ERROR_H_
#include <iostream>

namespace sdds {
	// Smart flag for checking error
	class Error {
		char* m_des{};
		// hold error message
	public:
		void clear();						// set empty
		Error() {};							// no error
		Error(const char* cstr);

		// rule of three
			// send error message
		Error(const Error& S);				// copy constuctor
		Error& operator=(const Error& S);	// copy 
		Error& operator=(const char* cstr);	// copy assign

		virtual ~Error();							// destructor
		// end of rule of three
		//Error& operator<<(const char* err);
		operator bool()const;				// return true if (m_des)
		bool operator!() const;

		// overload operator<<
		virtual std::ostream& write(std::ostream& ostr) const;
		//std::ostream& operator<<(std::ostream& ostr) const;

	};

	// overload operator<< non-member function
	std::ostream& operator<<(std::ostream& ostrLeftOperand, const Error& Roperand);
}

#endif // !SDDS_ERROR_H_