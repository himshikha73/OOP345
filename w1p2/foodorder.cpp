//==============================================
// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           22.01.2022
//==============================================

#define  _CRT_SECURE_NO_WARNINGS
#include <string>
#include <cstring>
#include "foodorder.h"
using namespace std;
namespace sdds 
{

	double g_taxrate = 0; //enternal link for tax rate
	double g_dailydiscount = 0; //enternal link for disount

	static int counter = 0; // to count number of rows

	FoodOrder::FoodOrder() : m_price(0), m_dailySpecial(false){

	}
	//copy constructor
	FoodOrder::FoodOrder(const FoodOrder& foodOrder) {
		if (foodOrder) {
			*this = foodOrder;
		}
	}
	FoodOrder::~FoodOrder() {
		delete[] m_description;
	}
	//copy assignment
	FoodOrder& FoodOrder::operator=(const FoodOrder& foodOrder) {
		if (this != &foodOrder) { //if not self copy
			strcpy(m_customerName, foodOrder.m_customerName);
			delete[] m_description;
			m_description = new char[strlen(foodOrder.m_description) + 1];
			strcpy(m_description, foodOrder.m_description);
			m_price = foodOrder.m_price;
			m_dailySpecial = foodOrder.m_dailySpecial;
		}
		return *this;
	}
	//display formated data only if object is not empty
	void FoodOrder::display() const
	{
		cout.width(2);
		cout.setf(ios::left);
		cout << ++counter;
		cout << ". ";
		if (*this) {

			cout.width(10);
			cout << m_customerName;
			cout << '|';
			cout.width(25);
			cout << m_description;
			cout << '|';
			cout.width(12);
			cout.precision(2);
			cout.setf(ios::fixed);
			cout << m_price + (m_price * g_taxrate);
			cout.unsetf(ios::left);
			cout.unsetf(ios::fixed);
			cout << '|';
			if (m_dailySpecial) {
				cout.setf(ios::right);
				cout.precision(2);
				cout.setf(ios::fixed);
				cout.width(13);
				cout << (m_price + (m_price * g_taxrate)) - g_dailydiscount;
				cout.unsetf(ios::right);
				cout.unsetf(ios::fixed);
			}
			cout << endl;
		}
		else {
			cout << "No Order" << endl;
		}
	}
	void FoodOrder::read(istream& is)
	{
		if (is) {
			string toRead; 
			char dailySpecial = 'N';
			is.getline(m_customerName, 10, ',');
			//read String of any size
			getline(is, toRead,',');

			//free, allocate and copy value of boundless string to fixed size c-string
			delete[] m_description;
			m_description = new char[toRead.length() + 1];
			strcpy(m_description, toRead.c_str());

			is >> m_price;
			is.ignore();
			is >> dailySpecial;
			m_dailySpecial = dailySpecial != 'N';
			is.ignore();
		}
	}
	//check if customer name is not empty string
	FoodOrder::operator bool() const
	{
		return m_customerName[0];
	}
}