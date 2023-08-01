#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>

#include "PosApp.h"
#include "Utils.h"
#include "NonPerishable.h"
#include "Perishable.h"
#include "Bill.h"

using namespace std;

namespace sdds {
	// function implementation

	// MENU ------------------------------------------------
	int PosApp::menu() {
		int select;
		bool checkInt;

		cout << "The Sene-Store" << endl;
		cout << "1- List items" << endl;
		cout << "2- Add item" << endl;
		cout << "3- Remove item" << endl;
		cout << "4- Stock item" << endl;
		cout << "5- POS" << endl;
		cout << "0- exit program" << endl;
		cout << "> ";

		do {
			checkInt = false;

			// prompt input
			cin >> select;

			// check the value is int
			if (cin.get() != '\n') {
				cout << "Invalid Integer, try again: ";

				// flush keyboard
				cin.clear();
				cin.ignore(10000, '\n');
			}
			else {
				// check the value is in the condition (>=0 && <= 5)
				if (select < 0 || select > 5) {
					cout << "[0<=value<=5], retry: > ";
				}
				else {
					checkInt = true;
					// break loop
				}
			}
		} while (!checkInt);

		return select;
	}

	// ADD ITEM (2) ------------------------------------------------
	PosApp& PosApp::addItem() {
		Item* temp{};
		title("Adding Item to the store");


		if (m_numItem == MAX_NO_ITEMS) {
			cout << "Inventory Full!" << endl;
		}
		else {
			char checkType;

			// ask use if the item is perisable
			cout << "Is the Item perishable? (Y)es/(N)o: ";
			do {
				cin >> checkType;
				if (cin.fail() || (checkType != 'y' && checkType != 'n')) {
					cin.clear();
					cin.ignore(10000, '\n');
					cout << "Only 'y' and 'n' are acceptable: ";
				}
			} while (cin.fail() || (checkType != 'y' && checkType != 'n'));

			// create new item
			if (checkType == 'y') {		// is perishable
				temp = new Perishable;
				// receive data
				cin >> *temp;
			}
			else if (checkType == 'n') {
				temp = new NonPerishable;
				// receive data
				cin >> *temp;
			}

			if (temp) {
				// receive data
				m_item[m_numItem++] = temp;
				title("DONE!");
			}


		}

		return *this;

	}

	// REMOVE ITEM (3) ------------------------------------------------
	PosApp& PosApp::removeItem() {
		bool remove = false;
		int selectRow{};

		title("Remove Item");
		title("Item Selection by row number");
		cout << "Press <ENTER> to start....";
		cin.ignore();

		selectRow = selectItem();

		cout << "Removing...." << endl;
		// print selected item in POS_FORM
		m_item[selectRow]->displayType(POS_FORM);
		m_item[selectRow]->write(cout);

		// delete all
		delete m_item[selectRow];
		m_item[selectRow] = nullptr;

		for (int i = selectRow; i < m_numItem; i++) {
			m_item[i] = m_item[i + 1];
			remove = true;
		}

		if (remove) {
			title("DONE!");
			m_numItem--;
		}

		return *this;
	}

	// SELECT ITEM
	int PosApp::selectItem() {
		Item* temp{};
		title("Listing Items");

		// sorting +++++++++++++++++++++++++++++++++++++++++++++++++++++
		for (int i = 0; i < m_numItem; i++) {

			for (int j = i + 1; j < m_numItem; j++) {
				int k = 0;
				while (m_item[i]->fName()[k] == m_item[j]->fName()[k]) {
					k++;
				}

				if (m_item[i]->fName()[k] > m_item[j]->fName()[k]) {
					temp = m_item[i];
					m_item[i] = m_item[j];
					m_item[j] = temp;
				}
			}
		}
		// sorting +++++++++++++++++++++++++++++++++++++++++++++++++++++
		// 
		// header ------------------------------
		headerList();

		// loop for printing
		for (int i = 0; i < m_numItem; i++) {

			cout << " ";
			cout.setf(ios::right);
			cout.width(3);
			cout.fill(' ');
			cout << i + 1;
			cout << " | ";
			cout.unsetf(ios::right);

			m_item[i]->displayType(POS_LIST);
			m_item[i]->write(cout) << endl;
		}

		// footer -------------------------------
		cout << "-----^--------^--------------------^-------^---^----^---------^-------------^" << endl;
		/// Select item
		int selectRow{};
		// get integer
		selectRow = U.getInt(1, m_numItem, "Enter the row number: ");

		return selectRow - 1; // return row index
	}

