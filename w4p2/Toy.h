//==============================================
// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           13.02.2022
//==============================================

#ifndef SDDS_TOY_H_
#define SDDS_TOY_H_
#include <string>
#include <iostream>
namespace sdds
{
	class Toy
	{
	private: //protected
		const int HST = 13;
		unsigned int m_orderID{};
		int m_itemsNum{};
		double m_price{};
		std::string m_name{};
	public:
		Toy();
		Toy(const std::string& toy);
		void update(int numItems);
		std::ostream& write(std::ostream& ostr)const;
		friend std::ostream& operator<<(std::ostream& ostr, const Toy& rightOperand);
		//operator bool() const;
		//Toy(const Toy& rightOperand); // copy constructor
		//Toy& operator=(const Toy& rightOperand); // copy assignment operator
	};
}
#endif // !SDDS_TOY_H_