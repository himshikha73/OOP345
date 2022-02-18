#define  _CRT_SECURE_NO_WARNINGS
#include <string>
#include <cstring>
#include "Pair.h"
using namespace std;
namespace sdds
{
	//Pair::Pair() : m_key{ "No Key" }, m_value{ "No Value" }{};
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
}