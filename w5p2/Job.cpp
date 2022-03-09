//==============================================
// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           08.03.2022
//==============================================

#define  _CRT_SECURE_NO_WARNINGS
#include <string>
#include <cstring>
#include <stdexcept>
#include "Job.h"

using namespace std;
namespace sdds
{
	
	Job::Job(string title) {
		if (!title.empty()) {
			m_title = title;

			m_workUnits = (m_title.length() % 10) + 1;
			m_remainUnits = m_workUnits;
		}
		
	}
	bool Job::is_active()const {
		return m_active;
	}
	bool Job::is_complete() const{
		return m_remainUnits == 0u;
	}
	string Job::name() const{
		return m_title;
	}
	void Job::operator()(size_t workUnits) {
		m_active = true;
		if (workUnits > m_remainUnits) {
			m_remainUnits = 0;
			m_active = false;
			throw underflow_error(string("Job has only ") + to_string(m_remainUnits) + " workunits remaining"); // ????
		}
		m_remainUnits -= workUnits;
		if (m_remainUnits == 0)
			m_active = false;
	}
	void Job::display(ostream& ostr) {
		ostr << "`" << m_title << "` [";
		ostr.fill('0');
		ostr.setf(ios::right);
		ostr.width(2);
		ostr << m_remainUnits;
		ostr << "/";
		ostr.width(2);
		ostr << m_workUnits;
		ostr << " remaining]";
		ostr.unsetf(ios::right);
	}
	ostream& operator<<(ostream& ostr, Job& rightOperand) {
		rightOperand.display(ostr);
		return ostr;
	}
}