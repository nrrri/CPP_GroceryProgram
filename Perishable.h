#ifndef SDDS_PERISHABLE_H_
#define SDDS_PERISHABLE_H_
#include <iostream>
#include "Item.h"
#include "Date.h"

namespace sdds {
	class Perishable : public Item {
	public:
		char itemType()const; // return 'P'

		// for Expired date
		Date m_expDate;
		// IO
		std::ostream& write(std::ostream& ostr) const;
		std::ofstream& save(std::ofstream& ofst) const;
		std::istream& read(std::istream& istr);
		std::ifstream& load(std::ifstream& ifst);

	};
}
#endif // !SDDS_PERISHABLE_H_


