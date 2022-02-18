//==============================================
// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           27.01.2022
//==============================================

#define  _CRT_SECURE_NO_WARNINGS
#include <string>
#include <cstring>
#include <fstream>
#include "ProteinDatabase.h"
using namespace std;
namespace sdds
{
	static int m_stringsNum;

	ProteinDatabase::ProteinDatabase()
	{
		m_stringsNum = 0; //assign in .h
	}
	ProteinDatabase::ProteinDatabase(std::string fileName)
	{
		m_stringsNum = 0; //assign in .h
		string toRead;
		ifstream in;
		in.open(fileName);
		in.ignore();
		while (in) {

			getline(in, toRead, '>');
			m_stringsNum++;
		}
		m_stringsNum--;
		//in.close();
		//in.open(fileName);
		in.clear();
		in.seekg(0);
		in.ignore();
		m_strings = new string[m_stringsNum];
		for (int i = 0; i < m_stringsNum; i++)
		{
			in.ignore(1000, '\n');
			getline(in, toRead, '>');
			m_strings[i] = toRead;
		}
	}
	size_t ProteinDatabase::size() const 
	{
		return m_stringsNum;
	}
	std::string ProteinDatabase::operator[](size_t index) const
	{
		//if (index < 0 || index > m_stringsNum - 1) { //23012
		////if (index == 0) {
		//	return  m_strings[index];
		//	
		//}
		//else {
		//	return "";
		//}
		if (m_stringsNum > 0 && static_cast<int>(index) >= 0 && static_cast<int>(index) <= m_stringsNum - 1) {
			return  m_strings[index];
		}
		else {
			return "";
		}
	}
	ProteinDatabase::operator bool() const 
	{
		return m_strings;
	}
	//copy constructor
	ProteinDatabase::ProteinDatabase(const ProteinDatabase& rightOperand)
	{
		if (rightOperand) {
			*this = rightOperand;
		}
	}
	ProteinDatabase& ProteinDatabase::operator=(const ProteinDatabase& rightOperand)
	{
		if (this != &rightOperand) { //if not self copy
			delete[] m_strings;
			//int len = rightOperand.m_strings->length();

			m_strings = new string[m_stringsNum];
			for (int i = 0; i < m_stringsNum; i++)
			{
				m_strings[i] = rightOperand.m_strings[i];
			}
			//m_strings = rightOperand.m_strings; //???
		}
		return *this;
	}
	ProteinDatabase::~ProteinDatabase() 
	{
		delete[] m_strings;
	}
}