// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           08.03.2022
//==============================================

#ifndef SDDS_CENTRALUNIT_H_
#define SDDS_CENTRALUNIT_H_
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "Job.h"

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
		bool has_jobs()const;
		size_t get_available_units()const;
		T* operator[](const char* title) const;
		void display()const;
		CentralUnit& operator+=(T* processor);
		static void complete_job(CentralUnit& cu, T* proc);
	};

	template <typename T>
	void CentralUnit<T>::complete_job(CentralUnit<T>& host, T* unit) {

		log << "[COMPLETE] ";
		log << *(unit->free());
		log << " using " << *unit << std::endl;
		log << host.get_available_units() << " units available." << std::endl;
	}

	template <typename T>
	std::ostream& CentralUnit<T>::log = std::cout;

	static size_t findNonWhiteSpace(std::string str, bool reversed = false) {
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
	CentralUnit<T>::CentralUnit(const std::string type, const char* fileName) : m_type{type} {
		std::ifstream file(fileName);
			if (!file)
			{
				throw std::invalid_argument("File cannot be opened.");
			}
		std::string record;
		size_t count = 0; 
		// count how many records are in the file
		do
		{
			std::getline(file, record);
			if (file)
				++count;
		} while (file);

		//set file to the beginning
		file.clear();
		file.seekg(std::ios::beg);
		
		if (count == 0)
			throw std::string("No units provided");

		m_size = count;
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

				start_pos = findNonWhiteSpace(record);
				record = record.substr(start_pos);
				start_pos = 0;

				end_pos = record.find('|');
				brand = record.substr(start_pos, end_pos - 1);
				start_pos = 0;
				brand = brand.substr(start_pos, findNonWhiteSpace(brand, true) + 1);

				start_pos = end_pos + 1;
				record = record.substr(start_pos);
				start_pos = findNonWhiteSpace(record);
				record = record.substr(start_pos);
				end_pos = record.find('|');
				start_pos = 0;
				code = record.substr(start_pos, end_pos - 1); //-1
				start_pos = 0;
				code = code.substr(start_pos, findNonWhiteSpace(code, true) + 1);
				
				start_pos = end_pos + 1;
				record = record.substr(start_pos);
				power = stoi(record);
			}
			catch (std::exception) {

				file.clear();
				power = 1;

			}
			start_pos = 0;
			end_pos = 0;

			m_items[i] = new T(this, brand, code, power);

			m_items[i]->on_complete(CentralUnit<T>::complete_job);

			m_items[i]->on_error([=](T* unit) -> void
				{
					Job* newJob = unit->free();
					log << "Failed to complete job " << newJob->name() << std::endl;
					log << get_available_units() << " units available." << std::endl;
					delete newJob;
				});
		}
	}
	template <typename T>
	CentralUnit<T>& CentralUnit<T>::operator+=(const std::string jobName) {
			if (m_count >= 4)
				throw std::string("Job queue is full");
			m_jobs[m_count++] = new Job(jobName);
		return *this;
	}

	template <typename T>
	void CentralUnit<T>::run() {
		for (size_t i = 0; i < m_size; i++)
		{
			if (*m_items[i] && m_count > 0) {
				*m_items[i] += m_jobs[--m_count];
				m_jobs[m_count] = nullptr;
			}

			m_items[i]->operator()();
		}
	}

	template <typename T>
	void CentralUnit<T>::display()const {
		log << "Central" << m_type << " Unit list" << std::endl;
		for (size_t i = 0; i < m_size; i++)
		{
			log << "[";
			log.width(4);
			log.fill('0');
			log << i + 1;
			log << "] ";
			log << *m_items[i] << std::endl;
		}

	}

	template <typename T>
	T* CentralUnit<T>::operator[](const char* title) const {
		for (size_t i = 0; i < m_size; i++)
		{
			std::string str = title;
			if(m_items[i]->get_current_job())
			if (m_items[i]->get_current_job()->name() == str) 
				return m_items[i];
		} 
		throw std::out_of_range("Job is not being handled by a unit");
		return nullptr;
	}
	
	template <typename T>
	bool CentralUnit<T>::has_jobs()const {
		return m_count != 0 || get_available_units() != m_size;
	}



	template <typename T>
	size_t CentralUnit<T>::get_available_units() const {
		size_t count = 0;
		size_t flag = m_size;
		while (flag)
			if (!m_items[--flag]->get_current_job())
				count++;

		return count;
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
			throw std::exception();
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

	template<typename T>
	CentralUnit<T>& CentralUnit<T>::operator+=(T* proc)
	{
		if (*proc) {
			T** items{};
			if (get_available_units() >= m_size) {
				items = new T * [m_size + 1];
				for (size_t i = 0; i < m_size; i++)
				{
					items[i] = m_items[i];
				}
				items[m_size] = proc;
				delete[] m_items;
			}
			m_items = items;

			m_items[m_size]->on_complete(CentralUnit<T>::complete_job);
			m_items[m_size++]->on_error([=](T* unit) -> void
				{
					Job* newJob = unit->free();
					log << "Failed to complete job " << newJob->name() << std::endl;
					log << get_available_units() << " units available." << std::endl;
					delete newJob;
				});
		}
		else {
			throw std::string("Proc not available");
		}
		return *this;
	}

}
#endif // !SDDS_CENTRALUNIT_H_