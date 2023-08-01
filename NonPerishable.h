#ifndef SDDS_NONPERISHABLE_H_
#define SDDS_NONPERISHABLE_H_
#include <iostream>
#include "Item.h"

namespace sdds {
	class NonPerishable : public Item { // derive class
	public:
		char itemType()const; // return 'N'
		std::ostream& write(std::ostream& ostr) const;

	};
}
#endif // !SDDS_NONPERISHABLE_H_


