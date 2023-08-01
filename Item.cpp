#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Utils.h"
#include "Item.h"
using namespace std;

namespace sdds {

	void Item::setEmpty() {
		m_sku[0] = '\0';
		delete[] m_name;
		m_name = nullptr;
		m_price = 0;
		m_tax = false;
		m_quantity = 0;
		m_type = 0;
		m_error.clear();
	}

	bool Item::isEmpty() const {
		return m_name == nullptr;
	}

	Item::Item() {
		setEmpty();
	}

	// rule of three --------------------------------------

	Item::Item(const Item& i) {
		setEmpty();
		operator=(i);
	}

	Item::~Item() {
		delete[] m_name;
		m_name = nullptr;
	}

	Item& Item::operator=(const Item& S) {
		if (this != &S) {
			U.strcpy(m_sku, S.m_sku);
			m_price = S.m_price;
			m_tax = S.m_tax;
			m_quantity = S.m_quantity;
			m_type = S.m_type;

			// check error
			if (S.m_error) {
				m_error = S.m_error;
			}

			if (m_name) {
				delete[] m_name;
				m_name = nullptr;
			}
			m_name = new char[U.strlen(S.m_name) + 1];
			U.strcpy(m_name, S.m_name);
			
		}
		return *this;
	}
	// rule of three --------------------------------------

	// operator overload ----------------------------------
	// compare SKU code
	bool Item::operator==(const char* s)const {
		return U.strcmp(m_sku, s) == 0;
	}

	// compare alphabet from their names
	bool Item::operator>(const Item& i)const {
		// turn to ASCII number
		int num_a = (int)m_name[0];
		int num_b = (int)i.m_name[0];
		return num_a > num_b;
	}

	bool Item::operator<(const Item& i)const {
		// turn to ASCII number
		int num_a = (int)m_name[0];
		int num_b = (int)i.m_name[0];
		return num_a < num_b;
	}

	int Item::operator+=(int r_qty) {
		//int sum = m_quantity + value;
		m_quantity += r_qty;
		if (m_quantity > MAX_STOCK_NUMBER) {
			m_quantity = MAX_STOCK_NUMBER;
			m_error.clear();
			m_error = ERROR_POS_QTY;
		}
		return m_quantity;
	}

	// reduce value to quantity
	int Item::operator-=(int r_qty) {
		m_quantity -= r_qty;
		if (r_qty > m_quantity) {
			m_quantity = 0;
			m_error.clear();
			m_error = ERROR_POS_STOCK;
		}
		return m_quantity;
	}

	Item::operator bool() const {
		return !m_error;
	}

	Item& Item::setQty(Item& qty) {
		qty -= 1;
		return *this;
	}

	//// Member function -------------------------------
	char Item::itemType()const {
		return 'T';
	} // will be used in Perish and NonPerish

	Item& Item::displayType(const int POS_type) {
		m_type = POS_type;
		return *this;
	}

	double Item::cost() const {
		double t_cost{};
		if (m_tax) {
			t_cost = m_price * (1 + TAX); // if have tax
		}
		else {
			t_cost = m_price;
		}

		return t_cost;
	}

	// quantity query
	int Item::quantity()const {
		return m_quantity;
	}

	const char* Item::fName() const {
		return m_name;
	}

	const char* Item::sku()const {
		return m_sku;
	}


	// set empty
	Item& Item::clear() {
		m_error.clear();
		return *this;
	}

	std::ostream& Item::write(std::ostream& ostr) const {

		if (!isEmpty()) {
			if (m_error) {
				m_error.write(ostr);
			}
			else {
				char name[21]{};
				if (m_name != nullptr) {
					U.strcpy(name, m_name, 20);
				}

				// display
				ostr.setf(ios::fixed);
				ostr.precision(2);

				if (m_type == POS_LIST) {
					// display m_sku
					cout.setf(ios::left);
					ostr.width(7);
					ostr.fill(' ');
					ostr << m_sku;
					ostr << "|";

					// display name
					ostr.width(20);
					ostr.fill(' ');
					ostr << name;
					cout.unsetf(ios::left);
					ostr << "|";

					// display price
					ostr.width(7);
					ostr.fill(' ');
					ostr << m_price;
					ostr << "|";

					// display tax
					ostr.width(3);
					ostr.fill(' ');
					if (m_tax) { ostr << " X "; }
					else { ostr << ""; };
					ostr << "|";

					// display quantity
					ostr.width(4);
					ostr.fill(' ');
					ostr << m_quantity;
					ostr << "|";

					// display price with tax
					ostr.width(9);
					ostr.fill(' ');
					ostr << (cost() * m_quantity);
					ostr << "|";
				}
				else if (m_type == POS_FORM) {
					// header
					ostr.fill('=');
					ostr.width(13);
					ostr << '=';
					ostr << "v" << endl;

					// name
					ostr.setf(ios::left);
					ostr.width(13);
					ostr.fill(' ');
					ostr << "Name:";
					ostr << m_name << endl;

					// sku
					ostr.width(13);
					ostr.fill(' ');
					ostr << "Sku:";
					ostr << m_sku << endl;

					// Price
					ostr.width(13);
					ostr.fill(' ');
					ostr << "Price:";
					ostr << m_price << endl;

					// Price with tax
					ostr.width(13);
					ostr.fill(' ');
					ostr << "Price + tax:";
					if (m_tax) {
						ostr << cost();
					}
					else {
						ostr << "N/A";
					}

					// quantity
					ostr << endl;
					ostr.width(13);
					ostr.fill(' ');
					ostr << "Stock Qty:";
					ostr << m_quantity << endl;

					ostr.unsetf(ios::left);
				}
			}
		}
		return ostr;

	}

