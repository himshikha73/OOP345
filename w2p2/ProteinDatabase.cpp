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
#include <fstream>
#include "ProteinDatabase.h"
using namespace std;
namespace sdds
{
	static int m_stringsNum = 0;

	static void cpy(char* des, const char* src) 
	{
		while (( * des++ = *src++));
	}
	static int len(const char* str) 
	{
		const char* end = str;
		while (*end++);
		return static_cast<int>(end - str) - 1;
	}
	static void allocNcpy(char*& des, const char* src) 
	{
		des = new char[len(src) + 1];
		cpy(des, src);
	}

	static void removeChar(char* str, char ch) 
	{
		int l = len(str);
		for (int i = 0; i < l; i++)
		{
			if (str[i] == ch)
			{
				for (int j = i; j < l; j++)
				{
					str[j] = str[j + 1];
				}
				l--;
				i--;
			}
		}
	}

	ProteinDatabase::ProteinDatabase()
	{

	}
	ProteinDatabase::ProteinDatabase(std::string fileName)
	{
		char delimiter;
		string toRead;
		ifstream in;
		in.open(fileName);
		in.get(delimiter);
		while (in) {
			getline(in, toRead, delimiter);
			m_stringsNum++;
		}
		m_stringsNum--;
		in.clear();
		in.seekg(0);
		

		m_strings = new string[size()];
		for (size_t i = 0; i < size(); i++)
		{
			in.ignore(1000, '\n'); //ignore description
			
			int ReadBufferSize = 61;
			char* data = new char[ReadBufferSize];
			char* str = data;
			int noOfBuffers = 1;
			bool done;
			do {
				done = true;
				in.getline(str, ReadBufferSize, delimiter); // if cin fails, it means entry was greater than 80 chars
				if (in.fail()) {
					noOfBuffers++;  // keep track of number of buffers to add
					char* temp = new char[(ReadBufferSize - 1) * noOfBuffers + 1]; // allocate bigger memory
					cpy(temp, data); // copy the already read test into temp
					delete[] data;  // delete the old (too short) memory
					data = temp;    // point to newly large allocated memory 
					str = data + (ReadBufferSize - 1) * (noOfBuffers - 1); // set the read pointer to continue reading the rest of text
					in.clear();   // clear cin to read again
					done = false;  //we are not done yet
				}
			} while (!done);   // go back and continue reading if not done
			allocNcpy(str, data);
			delete[] data;
			removeChar(str, '\n');
			m_strings[i] = str;
			delete[] str;
		}
	}
	size_t ProteinDatabase::size() const 
	{
		return m_stringsNum;
	}
	std::string ProteinDatabase::operator[](size_t index) const
	{
		if (m_strings && size() > 0 && index >= 0 && index <= size() - 1) {
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

			m_strings = new string[size()];
			for (size_t i = 0; i < size(); i++)
			{
				m_strings[i] = rightOperand.m_strings[i];
			}
		}
		return *this;
	}
	ProteinDatabase::ProteinDatabase(ProteinDatabase&& rightOperand) {  // move copyconstructor
		operator=(move(rightOperand));
	}
	ProteinDatabase& ProteinDatabase::operator=(ProteinDatabase&& rightOperand) { // move assignment 
		if (this != &rightOperand) {

			delete[] m_strings;
			m_strings = rightOperand.m_strings;
			rightOperand.m_strings = nullptr;
		}
		return *this;
	}
	ProteinDatabase::~ProteinDatabase() 
	{
		delete[] m_strings;
	}
}