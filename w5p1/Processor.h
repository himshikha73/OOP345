// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           20.02.2022
//==============================================

#ifndef SDDS_PROCESSOR_H_
#define SDDS_PROCESSOR_H_
#include <string>
#include <iostream>
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
	public:
		Processor(CentralUnit<Processor>*hostCentralUnit, std::string brand, std::string code, size_t power);
		void run();
		explicit operator bool() const;
		Processor& operator+=(Job*& job);
		Job* get_current_job() const;
		//~Processor();
	};
}
#endif // !SDDS_PROCESSOR_H_

