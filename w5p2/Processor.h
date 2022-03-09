// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           08.03.2022
//==============================================

#ifndef SDDS_PROCESSOR_H_
#define SDDS_PROCESSOR_H_
#include <string>
#include <iostream>
#include <functional> 
#include "CentralUnit.h"
#include "Job.h" //redundant

namespace sdds
{
	class Processor
	{
	private:
		CentralUnit<Processor>* m_host{};
		std::string m_brand{};
		std::string m_code{};
		size_t m_power{};
		Job* m_current{};
		void (*m_act)(CentralUnit<Processor>& hostCentralUnit, Processor* proc) {}; // ??????
		std::function<void(Processor* proc)> m_func{};
	public:
		Processor(CentralUnit<Processor>*hostCentralUnit, std::string brand, std::string code, size_t power);
		void run();
		explicit operator bool() const;
		Processor& operator+=(Job*& job);
		Job* get_current_job() const;
		void operator()();
		void on_complete(void (*act)(CentralUnit<Processor>& centrUnit, Processor* proc)); // might be names
		void on_error(std::function<void(Processor* proc)> func);
		Job* free();
		void display(std::ostream& ostr)const;
		friend std::ostream& operator<<(std::ostream& ostr, const Processor& rightOperand);

	};
}
#endif // !SDDS_PROCESSOR_H_

