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
#include <iostream>
#include "Bill.h"
#include "Date.h"
using namespace std;
namespace sdds {
   void Bill::clear() {
      m_num = 0;
      m_total = 0;
   }
   bool Bill::add(const Item* item) {
      bool added = false;
      if(m_num != MAX_BILL_ITEMS) {
         m_items[m_num++] = item;
         added = true;
         m_total += item->cost();
      }
      return added;
   }

   double Bill::total() const {
      return m_total;
   }

   std::ostream& Bill::print(std::ostream& ostr)const {
      unsigned i;
      Date now;
      now.dateOnly(false);
      ostr << "v---------------------------------------v" <<endl;
      ostr << "| " << now << "                     |" << endl;
      ostr << "+---------------------v-----------v-----+" << endl;
      ostr << "| Item                |     Price | Tax +" << endl;
      ostr << "+---------------------v-----------v-----+" << endl;
      for(i = 0; i < m_num; i++) {
         m_items[i]->bprint(ostr);         
      }
      ostr << "+---------------------^-----------^-----+" << endl;
      ostr << "| total:";
      ostr.width(25);
      ostr.setf(ios::right);
      ostr.setf(ios::fixed);
      ostr.precision(2);
      ostr.fill(' ');
      ostr << m_total << " |" << endl;
      ostr.unsetf(ios::right);
      ostr.unsetf(ios::fixed);
      return ostr << "^---------------------------------^" << endl;
   }
}
