#ifndef SDDS_POSIO_H_
#define SDDS_POSIO_H_
#include <iostream>
#include <fstream>

#include "Error.h"

namespace sdds {
	class PosIO : public Error {
		// 4 pure virtual methods
	public:
		virtual std::ostream& write(std::ostream& ostr) const = 0;
		virtual std::istream& read(std::istream& istr) = 0;
		virtual std::ofstream& save(std::ofstream& ofst) const = 0;
		virtual std::ifstream& load(std::ifstream& ifst) = 0;
		virtual ~PosIO() {};
	};
	// write
	std::ostream& operator<<(std::ostream& ostr, const PosIO& pos);
	// save
	std::ofstream& operator<<(std::ofstream& ofst, const PosIO& pos);

	// read
	std::istream& operator>>(std::istream& istr, PosIO& pos);
	// load
	std::ifstream& operator>>(std::ifstream& ifst, PosIO& pos);
}
#endif // !SDDS_POSIO_H_
