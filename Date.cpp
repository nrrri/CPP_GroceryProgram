#include <iostream>
#include <fstream>
#include <iomanip>

#include "Date.h"
#include "POS.h"
#include "Utils.h"

using namespace std;
namespace sdds {

	void Date::setEmpty() {
		tm_year = 0;
		tm_month = 0;
		tm_day = 0;
		tm_hour = 0;
		tm_min = 0;

		//dateOnlyFlag = true;
		m_error = nullptr;
	}

	Date::Date() {
		setEmpty();
		getSystemDate(tm_year, tm_month, tm_day, tm_hour, tm_min, false); // set to false to avoid set only date
		// always validate
	}

	// check valid date format
	// overload date [validate sequence and date]
	Date::Date(int year, int month, int day, int hour, int min) {
		setEmpty();
		// check valid
		setDate(year, month, day, hour, min, false);

	}

	//-----------------------------------------------------------------------------------
	void Date::setDate(int year, int month, int day, int hour, int min, bool CheckFlag) {
		// min and hour are set default as 0
		//setEmpty();
		// set date
		tm_year = year;
		tm_month = month;
		tm_day = day;

		// set time
		if (CheckFlag) {
			// if dateOnly (true)
			this->dateOnly(CheckFlag); // set time to 0
		}
		else {
			tm_hour = hour;
			tm_min = min;
		}

		// after set date they will be validated
		validateDate();
	}

	// validation date & time
	bool Date::validateDate() {
		bool check = false;
		if (tm_year < MIN_YEAR || tm_year > MAX_YEAR) {
			m_error = "Invalid Year";
		}
		else {
			// check valid month
			if (tm_month < 0 || tm_month > 12) {
				m_error = "Invalid Month";
				check = false;

			}
			else {
				// check valid day
				if (tm_day < 0 || tm_day > daysOfMonth(tm_year, tm_month)) {
					m_error = "Invalid Day";
					check = false;
				}
				else {
					check = true;
				}
			}
		}

		// check if included time validation
		if (!dateOnlyFlag) {
			validateTime();
		}
		return check;
	}

	bool Date::validateTime() {
		bool check = false;
		//dateOnly(false);
		if (tm_hour < 0 || tm_hour > 23) {
			check = false;
			m_error = "Invalid Hour";
		}
		else {
			if (tm_min < 0 || tm_min > 59) {
				m_error = "Invalid Minute";
				check = false;
			}
			else {
				check = true;
			}
		}
		// check valid min

		return check;
	}

	//-----------------------------------------------------------------------------------

	// CAL DATE
	// calculate unique date
	int Date::calUniqueDate()const {
		return uniqueDateValue(
			this->tm_year,
			this->tm_month,
			this->tm_day,
			this->tm_hour,
			this->tm_min);
	}

	int Date::daysOfMonth(int year, int month) {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int mon = month >= 1 && month <= 12 ? month : 13;
		mon--;
		return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}


	// comparison Operator overload
	// use uniqueDateValue
	bool Date::operator==(Date& ROp) const {
		return calUniqueDate() == ROp.calUniqueDate();
	}

	bool Date::operator!=(Date& ROp) const {
		return calUniqueDate() != ROp.calUniqueDate();
	}

	bool Date::operator<(Date& ROp) const {
		return calUniqueDate() < ROp.calUniqueDate();
	}

	bool Date::operator>(Date& ROp) const {
		return calUniqueDate() > ROp.calUniqueDate();
	}

	bool Date::operator<=(Date& ROp) const {
		return calUniqueDate() <= ROp.calUniqueDate();
	}

	bool Date::operator>=(Date& ROp) const {
		return calUniqueDate() >= ROp.calUniqueDate();
	}
	//-----------------------------------------------------------------------------------