	// STOCK ITEM (4) ------------------------------------------------
	PosApp& PosApp::stockItem() {
		int selectRow{}, new_qty{};
		title("Select an item to stock");
		title("Item Selection by row number");
		cout << "Press <ENTER> to start....";
		cin.ignore();

		selectRow = selectItem();

		cout << "Selected Item:" << endl;
		// print selected item in POS_FORM
		m_item[selectRow]->displayType(POS_FORM);
		m_item[selectRow]->write(cout);

		// change quantity
		int stock_qty = MAX_STOCK_NUMBER - m_item[selectRow]->quantity();
		new_qty = U.getInt(1, stock_qty, "Enter quantity to add: ");

		// adding new quantity
		*m_item[selectRow] += new_qty;

		title("DONE!");

		return *this;
	}

	// LIST ITEM (1) ------------------------------------------------
	PosApp& PosApp::listItem() {
		Item* temp{};
		title("Listing Items");

		// sorting +++++++++++++++++++++++++++++++++++++++++++++++++++++
		for (int i = 0; i < m_numItem; i++) {

			for (int j = i + 1; j < m_numItem; j++) {
				int k = 0;
				while (m_item[i]->fName()[k] == m_item[j]->fName()[k]) {
					k++;
				}

				if (m_item[i]->fName()[k] > m_item[j]->fName()[k]) {
					temp = m_item[i];
					m_item[i] = m_item[j];
					m_item[j] = temp;
				}
			}
		}
		// sorting +++++++++++++++++++++++++++++++++++++++++++++++++++++
		// 
		// header ------------------------------
		headerList();

		// loop for printing
		for (int i = 0; i < m_numItem; i++) {

			cout << " ";
			cout.setf(ios::right);
			cout.width(3);
			cout.fill(' ');
			cout << i + 1;
			cout << " | ";
			cout.unsetf(ios::right);

			m_item[i]->displayType(POS_LIST);
			m_item[i]->write(cout) << endl;
		}

		// footer -------------------------------
		cout << "-----^--------^--------------------^-------^---^----^---------^-------------^" << endl;
		// cal total
		cout.setf(ios::right);
		cout.width(48);
		cout.fill(' ');
		cout << "Total Asset: $  |";
		double totalCost{};
		for (int i = 0; i < m_numItem; i++) {
			totalCost += (m_item[i]->cost() * m_item[i]->quantity());
		}
		cout.width(14);
		cout.precision(2);
		cout.fill(' ');
		cout << totalCost << "|" << endl;
		cout.unsetf(ios::right);
		cout << "-----------------------------------------------^--------------^" << endl << endl;

		return *this;
	}

	// POS (5) ------------------------------------------------
	PosApp& PosApp::POS() {
		char t_sku[MAX_SKU_LEN]{};
		Bill m_bill{};
		Item* t_item{};
		int qty;

		title("Starting Point of Sale");
		// loop for prompting sku / enter
		do {
			cout << "Enter SKU or <ENTER> only to end sale..." << endl;
			cout << "> ";
			// prompt for enter or sku
			cin.getline(t_sku, MAX_SKU_LEN + 1);

			// find match sku num
			if (cin.fail()) {
				cin.clear();
				cin.ignore(10000, '\n');
				cout << "SKU too long" << endl;
			}

			if (*t_sku) {
				t_item = search(t_sku);
				// find index

				if (t_item == nullptr) { // if address != nullptr
					cout << "!!!!! Item Not Found !!!!!" << endl;

				}
				else if (t_item->quantity() == 0) {
					cout << "Item out of stock" << endl;

				}
				else {
					t_item->displayType(POS_FORM);
					m_bill.add(t_item);
					t_item->write(cout) << endl;

					t_item->setQty(*t_item);

					//cout << *t_item << endl;

					cout << ">>>>> Added to bill" << endl;
					cout << ">>>>> Total: ";
					cout.setf(ios::fixed);
					cout.precision(2);
					cout << m_bill.total() << endl;
					cout.unsetf(ios::fixed);

				}
			}

			// ---------------------------




		} while (*t_sku);

		// print bill
		m_bill.print(cout);
		m_bill.clear();

		return *this;
	}

