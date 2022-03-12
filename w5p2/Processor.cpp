//==============================================
// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           08.03.2022
//==============================================

#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
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
			if (m_host && m_current) {
				if (!m_current->is_complete()) {
					m_current->operator()(m_power);
				}
				else {
					delete m_current;
					m_current = nullptr;
				}
			}
			
		}
		catch (std::underflow_error&) {
			cout << "Processed over quota for " << *(m_current);
			delete m_current;
			m_current = nullptr;
		}
	}

	Processor::operator bool() const {

		return !m_current;
	}
	Processor& Processor::operator+=(Job*& job) {
		if (m_current) {
			throw exception();
		}
			m_current = job;
		return *this;
	}
	Job* Processor::get_current_job() const {
		return m_current;
	}
	void Processor::on_complete(void(*act)(CentralUnit<Processor>& centrUnit, Processor* proc))
	{
		m_act = act;
	}
	void Processor::on_error(std::function<void(Processor* proc)> func) {
		m_func = func;
	}
	Job* Processor::free() {
		Job* newJob = m_current;
		m_current = nullptr;
		return newJob;
	}

	void Processor::operator()() {
		if (m_current && !m_current->is_complete()) {
			try {
				m_current->operator()(m_power);
				if (m_act && m_current->is_complete())
					m_act(*m_host, this);
			}
			catch (std::underflow_error&) {
				if(m_func)
					m_func(this);
			}
		}
	}

	void Processor::display(ostream& ostr)const {
		ostr << "(" << m_power << ") " << m_brand << " " << m_code;
		if (m_current) {
			ostr << " processing ";
			m_current->display(ostr);
		}
	}

	ostream& operator<<(ostream& ostr, const Processor& rightOperand) {
		rightOperand.display(ostr);
		return ostr;
	}
}