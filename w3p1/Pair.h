//==============================================
// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           07.02.2022
//==============================================

#ifndef SDDS_PAIR_H_
#define SDDS_PAIR_H_
#include <iostream>

namespace sdds
{

	class Pair
	{
		std::string m_key{};
		std::string m_value{};
	public:
		const std::string& getKey() { return m_key; }
		const std::string& getValue() { return m_value; }
		Pair(const std::string& key, const std::string& value) : m_key{ key }, m_value{ value }{};
		Pair();

		std::ostream& write(std::ostream& ostr)const;
		// TODO: Add here the missing the prototypes for the members
		//           that are necessary if this class is to be used
		//           with the template classes described below.
		//       Implement them in the Pair.cpp file.
		
	};
	std::ostream& operator<<(std::ostream& ostr, const Pair& rightOperand);
}
#endif // !SDDS_PAIR_H_
