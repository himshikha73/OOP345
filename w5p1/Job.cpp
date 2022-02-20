//==============================================
// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           20.02.2022
//==============================================

#define  _CRT_SECURE_NO_WARNINGS
#include <string>
//#include <algorithm>
//#include <iterator>
//#include <iostream>
#include <cstring>
//#include <iomanip>
#include "Job.h"
using namespace std;
namespace sdds
{
	Job::Job() {

	}
	Job::Job(std::string title) {
		m_workUnits = (m_remainUnits % 10) + 1;
	} //(m_title.length() % 10) + 1
	bool Job::is_active() {
		return m_active;
	}
	bool Job::is_complete() {
		return m_workUnits == 0;
	} //return m_workUnit == 0;
	std::string Job::name() {
		return m_title;
	} //return new String(m_title);
	auto Job::operator()(unsigned int workUnits) {
		try {
			if (workUnits > m_remainUnits) {
				m_remainUnits = 0;
				throw std::underflow_error("error"); // ????
			}
			m_remainUnits -= m_workUnits;
			if (m_remainUnits == 0)
				m_active = false;
		}
		catch (std::underflow_error) {

		}
	} //m_remainUnits-workUnits, if(m_remainUnits == 0) m_active = false; if(workUnits > m_remainUnits) m_remainUnits = 0; + std::underflow_error
	void Job::display(std::ostream& ostr) {
		ostr << "`" << m_title << "`[";
		ostr.fill('0');
		ostr.setf(ios::right);
		ostr.width(2);
		ostr << m_remainUnits;
		ostr << " / ";
		ostr.width(2);
		ostr << m_workUnits;
		ostr << " remaining]" << endl;
		ostr.unsetf(ios::right);

		//`JOB NAME`[XX / XX remaining]
	}
	
	std::ostream& operator<<(std::ostream& ostr, Job& rightOperand) {
		rightOperand.display(ostr);
		return ostr;
	}
}