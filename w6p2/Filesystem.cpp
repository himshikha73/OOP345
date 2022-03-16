//==============================================
// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           12.03.2022
//==============================================

#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <exception>
#include <iostream>
#include <fstream>
#include "Filesystem.h"
#include "Directory.h"
#include "File.h"
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
	Filesystem::Filesystem(std::string fileName, std::string root) {
		m_root = new Directory(root);
		//m_current = new Directory(root);
		

		std::ifstream fileToRead(fileName);
		if (!fileToRead)
		{
			throw std::invalid_argument("File cannot be opened.");
		}
		size_t count = 0;
		std::string record;
		do
		{
			std::getline(fileToRead, record);
			if (fileToRead)
				++count;
		} while (fileToRead);
		//set file to the beginning
		fileToRead.clear();
		fileToRead.seekg(std::ios::beg);

		std::string path;
		std::string content;
		size_t start_pos{};
		size_t end_pos{};

		for (size_t i = 0; i < count; i++)
		{
			//set current to root directory
			m_current = m_root;
			start_pos = 0;
			end_pos = 0;

			std::getline(fileToRead, record);
			if (record.find('|') == -1) {
				//delete leading spaces
				start_pos = findNonWhiteSpace(record);
				record = record.substr(start_pos);
				start_pos = 0;
				record = record.substr(start_pos, findNonWhiteSpace(record, true) + 1);
				//find first '/'
				while(record.find('/') != -1){
					string temp;
					end_pos = record.find('/');
					temp = record.substr(start_pos, end_pos + 1);
					Directory* dir = dynamic_cast<Directory*>(m_current->find(temp));
					if (!dir) {
						dir = new Directory(temp); //might be RECURSIVE as it is folder
						operator+=(dir); //might be root instead of current
						m_current = dir;
					}
					else m_current = dir;
					record = record.substr(end_pos + 1);
				}
				
			}
			else {
				string pathName;
				end_pos = record.find('|');
				pathName = record.substr(start_pos, end_pos);
				//delete leading and trailing spaces
				start_pos = findNonWhiteSpace(pathName);
				pathName = pathName.substr(start_pos);
				start_pos = 0;
				end_pos = findNonWhiteSpace(pathName, true);
				pathName = pathName.substr(start_pos, end_pos + 1);

				//start_pos = findNonWhiteSpace(record);
				//end_pos = findNonWhiteSpace(record, true);
				//record = record.substr(start_pos, end_pos);
				start_pos = 0;
				end_pos = 0;
				while (pathName.find('/') != -1) {
					string directoryName;
					end_pos = pathName.find('/');
					directoryName = pathName.substr(start_pos, end_pos + 1);
					Directory* dir = dynamic_cast<Directory*>(m_current->find(directoryName));
					if (!dir) {
						dir = new Directory(directoryName); //might be RECURSIVE as it is folder
						operator+=(dir); //might be root instead of current
						m_current = dir;
					}else m_current = dir;
					pathName = pathName.substr(end_pos + 1);
				}

				start_pos = record.find('|');
				record = record.substr(start_pos + 1);
				start_pos = findNonWhiteSpace(record);
				record = record.substr(start_pos);
				start_pos = 0;
				end_pos = findNonWhiteSpace(record, true);
				record = record.substr(start_pos, end_pos + 1);

				File* file = new File(pathName, record);
				operator+=(file);
			}

/*			start_pos = findNonWhiteSpace(record);
			record = record.substr(start_pos);
			start_pos = 0;

			end_pos = record.find('|');
			path = record.substr(start_pos, end_pos - 1);
			start_pos = 0;
			path = path.substr(start_pos, findNonWhiteSpace(path, true) + 1);

			start_pos = end_pos + 1;
			record = record.substr(start_pos);
			start_pos = findNonWhiteSpace(record);
			record = record.substr(start_pos);
			end_pos = findNonWhiteSpace(record, true);
			content = content.substr(start_pos, end_pos);*/ //might be end_pos + 1
			//------------------------------------------------
			//end_pos = record.find('|');
			//start_pos = 0;
			//content = record.substr(start_pos, end_pos - 1); //-1
			//start_pos = 0;
			//content = content.substr(start_pos, findNonWhiteSpace(content, true) + 1);
		}
		m_current = m_root;
	}
	Directory* Filesystem::change_directory(const std::string& name) {
		if (name.empty()) {
			m_current = m_root;
		}
		else {
			Directory* newDir = dynamic_cast<Directory*>(m_root->find(name));
			if (!newDir)
				throw std::invalid_argument("Cannot change directory! " + name + " not found!");
			return newDir;
		}
		return m_current;
	}
	Directory* Filesystem::get_current_directory() const {
		return m_current;
	}
	Filesystem& Filesystem::operator+=(Resource* res) {
		*m_current += res;
		//return m_current;
		//???????????????????????
		return *this;
	}
	// move copyconstructor
	Filesystem::Filesystem(Filesystem&& rightOperand) {
		operator=(std::move(rightOperand));
	}
	// move assignment operator
	Filesystem& Filesystem::operator=(Filesystem&& rightOperand) {
		if (this != &rightOperand) {
			delete m_current;
			delete m_root;

			m_current = rightOperand.m_current;
			m_root = rightOperand.m_root;
			rightOperand.m_root = nullptr;
			rightOperand.m_current = nullptr;
		}
		return *this;
	}
	Filesystem::~Filesystem() {
		delete m_root;
		//delete m_current;
	}
}