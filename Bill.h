// Final Project
// Point of Sale Application
// Bill.cpp
// Version 1.0
// Date  2023-03-29
// Author   Fardad Soleimanloo
// Description
// Generates Bill using Item::bprint()
//
/////////////////////////////////////////////////////////////////
#ifndef SDDS_BILL_H
#define SDDS_BILL_H
#include <iostream>
#include "Item.h"
namespace sdds{
   const unsigned MAX_BILL_ITEMS = 100u;
   class Bill {
      const Item* m_items[MAX_BILL_ITEMS]{};
      unsigned m_num = 0;
      double m_total = 0;
   public:
      /// <summary>
      /// Clears the Bill and sets it to an empty bill
      /// </summary>
      void clear();
      /// <summary>
      /// Adds an item to the bill
      /// </summary>
      /// <param name="item: ">Address of an Item that is sold</param>
      /// <returns>true if item is added or false if the bill if has reached its limit of number of items</returns>
      bool add(const Item* item);
      /// <summary>
      /// Calculates the total price of the items in the bill
      /// </summary>
      /// <returns>the total price</returns>
      double total()const;
      /// <summary>
      /// inserts the bill into ostream using the bprint method of the Item.
      /// </summary>
      /// <param name="ostr: ">cout object (or any other ostream)</param>
      /// <returns>reference of ostream</returns>
      std::ostream& print(std::ostream& ostr)const;
   };
}
#endif // SDDS_BILL_H


