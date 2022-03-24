//==============================================
// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           23.03.2022
//==============================================
#define  _CRT_SECURE_NO_WARNINGS
#define GET_VARIABLE_NAME(Variable) (#Variable)
#include <iostream>
#include <fstream>
#include <iterator>
#include <iomanip>
#include <string>
#include <algorithm>
#include "CovidCollection.h"
using namespace std;
namespace sdds
{
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

	CovidCollection::CovidCollection(std::string fileName) {
		std::ifstream fileToRead(fileName);
		if (!fileToRead)
		{
			throw std::invalid_argument("File cannot be opened.");
		}
		size_t count = 0;
		std::string record;

		//count number of lines
		do
		{
			std::getline(fileToRead, record);
			if (fileToRead)
				++count;
		} while (fileToRead);
		//set file to the beginning
		fileToRead.clear();
		fileToRead.seekg(std::ios::beg);

		size_t start_pos{};
		size_t end_pos{};

		for (size_t i = 0; i < count; i++)
		{
			Covid infection;
			start_pos = 0;
			end_pos = 0;

			//read whole line
			std::getline(fileToRead, record);

			//delete leading spaces
			start_pos = findNonWhiteSpace(record);
			record = record.substr(start_pos);

			start_pos = 0;

			end_pos = record.find(' ');
			if (record[end_pos + 1] != ' ') {
				end_pos = record.find(' ', end_pos + 1);
			}
			infection.m_country = record.substr(start_pos, end_pos);

			//find city
			record = record.substr(end_pos);
			start_pos = findNonWhiteSpace(record);
			record = record.substr(start_pos);

			start_pos = 0;
			end_pos = record.find(' ');
			if (record[end_pos + 1] != ' ') {
				end_pos = record.find(' ', end_pos + 1);
			}
			infection.m_city = record.substr(start_pos, end_pos);

			//find variant
			record = record.substr(end_pos);
			start_pos = findNonWhiteSpace(record);
			record = record.substr(start_pos);

			start_pos = 0;
			end_pos = record.find(' ');
			infection.m_variant = record.substr(start_pos, end_pos);

			//find year

			record = record.substr(end_pos);
			start_pos = findNonWhiteSpace(record);
			record = record.substr(start_pos);
			//record = record.substr(end_pos);
			infection.m_year = stoi(record);

			//find cases
			end_pos = record.find(' ');
			record = record.substr(end_pos + 1);
			infection.m_cases = stoi(record);

			//find deaths
			end_pos = record.find(' ');
			record = record.substr(end_pos + 1);
			infection.m_deaths = stoi(record);
			
			m_infections.push_back(infection);
		}
	}
	void CovidCollection::display(std::ostream& out) const {
		// below snippet find first number greater than 4
// find_if searches for an element for which
// function(third argument) returns true
		//for_each(m_infections.begin(),
		//	std::next(m_infections.begin(), 5),
		//	[](int x) {std::cout << ' ' << x; });
		//vector<Covid>::iterator it = ([=](int i) -> Covid
		//	{
		//		return m_infections.front();
		//	});
		//cout << "First number greater than 4 is : " << *p << endl;
		//vector<Covid>::iterator it;
		/*for (Covid i : m_infections)
		{
			out << i;
		}*/
		size_t totalCases{};
		size_t totalDeaths{};
		for_each(m_infections.begin(), m_infections.end(), [=, &totalDeaths, &totalCases, &out](Covid n) -> void 
			{
				totalCases += n.m_cases;
				totalDeaths += n.m_deaths;
				out << n;
			});
		out << "| ";
		out.unsetf(ios::right);
		out.width(62);
		out << "Total Cases Around the World:";
		out.width(7);
		out << totalCases << " |";
		out << "| ";
		out.unsetf(ios::right);
		out.width(62);
		out << "Total Deaths Around the World:";
		out.width(7);
		out << totalDeaths << " |";
	}
	template <typename T>
	bool CovidCollection::compare(const T& val1, const T& val2)const {
		return (val1 < val2);
	}
	void CovidCollection::sort(std::string name) {
		//country, variant, cases or deaths
		if (name == "country") {
			//std::sort(m_infections.begin(), m_infections.end(), compare(m_infections, m_infections));
			std::sort(m_infections.begin(), m_infections.end(), [](Covid& cov1, Covid& cov2) 
				{
					return cov1.m_country < cov1.m_country;
				});
		}
		else if (name == "variant") {
			std::sort(m_infections.begin(), m_infections.end(), [](Covid& cov1, Covid& cov2)
				{
					return cov1.m_variant < cov1.m_variant;
				});
		}
		else if (name == "cases") {
			std::sort(m_infections.begin(), m_infections.end(), [](Covid& cov1, Covid& cov2)
				{
					return cov1.m_cases < cov1.m_cases;
				});
		}
		else if (name == "deaths") {
			std::sort(m_infections.begin(), m_infections.end(), [](Covid& cov1, Covid& cov2)
				{
					return cov1.m_deaths < cov1.m_deaths;
				});
		}
		
	}

	//Review it!!!!
	void CovidCollection::cleanList() {
		for_each(m_infections.begin(), m_infections.end(), [](Covid n) -> void
			{
				if (n.m_variant == "[None]")
					n.m_variant = "";
			});
	}
	bool CovidCollection::inCollection(string name) const {
		for_each(m_infections.begin(), m_infections.end(), [=](Covid n) -> bool
			{
				return n.m_variant == name;
			});
	}
	std::list<Covid> CovidCollection::getListForCountry() const {

	}
	std::list<Covid> CovidCollection::getListForVariant() const {

	}
	ostream& operator<<(ostream& out, const Covid& theCovid) {
		//| COUNTRY(20) | CITY(15) | VARIANT(20) | YEAR(6) | CASES | DEATHS |
		out << "| ";
		out.unsetf(ios::right);
		out.setf(ios::left);
		out.width(21);
		out << theCovid.m_country;
		out << " | ";
		out.width(15);
		out << theCovid.m_city;
		out << " | ";
		out.width(20);
		out << theCovid.m_variant;
		out << " | ";
		out.unsetf(ios::left);
		out.setf(ios::right);
		out.width(6);
		theCovid.m_year < 0 ? out << ' ' : out << theCovid.m_year;
		out << " | ";
		out.width(4);
		out << theCovid.m_cases;
		out << " | ";
		out.width(3);
		out << theCovid.m_deaths;
		out << " | " << endl;
		out.unsetf(ios::right);
		return out;
	}
};