// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           20.02.2022
//==============================================

#ifndef SDDS_CENTRALUNIT_H_
#define SDDS_CENTRALUNIT_H_
#include <string>
#include <cstring>
#include <iostream>
#include <fstream>
#include "Job.h"
namespace sdds
{
	template <typename T>
	class CentralUnit
	{
	private:
		std::string m_type{};
		T** m_items{}; //a dynamically-allocated array of pointers to individual units of type T (i.e. any type). These are the units that will be hosted in the CentralUnit object.
		Job* m_jobs[4]; // a statically-allocated array of pointers to jobs that are queued up and waiting to be handled by an individual unit when the central unit is run. Only a maximum of 4 jobs can be queued up at any given time.
		size_t m_size{};//stores the number of individual units hosted by the central unit.
		size_t m_count{};//stores the number of jobs queued upand waiting to be handled.
	public:
		std::ostream& log;
		CentralUnit();
		CentralUnit(const std::string type,const char* fileName);
		//CentralUnit(T* hostCentralUnit, std::string type, char* fileName, unsigned int workCapacity);
		~CentralUnit();
		CentralUnit(const CentralUnit& rightOperand); // copy constructor
		CentralUnit& operator=(const CentralUnit& rightOperand); // copy assignment operator
		CentralUnit& operator+=(const std::string jobName);
		void run();
		bool has_jobs()const; /// ????????????????
		int get_available_units();
	};

	static size_t findNonChar(std::string str, bool reversed = false) {
		if (reversed) {
			for (size_t i = str.length() - 1; i >= 0; i--)
			{
				if (str[i] != ' ')
					return i;
			}
		}
		for (size_t i = 0; i < str.length(); i++)
		{
			if (str[i] != ' ')
				return i;
		}
		return 0;
	}

	template <typename T>
	CentralUnit<T>::CentralUnit() {}

	//template <typename T>
	//CentralUnit<T>::CentralUnit(T* hostCentralUnit, std::string type, char* fileName, unsigned int workCapacity) {

	//}

	template <typename T>
	CentralUnit<T>::CentralUnit(const std::string type, const char* fileName) : log{std::cout} {
		//log = std::cout;
		std::ifstream file(fileName);
		//try {
			if (!file)
			{
				throw std::invalid_argument("File cannot be opened.");
			}
		//}
		//catch (std::invalid_argument error) {
			//log << "**EXPECTED EXCEPTION: " <<  error.what() << std::endl;
		//}
		std::string record;
		//size_t count = 0; ????????????????????????????????????????????????????????????
		// count how many records are in the file
		do
		{
			std::getline(file, record);
			if (file)
				//++count; ?????????????????????????
				++m_size;
		} while (file);

		//set file to the beginning
		file.clear();
		file.seekg(std::ios::beg);
		
		std::string brand;
		std::string code; //code
		int power; //power
		size_t start_pos{};
		size_t end_pos{};
		for (size_t i = 0; i < m_size; i++)
		{
			try {
				std::getline(file, record);
				//brand
				start_pos = findNonChar(record);
				record = record.substr(start_pos);
				start_pos = 0;
				//end_pos = findNonChar(record, true);
				end_pos = record.find('|');
				brand = record.substr(start_pos, end_pos - 1);
				start_pos = 0;
				brand = brand.substr(start_pos, findNonChar(brand, true) + 1);
				std::cout << brand << " ";
				//model
				start_pos = end_pos + 1;
				record = record.substr(start_pos);
				start_pos = findNonChar(record);
				record = record.substr(start_pos);
				end_pos = record.find('|');
				start_pos = 0;
				code = record.substr(start_pos, end_pos - 1); //-1
				start_pos = 0;
				code = code.substr(start_pos, findNonChar(code, true) + 1);
				std::cout << code << " ";
				
				//coreNum
				start_pos = end_pos + 1;
				record = record.substr(start_pos);
				power = stoi(record);
				std::cout << power << std::endl;

				//start_pos = record.find('|');
				//record = record.substr(start_pos + 1);
				//start_pos = findNonChar(record);
				//end_pos = findNonChar(record, true);
				//model = record.substr(start_pos, end_pos);
				//start_pos = record.find('|');
				//record = record.substr(start_pos + 1);
				//coreNum = stoi(record);
				start_pos = 0;
				end_pos = 0;
			}
			catch (std::exception& err) {
				//file.ignore(1000,'/n');
				file.clear();
				power = 1;//WORK_CAPACITY = 0; ???????????
				start_pos = 0;
				end_pos = 0;
				std::cout << std::endl;
			}

		}
	}
	template <typename T>
	CentralUnit<T>& CentralUnit<T>::operator+=(const std::string) {
		try {
			if (m_count > 4)
				throw 1;
			//Job newJob = new Job();
			m_jobs[m_count] = new Job;
		}
		catch(int i) {
			std::cout << "STRING ERROR" << std::endl;
		}
		return *this;
	}
	template <typename T>
	void CentralUnit<T>::run() { 
		for (size_t i = 0; i < m_count; i++)
		{
			// ???????????????????????????????????????????????????????????????????
		}
	}
	template <typename T>
	bool CentralUnit<T>::has_jobs()const {
		return false;
		// return ???????????????????????????????????????????????????
	}
	template <typename T>
	int CentralUnit<T>::get_available_units() {
		return m_size;
		//return ????????????????????????????????????????????????
	}
	template <typename T>
	CentralUnit<T>::~CentralUnit() {

	}
	template <typename T>
	CentralUnit<T>::CentralUnit(const CentralUnit& rightOperand) : log(std::cout) {
		//try {
			throw 1;
			//throw std::exception;
		//}
		//catch (int i) {
		//catch (std::exception) {
			//throw std::exception;
		//}
		//throw compilte time error
	} // copy constructor
	template <typename T>
	CentralUnit<T>& CentralUnit<T>::operator=(const CentralUnit<T>& rightOperand) {
		//try {
			throw std::exception;
		//}
		//catch (std::exception) {

		//}
		//throw compilte time error
	} // copy assignment operator

}
#endif // !SDDS_CENTRALUNIT_H_