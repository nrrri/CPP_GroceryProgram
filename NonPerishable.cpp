#include <iostream>
#include "NonPerishable.h"
#include "Item.h"

using namespace std;
namespace sdds {

	char NonPerishable::itemType()const {
		return 'N';
	}


	std::ostream& NonPerishable::write(std::ostream& ostr) const {
		if (!isEmpty()) { // check Item is good
			Item::write(ostr);
			// if Item = POS_LIST
			if (m_type == POS_LIST) {
				ostr << "     N / A   |";
				// doestn't have an expired date
			}
			else {
				ostr << "=============^" << endl;
			}
		}

		return ostr;
	}

} // end of namespace