	std::ofstream& Item::save(std::ofstream& ofst) const {

		if (!isEmpty()) {
			if (m_error) {
				ofst << m_error << endl;
			}
			else {
				ofst.setf(ios::fixed);
				ofst.precision(2);
				ofst << itemType() << ",";
				ofst << m_sku << ",";
				ofst << m_name << ",";
				ofst << m_price << ",";
				ofst << m_tax << ",";
				ofst << m_quantity;
			}
		}
		return ofst;
	}

	std::istream& Item::read(std::istream& istr) {

		char t_sku[1024]{};
		char t_name[1024]{};
		char t_tax{};

		// prompt for SKU
		cout << "Sku" << endl;
		cout << "> ";
		do {
			istr >> t_sku;
			if (istr.fail() || U.strlen(t_sku) > MAX_SKU_LEN) {
				istr.clear();
				istr.ignore(10000, '\n');
				cout << ERROR_POS_SKU << endl;
				cout << "> ";
			}
		} while (istr.fail() || U.strlen(t_sku) > MAX_SKU_LEN);
		istr.ignore(10000, '\n');
		U.strcpy(m_sku, t_sku);
		

		if (this->m_name) { // recheck
			delete[] m_name;
			m_name = nullptr;
		}

		// prompt Name
		cout << "Name" << endl;
		cout << "> ";

		do {
			istr.getline(t_name, 1024);
			if (U.strlen(t_name) > MAX_NAME_LEN) {
				cout << ERROR_POS_NAME << endl;
				cout << "> ";
			}
		} while (U.strlen(t_name) > MAX_NAME_LEN);
		m_name = new char[U.strlen(t_name) + 1];
		U.strcpy(m_name, t_name);

				// prompt Price
		cout << "Price" << endl;
		cout << "> ";

		do {
			istr >> m_price;
			if (istr.fail() || m_price < 0) {
				cout << ERROR_POS_PRICE << endl;
				cout << "> ";
			}
			istr.clear();
			istr.ignore(10000, '\n');

		} while (istr.fail() || !(m_price > 0));

		// prompt tax
		cout << "Taxed?" << endl;
		cout << "(Y)es/(N)o: ";
		do {
			istr >> t_tax;
			if (istr.fail() || (t_tax != 'y' && t_tax != 'n')) {
				istr.clear();
				istr.ignore(10000, '\n');
				cout << "Only 'y' and 'n' are acceptable: ";
			}

		} while (istr.fail() || (t_tax != 'y' && t_tax != 'n'));
		t_tax == 'y' ? m_tax = true : m_tax = false;

		// prompt quantity
		cout << "Quantity" << endl;
		cout << "> ";

		do {
			istr >> m_quantity;
			if (istr.fail() || (m_quantity <= 0 || m_quantity > MAX_STOCK_NUMBER)) {
				istr.clear();
				istr.ignore(10000, '\n');
				cout << ERROR_POS_QTY << endl;
				cout << "> ";
			}

		} while (istr.fail() || (m_quantity <= 0 || m_quantity > MAX_STOCK_NUMBER));

		return istr;
	}

	std::ifstream& Item::load(std::ifstream& ifst) {
		// temp variable
		char t_sku[1024]{};
		char t_name[1024]{};
		double t_price{};
		int t_tax{};
		int t_quantity{};

		// clear m_err
		m_error.clear();

		// read all values, separate by comma ','
		ifst.getline(t_sku, 1024, ',');
		ifst.getline(t_name, 1024, ',');
		ifst >> t_price;
		ifst.ignore();
		ifst >> t_tax;
		ifst.ignore();
		ifst >> t_quantity;

		// if not fail then validate value one by one
		if (!ifst.fail()) {
			if (U.strlen(t_sku) > MAX_SKU_LEN) {
				m_error.clear();
				m_error = ERROR_POS_SKU;
			}
			else if (U.strlen(t_name) > MAX_NAME_LEN) {
				m_error.clear();
				m_error = ERROR_POS_NAME;
			}
			else if (t_price < 0) {
				m_error.clear();
				m_error = ERROR_POS_PRICE;
			}
			else if (t_tax != 0 && t_tax != 1) {
				m_error = ERROR_POS_TAX;
			}
			else if (t_quantity > MAX_STOCK_NUMBER) {
				m_error.clear();
				m_error = ERROR_POS_QTY;
			}

			// if validate
			if (!m_error) {
				// copy SKU
				U.strcpy(m_sku, t_sku);
				// copy name
				if (m_name) {
				delete[] m_name;
				m_name = nullptr;
				}
				m_name = new char[U.strlen(t_name) + 1];
				U.strcpy(m_name, t_name);
				// copy price
				m_price = t_price;
				// copy tax
				t_tax != 0 ? m_tax = true : m_tax = false;
				// copy quantity
				m_quantity = t_quantity;
			}
		}
		return ifst;
	}

	std::ostream& Item::bprint(std::ostream& ostr)const {

		char t_name[21]{};
		U.strcpy(t_name, m_name, 20);

		cout.fill(' ');
		cout.setf(ios::left);
		ostr << "| ";

		ostr.width(20);
		ostr << t_name;
		cout.unsetf(ios::left);
		ostr << "|";

		ostr.width(10);
		ostr.precision(2);
		ostr << cost();
		ostr << " |";

		ostr.width(3);
		if (m_tax) ostr << "T";
		else ostr << " ";
		ostr << "  |" << endl;

		return ostr;
	}

	std::istream& operator>>(std::istream& is, Item& item) {
		return item.read(is);
	}

	// recheck mem leak
	std::ifstream& operator>>(std::ifstream& ifs, Item& item) {
		return item.load(ifs);
	}

	//Helper

	double operator+=(double& value, const Item& i) {
		value += (i.cost() * i.quantity());
		return value;
	}



}