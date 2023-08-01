#ifndef SDDS_POSAPP_H
#define SDDS_POSAPP_H

#include <iostream>
#include "Item.h"
namespace sdds {
	class PosApp : public Item {
		// store data file name
		char m_fileName[128];

		// Items pointer array
		// use max num for array size >> call iptr
		Item* m_item[MAX_NO_ITEMS]{};

		// nptr
		int m_numItem{};

	public:
		int menu(); // display menu system and return choice (int

		// menu list
		PosApp& addItem();
		PosApp& removeItem();
		int selectItem();
		PosApp& stockItem();
		PosApp& listItem();
		PosApp& POS();
		PosApp& saveRecs();
		PosApp& loadRecs();
		PosApp& run();
		Item* search(const char* sku)const;


		//PosApp();
		// constuctor and destructor
		PosApp(const char* fileName = nullptr);
		// rule of tree
		PosApp(const PosApp& S);			// copy constructor
		PosApp& operator=(const char* fileName);	// copy assigment
		PosApp& operator=(const PosApp& S);

		~PosApp();

		void title(const char* title);
		
		void headerList();

		PosApp& operator+=(int r_qty);

	};
}
#endif // !SDDS_POSAPP_H
