//==============================================
// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           13.02.2022
//==============================================

#ifndef SDDS_CHILD_H_
#define SDDS_CHILD_H_
#include <string>
#include <iostream>
#include "Toy.h"
namespace sdds
{
	class Child
	{
	private:
		int m_age{};
		int m_toysNum{};
		std::string m_name{};
		const Toy** m_toys{};
	public:
		Child(std::string name, int age, const Toy* toys[], size_t count);
		size_t size() const;
		friend std::ostream& operator<<(std::ostream& ostr, const Child& rightOperand);
		operator bool() const;
		Child(const Child& rightOperand); // copy constructor
		Child(Child&& rightOperand);  // move copyconstructor
		Child& operator=(const Child& rightOperand); // copy assignment operator
		Child& operator=(Child&& rightOperand); // move assignment operator
		~Child();
	};
}
#endif // !SDDS_CHILD_H_
