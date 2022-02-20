// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           20.02.2022
//==============================================

#ifndef SDDS_CENTRALUNIT_H_
#define SDDS_CENTRALUNIT_H_
#include <string>
#include <iostream>
#include "Job.h"
namespace sdds
{
	template <typename T>
	class CentralUnit
	{
	private:
		std::string m_type{};
		T** m_items{};
		Job* m_jobs[4];
		size_t m_size{};//stores the number of individual units hosted by the central unit.
		size_t m_count{};//stores the number of jobs queued upand waiting to be handled.
	public:
		std::ostream& log;
		CentralUnit() {}
		CentralUnit(std::string type, char* fileName);
	};

	static int findNonChar(std::string str, bool reversed = false) {
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

	template <typename T>
	CentralUnit<T>::CentralUnit(std::string type, char* fileName) {
		std::ifstream file(fileName);
		try {
			if (!file)
			{
				throw std::invalid_argument("File cannot be opened");
			}
		}
		catch (std::invalid_argument) {

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
		
		std::string brand;
		std::string model;
		int coreNum;
		size_t start_pos{};
		size_t end_pos{};
		for (size_t i = 0; i < count; i++)
		{
			try {
				std::getline(file, record);
				start_pos = findNonChar(record);
				end_pos = findNonChar(record, true);
				brand = record.substr(start_pos, end_pos);
				start_pos = record.find('|');
				record = record.substr(start_pos + 1);
				start_pos = findNonChar(record);
				end_pos = findNonChar(record, true);
				model = record.substr(start_pos, end_pos);
				start_pos = record.find('|');
				record = record.substr(start_pos + 1);
				coreNum = stoi(record);
				start_pos = 0;
				end_pos = 0;
			}
			catch (std::exception& err) {
				//WORK_CAPACITY = 0; ???????????
			}

		}
	}

}
#endif // !SDDS_CENTRALUNIT_H_