	// 
	std::ostream& Date::write(std::ostream& ostr) const {


		if (!m_error) {
			if (dateOnlyFlag) {
				// print just only date format
				// YYYY/MM/DD

				ostr << setfill('0')
					<< tm_year << "/"
					<< setw(2) << tm_month << "/"
					<< setw(2) << tm_day;
			}
			else {
				// print all
				// YYYY/MM/DD, HH:MN
				ostr << setfill('0')
					<< tm_year << "/"
					<< setw(2) << tm_month << "/"
					<< setw(2) << tm_day << ", "
					<< setw(2) << tm_hour << ":"
					<< setw(2) << tm_min;
			}
		}
		else {
			Error::write(ostr << m_error << "(");
			if (dateOnlyFlag) {
				// print just only date format
				// YYYY/MM/DD

				ostr << setfill('0')
					<< tm_year << "/"
					<< setw(2) << tm_month << "/"
					<< setw(2) << tm_day;
			}
			else {
				// print all
				// YYYY/MM/DD, HH:MN
				ostr << setfill('0')
					<< tm_year << "/"
					<< setw(2) << tm_month << "/"
					<< setw(2) << tm_day << ", "
					<< setw(2) << tm_hour << ":"
					<< setw(2) << tm_min;
			}
			ostr << ")";
		}

		return ostr;
	}

	std::istream& Date::read(std::istream& is) {
		is.clear();
		setEmpty();

		char delimiter;
		// read 3 interger (for DateOnly)
		is >> tm_year >> delimiter;
		if (is.fail()) {
			m_error = "Cannot read year entry";
			return is;
		};

		is >> tm_month >> delimiter;
		if (is.fail()) {
			m_error = "Cannot read month entry";
			return is;
		}

		is >> tm_day;
		if (is.fail()) {
			m_error = "Cannot read day entry";
			return is;
		}
		// read 2 more for all format date
		if (!dateOnlyFlag) {
			is.get(delimiter);
			if (delimiter == '\n') {

				tm_hour = 0;
				tm_min = 0;
			}
			else {
				is >> tm_hour >> delimiter;
				if (is.fail()) {
					m_error = "Cannot read hour entry";
					return is;
				}

				is >> tm_min;
				if (is.fail()) {
					m_error = "Cannot read minute entry";
					return is;
				}
			}
		}


		validateDate();
		return is;
	}

	std::ifstream& Date::load(std::ifstream& ifst) {
		int t_year = 0,
			t_month = 0,
			t_day = 0,
			t_hour = 0,
			t_min = 0;
		char delimiter;
		setEmpty();

		m_error.clear();

		ifst >> t_year >> delimiter >> t_month >> delimiter >> t_day;
		if (!dateOnlyFlag) {
			ifst >> delimiter >> t_hour >> delimiter >> t_min;
		}

		Date temp(t_year, t_month, t_day, t_hour, t_min);
		temp.dateOnly(dateOnlyFlag);
		if (!ifst.fail()) {
			temp.validateDate();

		}
		if (!temp.m_error) {
			*this = temp;
		}

		return ifst;
	}



	//-----------------------------------------------------------------------------------

	Date& Date::dateOnly(bool date) {
		if (date == true) {
			dateOnlyFlag = true;
		}
		else {
			dateOnlyFlag = false;
		}
		return *this;
	}

	//
	Date::operator bool()const {
		return m_error;
	}

	bool Date::operator !()const {
		return m_error;
	}

	const Error& Date::error()const {
		// return error attribute object
		Error::write(cout);
		return m_error;
	}


	//-----------------------------------------------------------------------------------
	// non member functions
	ostream& operator<<(ostream& ostr, const Date& S) {
		S.write(ostr);
		return  ostr;
	}

	// read file
	istream& operator>>(istream& istr, Date& S) {
		//S.read(istr);
		return S.read(istr);
	}

	// load
	ifstream& operator>>(ifstream& ifst, Date& S) {
		//S.read(ifst);
		return S.load(ifst);;
	}

}