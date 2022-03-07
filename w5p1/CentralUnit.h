// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           20.02.2022
//==============================================

#ifndef SDDS_CENTRALUNIT_H_
#define SDDS_CENTRALUNIT_H_
#include <string>
//#include <cstring>
#include <iostream>
#include <fstream>
#include <stdexcept>

#include "Job.h"
//#include "Processor.h"
namespace sdds
{
	template <typename T>
	class CentralUnit
	{
	private:
		std::string m_type{};
		T** m_items{}; //a dynamically-allocated array of pointers to individual units of type T (i.e. any type). These are the units that will be hosted in the CentralUnit object.
		Job* m_jobs[4]{}; // a statically-allocated array of pointers to jobs that are queued up and waiting to be handled by an individual unit when the central unit is run. Only a maximum of 4 jobs can be queued up at any given time.
		size_t m_size{};//stores the number of individual units hosted by the central unit.
		size_t m_count{};//stores the number of jobs queued upand waiting to be handled.
	public:
		static std::ostream& log;
		CentralUnit(const std::string type,const char* fileName);
		~CentralUnit();
		CentralUnit(const CentralUnit& rightOperand); // copy constructor
		CentralUnit& operator=(const CentralUnit& rightOperand) = delete; // copy assignment operator
		CentralUnit& operator+=(const std::string jobName);
		CentralUnit(CentralUnit&& rightOperand);  // move copyconstructor
		CentralUnit& operator=(CentralUnit&& rightOperand); // move assignment operator
		void run();
		bool has_jobs()const; /// ????????????????
		size_t get_available_units()const;

		CentralUnit& operator+=(T* processor);
	};

	template <typename T>
	std::ostream& CentralUnit<T>::log = std::cout;

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

	//template <typename T>
	//CentralUnit<T>::CentralUnit() {}

