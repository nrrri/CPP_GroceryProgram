#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "PosIO.h"
using namespace std;

namespace sdds {

	ostream& operator<<(ostream& ostr, const PosIO& pos) {
		return pos.write(ostr);
	}

	ofstream& operator<<(ofstream& ofst, const PosIO& pos) {
		return pos.save(ofst);
	}

	istream& operator>>(istream& istr, PosIO& pos) {
		pos.read(istr);
		return istr;
	}

	ifstream& operator>>(ifstream& ifst, PosIO& pos) {
		return pos.load(ifst);
	}
}