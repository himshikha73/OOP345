//==============================================
// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           07.02.2022
//==============================================

#define  _CRT_SECURE_NO_WARNINGS
#include <string>
#include <cstring>
#include "Pair.h"
using namespace std;
namespace sdds
{
	Pair::Pair(){};

	std::ostream& Pair::write(std::ostream& ostr)const 
	{
		ostr.setf(ios::right);
		ostr.width(20);
		ostr << m_key;
		ostr.setf(ios::left);
		ostr << ": " << m_value;
		ostr.unsetf(ios::left);
		return ostr;
	}

	std::ostream& operator<<(std::ostream& ostr, const Pair& rightOperand) 
	{
		rightOperand.write(ostr);
		return ostr;
	}
	//compare two Pair by key
	bool Pair::operator==(const Pair& RightOperand) 
	{
		return m_key == RightOperand.m_key;
	}
}