	//T or Processor template
	template <typename T>
	CentralUnit<T>::CentralUnit(const std::string type, const char* fileName) : m_type{type} {
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
		size_t count = 0; 
		// count how many records are in the file
		do
		{
			std::getline(file, record);
			if (file)
				//++count; ?????????????????????????
				++count;
		} while (file);

		//set file to the beginning
		file.clear();
		file.seekg(std::ios::beg);
		
		if (count == 0)
			throw std::string("No units provided"); // mIght be redundant

		m_size = count;
		//m_items  = new dynamic_cast<Processor>(T*[m_size]);
		m_items = new T* [m_size];

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
				//std::cout << brand << " ";
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
				//std::cout << code << " ";
				
				//coreNum
				start_pos = end_pos + 1;
				record = record.substr(start_pos);
				power = stoi(record);
				//std::cout << power << std::endl;

				//start_pos = record.find('|');
				//record = record.substr(start_pos + 1);
				//start_pos = findNonChar(record);
				//end_pos = findNonChar(record, true);
				//model = record.substr(start_pos, end_pos);
				//start_pos = record.find('|');
				//record = record.substr(start_pos + 1);
				//coreNum = stoi(record);
			}
			catch (std::exception) {
				//file.ignore(1000,'/n');
				file.clear();
				power = 1;//WORK_CAPACITY = 0; ???????????
				//std::cout << std::endl;
			}
			start_pos = 0;
			end_pos = 0;
			//T[i] = new Processor(T[i], brand, code, power);
			//dynamic_cast<Processor*>(m_items[i]) = new Processor(&this, brand, code, power);
			//m_items[i] = new T(this, brand, code, power);
			m_items[i] = new T(this, brand, code, power);
		}
	}
	template <typename T>
	CentralUnit<T>& CentralUnit<T>::operator+=(const std::string jobName) {
		//try {
			if (m_count >= 4)
				throw std::exception("Job queue is full  ");
			//Job newJob = new Job();
			m_jobs[m_count++] = new Job(jobName);
		//}
		//catch(int i) {
			//std::cout << "STRING ERROR" << std::endl;
		//}
		return *this;
	}

	//template <> //specialization
	//void CentralUnit<Processor>::run() {
	//	//for (size_t i = 0; i < m_count; i++)
	//	for (size_t i = 0; i < m_size; i++)
	//	{
	//		if (*m_items[i] && m_count > 0) {
	//			*m_items[i] += m_jobs[m_count--];
	//			m_jobs[m_count] = nullptr;
	//		}
	//		m_items[i]->run();
	//		//std::cout << m_items[i]->get_current_job();
	//		//std::cout << dynamic_cast<Processor>(m_items[i]).run();
	//		// ???????????????????????????????????????????????????????????????????
	//	}
	//}

	template <typename T>
	void CentralUnit<T>::run() {
		//for (size_t i = 0; i < m_count; i++)
		for (size_t i = 0; i < m_size; i++)
		{
			if (*m_items[i] && m_count > 0) {
				*m_items[i] += m_jobs[--m_count];
				m_jobs[m_count] = nullptr;
			}
			//dynamic_cast<Processor*>(m_items[i])->run();
			m_items[i]->run();
			//static_cast<Processor>(m_items[i]->run());
			//std::cout << m_items[i]->get_current_job();
			//std::cout << dynamic_cast<Processor>(m_items[i]).run();
			// ???????????????????????????????????????????????????????????????????
		}
	}

	//template<typename T>
	//void CentralUnit<T>::run()
	//{
	//	//throw "Running something";
	//	for (auto i = 0u; i < this->m_size; ++i)
	//	{
	//		T& currentUnit = *(this->m_items[i]);
	//		if (this->m_count > 0 && this->m_count <= MAX_JOB && (bool)(*m_items[i]) == false)
	//		{
	//			Job* lastJob = this->m_job[m_count - 1];
	//			currentUnit += lastJob;
	//			--m_count;
	//			this->m_job[m_count] = nullptr;
	//		}
	//		currentUnit.run();
	//	}
	//}
	
	template <typename T>
	bool CentralUnit<T>::has_jobs()const {
		//get_available_units != m_size
		return m_count != 0 || this->get_available_units() != m_size; // &&
		// return ???????????????????????????????????????????????????
		//return false;
	}

	//template<typename T>
	//bool CentralUnit<T>::has_jobs() const
	//{
	//	for (size_t i = 0; i < this->m_size; i++)
	//	{
	//		if (this->m_items[i]->get_current_job() != nullptr)
	//		{
	//			return -1;
	//		}
	//	}
	//	return 0;
	//}

	template <typename T>
	size_t CentralUnit<T>::get_available_units() const {
		size_t count = 0;
		size_t flag = m_size;
		while (flag)
			if (m_items[--flag])
				count++;
			//count++;
		
		//for (size_t i = 0; i < m_size; i++)
		//{

		//}

		return count; //CHECK IT
	} 
	template <typename T>
	CentralUnit<T>::~CentralUnit() {
		for (size_t i = 0; i < m_size; i++)
		{
			delete m_items[i];
		}
		delete[] m_items;
	}

	// copy constructor
	template <typename T>
	CentralUnit<T>::CentralUnit(const CentralUnit& rightOperand) {
		//try {
			//throw 1;
			throw std::exception();
		//}
		//catch (int i) {
		//catch (std::exception) {
			//throw std::exception;
		//}
		//throw compilte time error
	} 

	// move copyconstructor
	template<typename T>
	CentralUnit<T>::CentralUnit(CentralUnit&& rightOperand) {
		operator=(std::move(rightOperand));
	}  
	// move copyconstructor
	template<typename T>
	CentralUnit<T>& CentralUnit<T>::operator=(CentralUnit&& rightOperand) {
		if (this != &rightOperand) {
			for (size_t i = 0; i < m_size; i++)
			{
				delete m_items[i];
			}
			delete[] m_items;

			for (size_t i = 0; i < m_count; i++)
			{
				delete m_jobs[i];
			}
			delete[] m_jobs;

			m_count = rightOperand.m_count;
			m_size = rightOperand.m_size;
			m_type = rightOperand.m_type;
			m_type = rightOperand.m_type;

			m_items = rightOperand.m_items;
			m_jobs = rightOperand.m_jobs;
			rightOperand.m_items = nullptr;
			rightOperand.m_jobs = nullptr;
		}
		return *this;
	} // move assignment operator

	//MIGHT BE REDUNDANT
	template<typename T>
	CentralUnit<T>& CentralUnit<T>::operator+=(T* processor)
	{
		this->m_items[this->m_size] = processor;
		this->m_size++;
		return *this;
	}

}
#endif // !SDDS_CENTRALUNIT_H_