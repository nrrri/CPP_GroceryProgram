#ifndef SDDS_ITEM_H_
#define SDDS_ITEM_H_
#include <iostream>
#include <fstream>

#include "POS.h"
#include "PosIO.h"
#include "Error.h"

namespace sdds {
	// encapsulate an Item to be sold by the POS system.
	class Item : public PosIO { // Item is derived class of PosIO but base class of Perish and NonPerish
		char m_sku[MAX_SKU_LEN]{};
		//char m_name[MAX_NAME_LEN]{};
		char* m_name{};
		double m_price{};
		bool m_tax{};
		// store number of item in the shop (Using Item)
		int m_quantity{};
	protected:
		// display type
		// will be used both POS_LIST and POS_FROM
		int m_type{};
		// error state
		// using class Error
		Error m_error{};
		// initialize
		void setEmpty();
		bool isEmpty() const;

	public:
		// empty constructor
		Item();
		//// rule of three --------------------------------
		Item(const Item& S);
		virtual ~Item();
		Item& operator=(const Item& S);
		//// end of Rule of three --------------------------

		//// Member operator overload ----------------------
		// compare SKU code (c-string)
		bool operator==(const char* cstr)const;
		// compare alphabet from their names
		bool operator>(const Item& ROp)const;
		bool operator<(const Item& ROp)const;

		// add value to quantity and return quantity
		int operator+=(int ROp_quantity);
		// reduce value to quantity
		virtual int operator-=(int ROp_quantity);
		operator bool()const;

		Item& setQty(Item& qty);

		//// Member function -------------------------------
		// pure virtual
		virtual char itemType()const; // will be used in Perish and NonPerish
		// display type
		Item& displayType(const int POS_type); // POS_LIST OR POS_FORM

		// cost query >> add tax if it has
		double cost()const;
		// quantity query
		int quantity() const;
		const char* fName() const;
		const char* sku()const;
		// set empty
		Item& clear();

		//// IO --------------------------------------------
		virtual std::ostream& write(std::ostream& ostr) const; // will be used in Peerish and NonPerish
		virtual std::ofstream& save(std::ofstream& ofst) const;
		virtual std::istream& read(std::istream& istr);
		virtual std::ifstream& load(std::ifstream& ifst);
		std::ostream& bprint(std::ostream& ostr)const;

		//// -----------------------------------------------

	};
		// read
		std::istream& operator>>(std::istream& is, Item& item);
		// load
		std::ifstream& operator>>(std::ifstream& ifs, Item& item);
	//helper overload
	double operator+=(double& totalPrice, const Item& S);
}
#endif // !SDDS_ITEM_H_