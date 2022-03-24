//==============================================
// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           23.03.2022
//==============================================

#ifndef SDDS_FILE_H
#define SDDS_FILE_H
#include <string>
#include <vector>
#include <list>
namespace sdds
{

	struct Covid
	{
		std::string m_country{};
		std::string m_city{};
		std::string m_variant{};
		size_t m_cases{};
		int m_year{};
		size_t m_deaths{};
	};

	class CovidCollection
	{
	private:
		std::vector<Covid> m_infections;
	public:
		CovidCollection(std::string fileName);
		void display(std::ostream& out) const;
		void sort();
		void cleanList();
		bool inCollection() const;
		std::list<Covid> getListForCountry() const;
		std::list<Covid> getListForVariant() const;
	};
	std::ostream& operator<<(std::ostream& out, const Covid& theCovid);
}
#endif