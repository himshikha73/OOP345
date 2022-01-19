//==============================================
// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           16.01.2022
//==============================================

#define  _CRT_SECURE_NO_WARNINGS
#include <string>
#include "foodorder.h"
using namespace std;
namespace sdds 
{

	double g_taxrate = 0; //enternal link for tax rate
	double g_dailydiscount = 0; //enternal link for disount

	static int counter = 0; // to count number of rows

	FoodOrder::FoodOrder() : m_price(0), m_dailySpecial(false){

	}
	FoodOrder::~FoodOrder() {
		delete[] m_description;
		//m_description = nullptr;
	}
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
		string toRead;
		char dailySpecial;
		if (is) {

			is.getline(m_customerName, 10, ',');
			//is.getline(m_description, 25, ',');
			getline(is, toRead,',');

			//free, allocate and copy value of boundless string to fixed size c-string
			//m_description = nullptr;
			//delete[] m_description;
			m_description = nullptr;
			m_description = new char[toRead.length() + 1];
			strcpy(m_description, toRead.c_str());

			is >> m_price;
			is.ignore();
			is >> dailySpecial;
			if (dailySpecial == 'Y') {
				m_dailySpecial = true;
			}
			else if (dailySpecial == 'N') {
				m_dailySpecial = false;
			}
			is.ignore();
		}
	}
	FoodOrder::operator bool() const
	{
		return m_customerName[0];
	}
}