	// SEARCH
	Item* PosApp::search(const char* t_sku)const {
		Item* temp = nullptr;

		for (int i = 0; i < m_numItem; i++) {
			// compare sku
			if (*m_item[i] == t_sku) {
				// found
				temp = m_item[i];
				break;
			}
		}


		// return match otherwise nullptr
		return temp;
	}

	// SAVE called when select (0) ------------------------------------------------
	PosApp& PosApp::saveRecs() {
		title("Saving Data");
		ofstream output(m_fileName);
		//cout << "Saving data in datafile.csv" << endl;
		for (int i = 0; i < m_numItem; i++) {
			if (output) {
				output << *m_item[i] << endl;
			}
		}
		output.close();
		return *this;
	}

	// LOAD ITEM ------------------------------------------------
	PosApp& PosApp::loadRecs() {
		char type{};

		title("Loading Items");
		// load file into iptr array
		ifstream input(m_fileName);

		for (int i = 0; input; i++) {
			input >> type;
			input.ignore(); // for comma
			if (input) {

				if (m_item[i]) {
					delete m_item[i];
					m_item[i] = nullptr;
				}

				if (type == 'P') {
					m_item[i] = new Perishable;
					//delete m_item[i];
				}
				else if (type == 'N') {
					m_item[i] = new NonPerishable;
					//delete m_item[i];
				}

				if (m_item[i]) {
					input >> *m_item[i];
					m_numItem++;
					//delete[] m_item[i];
				}


			}
		}
		return *this;
	}

	// RUN MENU
	PosApp& PosApp::run() {
		int select;

		loadRecs();
		do {
			select = menu();
			switch (select)
			{
			case 1:
				listItem();
				break;
			case 2:
				addItem();
				break;
			case 3:
				removeItem();
				break;
			case 4:
				stockItem();
				break;
			case 5:
				POS();
				break;

			}

		} while (select != 0);
		saveRecs();

		cout << "Goodbye!" << endl;
		for (int i = 0; i < MAX_NO_ITEMS; i++) {
			if (m_item[i]) {
				delete m_item[i];
				m_item[i] = nullptr;
			}

		}
		return *this;
	}

	// constuctor and destructor

	PosApp::PosApp(const char* fileName) {
		//fileName = nullptr;
		if (fileName) {
			U.strcpy(m_fileName, fileName);
		}
	}
	PosApp::PosApp(const PosApp& S) {
		clear();
		operator=(S);
	}		// copy constructor

	PosApp& PosApp::operator=(const PosApp& S) {
		if (this != &S) {
			for (int i = 0; i < m_numItem; i++) {
				delete[] m_item[i];
			}
			clear();

			if (S.m_fileName) {
				U.strcpy(m_fileName, S.m_fileName);
			}
		}
		return *this;
	}	// copy assigment
	PosApp& PosApp::operator=(const char* fileName) {
		if (m_fileName != fileName) {
			/*for (int i = 0; i < m_numItem; i++) {
				delete[] m_item[i];
			}*/
			clear();

			if (fileName) {
				U.strcpy(m_fileName, fileName);
			}
		}
		return *this;
	}	// copy assigment

	PosApp::~PosApp() {
		/*for (int i = 0; i < m_numItem; i++) {
			delete m_item[i];
			m_item[i] = nullptr;
		}*/
	}

	// MS51 ---------------------------------------------
	// print title
	void PosApp::title(const char* title) {
		cout << ">>>> ";
		cout.width(72);
		cout.setf(ios::left);
		cout.fill('.');
		cout << title << endl;
		cout.unsetf(ios::left);
	}

	void PosApp::headerList() {
		// print 
		cout << " Row | ";
		cout.setf(ios::left);
		cout.width(6);
		cout.fill(' ');
		cout << "SKU" << " | ";

		cout.width(18);
		cout.fill(' ');
		cout << "Item Name" << " | ";

		cout.width(5);
		cout.fill(' ');
		cout << "Price" << " |TX |Qty | ";

		cout << "  Total" << " | ";

		cout.width(11);
		cout.fill(' ');
		cout << "Expiry Date" << " |" << endl;

		cout << "-----|--------|--------------------|-------|---|----|---------|-------------|" << endl;
	}

	// MS54 ---------------------------------------------
	PosApp& PosApp::operator+=(int r_qty) {
		Item::operator+=(r_qty);
		return *this;
	}

}