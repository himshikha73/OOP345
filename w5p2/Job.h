// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           08.03.2022
//==============================================

#ifndef SDDS_JOB_H_
#define SDDS_JOB_H_
#include <string>
#include <iostream>
namespace sdds
{
	class Job 
	{
	private:
		std::string m_title{};
		size_t m_workUnits{};
		size_t m_remainUnits{};
		bool m_active{};
	public:
		Job() = default;
		Job(std::string title);
		bool is_active()const;
		bool is_complete()const;
		std::string name()const;
		void display(std::ostream& ostr);
		void operator()(size_t workUnits);
	};
	std::ostream& operator<<(std::ostream& ostr, Job& rightOperand);
}
#endif // !SDDS_JOB_H_