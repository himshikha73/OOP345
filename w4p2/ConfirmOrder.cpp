//==============================================
// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           13.02.2022
//==============================================

#define  _CRT_SECURE_NO_WARNINGS
//#include <string>
//#include <algorithm>
//#include <iterator>
//#include <iostream>
//#include <cstring>
//#include <functional>
//#include <iomanip>
#include "Toy.h"
#include "ConfirmOrder.h"
using namespace std;
namespace sdds
{
	ConfirmOrder::ConfirmOrder() {

	}
	ConfirmOrder& ConfirmOrder::operator+=(const Toy& toy) {
		bool unique = true;
		//allocate and copy
		const Toy** toys = new const Toy * [m_toysNum + 1]{};
		for (int i = 0; i < m_toysNum; i++)
		{
			toys[i] = m_toys[i];
		}
		//for (int i = 0; i < m_toysNum; i++)
		//{
		//	delete m_toys[i];
		//}
		m_toys = toys;

		//check for uniqueness
		for (int i = 0; i < m_toysNum; i++)
		{
			if (m_toys[i] == &toy) {
				unique = false;
			}
		}
		//add
		if (unique) {
			m_toys[m_toysNum++] = &toy;
		}
		return *this;
	}
	ConfirmOrder& ConfirmOrder::operator-=(const Toy& toy) {
		bool found = false;
		int index;
		//check for uniqueness
		for (int i = 0; i < m_toysNum && !found; i++)
		{
			if (m_toys[i] == &toy) {
				index = i;
				found = true;
			}
		}
		//remove
		if (found) {
			m_toys[index] = nullptr;
		}
		return *this;
	}
	ConfirmOrder::operator bool() const {
		return m_toys;
	}
	// copy constructor
	ConfirmOrder::ConfirmOrder(const ConfirmOrder& rightOperand) {
		if (rightOperand) {
			*this = rightOperand;
		}
	}
	// move copyconstructor
	ConfirmOrder::ConfirmOrder(ConfirmOrder&& rightOperand) {
		operator=(move(rightOperand));
	}
	// copy assignment operator
	ConfirmOrder& ConfirmOrder::operator=(const ConfirmOrder& rightOperand) {
		if (this != &rightOperand) { //if not self copy
			//for (int i = 0; i < m_toysNum; i++)
			//{
			//	delete m_toys[i];
			//}
			m_toysNum = rightOperand.m_toysNum;
			m_toys = new const Toy * [m_toysNum] {};
			for (int i = 0; i < m_toysNum; i++)
			{
				m_toys[i] = rightOperand.m_toys[i];
			}
		}
		return *this;
	}
	// move assignment operator
	ConfirmOrder& ConfirmOrder::operator=(ConfirmOrder&& rightOperand) {
		if (this != &rightOperand) {

			//for (int i = 0; i < m_toysNum; i++)
			//{
			//	delete m_toys[i];
			//}
			//move
			m_toysNum = rightOperand.m_toysNum;
			m_toys = rightOperand.m_toys;
			//delete
			rightOperand.m_toys = nullptr;
			rightOperand.m_toysNum = 0;
		}
		return *this;
	}
	ConfirmOrder::~ConfirmOrder() {
		//for (int i = 0; i < m_toysNum; i++)
		//{
		//	delete m_toys[i];
		//}
	}
	std::ostream& operator<<(std::ostream& ostr, const ConfirmOrder& rightOperand) {
		ostr << "--------------------------" << endl;
		ostr << "Confirmations to Send" << endl;
		ostr << "--------------------------" << endl;
		//if (rightOperand.m_toys[CNT] != nullptr) {
		if (rightOperand.m_toys != nullptr) {
			for (int i = 0; i < rightOperand.m_toysNum; i++) {
				if(rightOperand.m_toys[i]) //???
					ostr << *(rightOperand.m_toys[i]); 
			}
		}
		else {
			ostr << "There are no confirmations to send!" << endl;
		}
		ostr << "--------------------------" << endl;
		return ostr;
	}
}