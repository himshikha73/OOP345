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
//#include <iostream>
//#include <cstring>
//#include <iomanip>
#include "Processor.h"
using namespace std;
namespace sdds
{

	Processor::Processor() {

	}
	Processor::Processor(CentralUnit<Processor>* hostCentralUnit, std::string brand, std::string code, int power) :
		m_host{ hostCentralUnit }, m_brand{ brand }, m_code{ code }, m_power{power}
	{
	}
	void Processor::run() {
		//handle run
	}
	Processor::operator bool() const {
		return m_current;
	}
	Processor& Processor::operator+=(Job*& job) {
		if (this) {
			throw exception();
		}
		m_current = job;
		return *this;
	}
	Job* Processor::get_current_job() const {
		return m_current;
	}


}