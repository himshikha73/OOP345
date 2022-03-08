//==============================================
// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           20.02.2022
//==============================================

#define  _CRT_SECURE_NO_WARNINGS
//#include <string>
//#include <algorithm>
//#include <iterator>
#include <iostream>
//#include <cstring>
//#include <iomanip>
#include "Processor.h"
using namespace std;
namespace sdds
{
	Processor::Processor(CentralUnit<Processor>* hostCentralUnit, std::string brand, std::string code, size_t power) :
		m_host{ hostCentralUnit }, m_brand{ brand }, m_code{ code }, m_power{power}
	{
	}
	void Processor::run() {
		try {
			if (m_host && m_current) { //delete nullptr
				if (!m_current->is_complete()) {
					m_current->operator()(m_power);
				}
				else {
					delete m_current;
					m_current = nullptr;
				}
			}
			
		}
		catch (std::underflow_error) {
			cout << "Processed over quota for " << *(m_current);
			delete m_current;
			m_current = nullptr; //might be redundant
		}
		//handle run
	}

	Processor::operator bool() const {
		return !m_current;
	}
	Processor& Processor::operator+=(Job*& job) {
		if (m_current) {
			throw exception();
		}
		//if(m_current == nullptr)
			m_current = job;
		return *this;
	}
	Job* Processor::get_current_job() const {
		return m_current;
	}

	void Processor::on_complete(void (*act)(CentralUnit<Processor>& hostCentralUnit, Processor* proc)) {
		//???????????
	}
	void Processor::on_error(std::function<void(Processor* proc)> func) {
		//delete func.;
		//m_current = nullptr;
	}
	Job* Processor::free(Processor* proc) {

		proc->m_current = nullptr;
		return proc->m_current;
	}

	void Processor::operator()() {
		if (!m_current) {
			
		}
		run();
	};

	void Processor::display(ostream& ostr)const {
		cout << "(" << m_power << ") " << m_brand << " " << m_code << " processing";
		if (m_current)
			m_current->display(ostr);
		//(POWER) BRAND CODE processing CURRENT_JOB_DETAILS
	}

	ostream& operator<<(ostream& ostr, const Processor& rightOperand) {
		rightOperand.display(ostr);
		return ostr;
	}
}