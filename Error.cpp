#include <iostream>
#include "Error.h"
#include "Utils.h"

using namespace std;

namespace sdds {
	void Error::clear() {
		delete[] m_des;
		m_des = nullptr;
	}

	Error::Error(const char* cstr) {
		int len;
		if (cstr) {
			len = U.strlen(cstr);
			m_des = new char[len + 1];
			U.strcpy(m_des, cstr);
		}
	};

	// rule of three

	// copy constuctor
	Error::Error(const Error& S) {
		clear();
		// send error message
		operator=(S);
	}

	// copy assign
	Error& Error::operator=(const Error& S) {
		if (this != &S) {
			clear();
			int len = U.strlen(S.m_des);
			if (S.m_des) {
				m_des = new char[len + 1];
				U.strcpy(m_des, S.m_des);
			}
		}
		return *this;
	}

	Error& Error::operator=(const char* cstr) {

		if (m_des != cstr) {
			delete[] m_des;
			clear();
			if (cstr) {
				m_des = new char[U.strlen(cstr) + 1];
				U.strcpy(m_des, cstr);
			}
		}
		return *this;
	}


	// destructor
	Error::~Error() {
		clear();
	};
	// end of rule of three

	ostream& Error::write(ostream& ostr) const {
		if (*this) {
			ostr << m_des;
		}
		return ostr;
	}

	Error::operator bool()const {
		// return true if it's not null
		return m_des != nullptr;
	}

	bool Error::operator!() const {
		return m_des == nullptr;
	}

	ostream& operator<<(ostream& osL, const Error& err) {
		return err.write(osL);
	}

}