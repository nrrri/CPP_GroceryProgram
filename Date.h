#ifndef SDDS_DATE_H
#define SDDS_DATE_H

#include <fstream>	// for ifstream
#include <iostream>	// for istream

#include "Date.h"
#include "POS.h"
#include "Utils.h"
#include "Error.h"

namespace sdds {

	class Date : public Error {
		// date
		int tm_year{};
		int tm_month{};
		int tm_day{};
		int tm_hour{};
		int tm_min{};

		// date only flag
		// if true = dateOnly
		bool dateOnlyFlag{};

		// set ERROR PART ---------------------------
		// Error attribute
		// Print error code
		Error m_error{};
		// set ERROR PART ++++++++++++++


		// empty state
		void setEmpty();

		void setDate(int year, int month, int day, int hour, int min, bool dateOnly); // receive date input from console/user
	public:
		//-----------------------------------------------------
		// CONSTRUCTOR ++++++++++++++++
		Date(); // set to current system date
		// check only date
		Date(int year, int month, int day, int hour = 0, int min = 0);	// overload date [validate sequence and date]
		//~Date();
		// 
		//-----------------------------------------------------
		// validation date & time
		bool validateDate();
		bool validateTime();
		Date& dateOnly(bool dateOnly = false);

		//-----------------------------------------------------
		int calUniqueDate()const;
		int daysOfMonth(int year, int month);
		// comparison Operator overload
		bool operator==(Date& uniqueDate) const;
		bool operator!=(Date& uniqueDate) const;
		bool operator<(Date& uniqueDate) const;
		bool operator>(Date& uniqueDate) const;
		bool operator<=(Date& uniqueDate) const;
		bool operator>=(Date& uniqueDate) const;
		//-----------------------------------------------------
		// operator I/O
		// write
		std::ostream& write(std::ostream& ostr = std::cout) const;
		// read to file
		std::istream& read(std::istream& istr = std::cin);
		std::ifstream& load(std::ifstream& ifst);


		operator bool()const;
		bool operator!()const;


		const Error& error()const;

	};

	// write
	std::ostream& operator<<(std::ostream& ostr, const Date& S);
	// read
	std::istream& operator>>(std::istream& istr, Date& S);
	// load
	std::ifstream& operator>>(std::ifstream& ifst, Date& S);

}

#endif // !SDDS_DATE_H
