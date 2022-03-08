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
#include <stdexcept>
//#include <iomanip>
#include "Job.h"

using namespace std;
namespace sdds
{
	
	Job::Job(string title) {
		if (!title.empty()) {
			//m_workUnits = (m_remainUnits % 10) + 1;
			m_title = title;
			/*int len = m_title.length();*/
			m_workUnits = (m_title.length() % 10) + 1; //+1;
			m_remainUnits = m_workUnits;
		}
		
	} //(m_title.length() % 10) + 1
	bool Job::is_active()const {
		return m_active;
	}
	bool Job::is_complete() const{
		return m_remainUnits == 0u;
	} //return m_workUnit == 0;
	string Job::name() const{
		return m_title;
	} //return new String(m_title);
	void Job::operator()(size_t workUnits) {
		m_active = true;
		if (workUnits > m_remainUnits) {
			m_remainUnits = 0;
			m_active = false;
			throw underflow_error(string("Job has only ") + to_string(m_remainUnits) + " workunits remaining"); // ????
		}
		//m_remainUnits -= m_workUnits;
		m_remainUnits -= workUnits;
		if (m_remainUnits == 0)
			m_active = false;
	} //m_remainUnits-workUnits, if(m_remainUnits == 0) m_active = false; if(workUnits > m_remainUnits) m_remainUnits = 0; + std::underflow_error
	void Job::display(ostream& ostr) {
		ostr << "`" << m_title << "` [";
		ostr.fill('0');
		ostr.setf(ios::right);
		ostr.width(2);
		ostr << m_remainUnits;
		ostr << "/";
		ostr.width(2);
		ostr << m_workUnits;
		ostr << " remaining]" << endl;
		ostr.unsetf(ios::right);

		//`JOB NAME`[XX / XX remaining]
	}


	
	ostream& operator<<(ostream& ostr, Job& rightOperand) {
		rightOperand.display(ostr);
		return ostr;
	}
}