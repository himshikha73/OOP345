//==============================================
// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           13.02.2022
//==============================================

#define  _CRT_SECURE_NO_WARNINGS
#include <string>
#include <iostream>
//#include <algorithm>
//#include <iterator>
//#include <cstring>
//#include <functional>
//#include <iomanip>
#include "Child.h"
using namespace std;
namespace sdds
{
	Child::Child(string name, int age, const Toy* toys[], size_t count) :
		m_age{ age },
		m_toysNum{ count },
		m_name{ name } {
		m_toys = new const Toy* [count];
		for (int i = 0; i < static_cast<int>(count); i++) {
			m_toys[i] = new Toy(*toys[i]);
		}
	}
	size_t Child::size() const {
		return m_toysNum;
	}
	ostream& operator<<(std::ostream& ostr, const Child& rightOperand) {
		static int CNT = 0;
		ostr << "--------------------------" << endl;
		ostr << "Child " << ++CNT << ": " << rightOperand.m_name + " " << rightOperand.m_age << " years old:" << endl;
		ostr << "--------------------------" << endl;
		//if (rightOperand.m_toys[CNT] != nullptr) {
		if (rightOperand.m_toys != nullptr) {
			for (size_t i = 0; i < rightOperand.size(); i++) { //m_toysNum
				//for (int i = 0; i < rightOperand.m_toysNum; i++) //rightOperand.m_toysNum ????
				//{
				ostr << *rightOperand.m_toys[i]; //???
				//(*PlaneAlfa.Parties[j]).name
			//}
			}
		}
		else {
			ostr << "This child has no toys!" << endl;
		}
		ostr << "--------------------------" << endl;
		return ostr;
	}
	Child::operator bool() const
	{
		return m_toys;
	}
	// copy constructor
	Child::Child(const Child& rightOperand) {
		if (rightOperand) {
			*this = rightOperand;
		}
	} 
	// move copyconstructor
	Child::Child(Child&& rightOperand) {
		operator=(std::move(rightOperand));
	}  
	// copy assignment operator
	Child& Child::operator=(const Child& rightOperand) {
		if (this != &rightOperand) { //if not self copy

			for (int i = 0; i < m_toysNum; i++)
			{
			   delete this->m_toys[i]; //this
			}
			delete[] this->m_toys;

			m_age = rightOperand.m_age;
			m_toysNum = rightOperand.m_toysNum;
			m_name = rightOperand.m_name;
			
			m_toys = new const Toy * [size()]; //m_toysNum
			for (size_t i = 0; i < size(); i++) //m_toysNum
			{
				m_toys[i] = new Toy(*rightOperand.m_toys[i]);
			}
			
		}
		return *this;
	} 
	// move assignment operator
	Child& Child::operator=(Child&& rightOperand) {
		if (this != &rightOperand) {


			for (int i = 0; i < m_toysNum; i++) {
				delete this->m_toys[i]; //this
			}
			delete[] this->m_toys;
			//move
			m_toys = rightOperand.m_toys;
			m_age = rightOperand.m_age;
			m_name = rightOperand.m_name;
			m_toysNum = rightOperand.m_toysNum;
			//delete
			rightOperand.m_toys = nullptr;
			rightOperand.m_age = 0;
			rightOperand.m_name = "";
			rightOperand.m_toysNum = 0;
		}
		return *this;
	} 
	Child::~Child() {

		for (int i = 0; i < m_toysNum; i++) {
			delete this->m_toys[i]; //this
		}
		delete[] this->m_toys;
		
	}
}