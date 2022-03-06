// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           20.02.2022
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
		Job(std::string title); //(m_title.length() % 10) + 1
		bool is_active()const ;
		bool is_complete()const ; //return m_workUnit == 0;
		std::string name()const ; //return new String(m_title);
		void display(std::ostream& ostr);
		void operator()(size_t workUnits); //m_remainUnits-workUnits, if(m_remainUnits == 0) m_active = false; if(workUnits > m_remainUnits) m_remainUnits = 0; + std::underflow_error
	};
	std::ostream& operator<<(std::ostream& ostr, Job& rightOperand);
}
#endif // !SDDS_JOB_H_