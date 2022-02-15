//==============================================
// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           13.02.2022
//==============================================

#ifndef SDDS_CONFIRMORDER_H_
#define SDDS_CONFIRMORDER_H_
#include <string>
#include <iostream>
namespace sdds
{
	class ConfirmOrder
	{
	private:
		int m_toysNum{};
		const Toy** m_toys {};
	public:
		ConfirmOrder& operator+=(const Toy& toy);
		ConfirmOrder& operator-=(const Toy& toy);
		friend std::ostream& operator<<(std::ostream& ostr, const ConfirmOrder& rightOperand);
		operator bool() const;
		ConfirmOrder();
		ConfirmOrder(const ConfirmOrder& rightOperand); // copy constructor
		ConfirmOrder(ConfirmOrder&& rightOperand);  // move copyconstructor
		ConfirmOrder& operator=(const ConfirmOrder& rightOperand); // copy assignment operator
		ConfirmOrder& operator=(ConfirmOrder&& rightOperand); // move assignment operator
		~ConfirmOrder();

	};
}
#endif // !SDDS_CONFIRMORDER_H_