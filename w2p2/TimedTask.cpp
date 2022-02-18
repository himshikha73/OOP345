//==============================================
// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           31.01.2022
//==============================================

#define  _CRT_SECURE_NO_WARNINGS
#include <string>
#include <cstring>
#include "TimedTask.h"
using namespace std;
namespace sdds
{
	TimedTask::TimedTask() : m_recordsNum(0)
	{

	}
	void TimedTask::startClock() 
	{
		m_startTime = std::chrono::steady_clock::now();
	}
	void TimedTask::stopClock()
	{
		m_stopTime = std::chrono::steady_clock::now();
	}
	void TimedTask::addTask(const char* taskName) {
		
		m_tasks[m_recordsNum].m_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(m_stopTime - m_startTime);
		m_tasks[m_recordsNum].m_name = taskName;
		m_tasks[m_recordsNum].m_timeUnits = "nanoseconds";
		m_recordsNum++;
	}
	ostream& TimedTask::write(ostream& ostr)const {
		ostr << "--------------------------" << endl;
		ostr << "Execution Times:" << endl;
		ostr << "--------------------------" << endl;
		for (int i = 0; i < m_recordsNum; i++)
		{
			ostr.setf(ios::left);
			ostr.width(21);
			ostr << m_tasks[i].m_name;
			ostr.unsetf(ios::left);
			ostr.setf(ios::right);
			ostr.width(13);
			ostr << m_tasks[i].m_duration.count();
			ostr.unsetf(ios::right);
			ostr << " " << m_tasks[i].m_timeUnits << endl;
		}
		ostr << "--------------------------" << endl;
		return ostr;
	}
	ostream& operator<<(ostream& ostr, const TimedTask& rightOperand)
	{
		rightOperand.write(ostr);
		return ostr;
	}
}