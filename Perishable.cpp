#include <iostream>

#include "Perishable.h"
#include "Date.h"

using namespace std;
namespace sdds {
	char Perishable::itemType()const {
		return 'P';
	}

	// IO
	std::ostream& Perishable::write(std::ostream& ostr) const {
		if (!isEmpty()) {
			Item::write(ostr);
			if (m_type == POS_LIST) {
				ostr << "  ";
				m_expDate.write(ostr);
				ostr << " " << '|';
			}
			else { // POS_FORM
				ostr << "Expiry date: ";
				m_expDate.write(ostr) << endl << "=============^" << endl;
			}
		}
		return ostr;
	}

	std::ofstream& Perishable::save(std::ofstream& ofst) const {
		// if in good state then extract with comma and expired date into ofstream
		if (ofst.good()) {
			Item::save(ofst);
			ofst << ",";
			m_expDate.write(ofst);
		}
		return ofst;
	}

	std::istream& Perishable::read(std::istream& istr) {

		if (!istr.fail()) {
			Item::read(istr);
			istr.ignore(10000, '\n');
			// if read id not fail then create date
			Date temp{};
			temp.dateOnly(true);
			//Date::dateOnly(true);

			// prompt expired date
			cout << "Expiry date (YYYY/MM/DD)" << endl;
			cout << "> ";
			// receive date
			temp.read(istr);
			temp.validateDate();
			if (!m_error) {
				m_expDate = temp;
			}

		}
		return istr;
	}

	std::ifstream& Perishable::load(std::ifstream& ifst) {

		if (!ifst.fail()) {
			Item::load(ifst);
			// create date and set dateOnly
			ifst.ignore(); // ignore one char to pass the comma

			Date temp{};
			temp.dateOnly(true);
			temp.load(ifst);

			// if date is in good state set expire date if not set error
			if (!temp.error()) {
				m_expDate = temp;
			}
		}
		return ifst;
	}

} // end of namespace