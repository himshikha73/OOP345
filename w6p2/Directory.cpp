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
#include "Directory.h"
#include "Resource.h"
#include "File.h"
using namespace std;
namespace sdds
{
	Directory::Directory(std::string dirName) {
		m_name = dirName; //m_name = dirName + "/"; OR // m_parent_path + dirName;
		m_parent_path += m_name;
	}
	//sets the parent path to the parameter.
	void Directory::update_parent_path(const string& parent_path) {
		//m_parent_path = m_parent_path + m_name + parent_path;
		for (int i = 0; i < count(); i++)
		{
			m_contents[i]->update_parent_path(path());// might be . insetead of ->
		}
		//for (auto i : m_contents)
		//{
		//	i.m_parent_path = path(); //?????
		//}
	}
	NodeType Directory::type() const {
		return NodeType::DIR;

	};
	string Directory::path() const {
		return m_parent_path; // might be without name, it create double / (m_parent_path + m_name)
	}
	std::string Directory::name() const {
		return m_name;
	}
	int Directory::count() const {
		return static_cast<int>(m_contents.size());
	}
	size_t Directory::size() const {
		if (!m_contents.empty()) {
			size_t size = 0;
			for (int i = 0; i < count(); i++)
			{
				size += m_contents[i]->size();
			}
			return size;
		}
		return 0u;
	}
	//adds a resource to the directoryand returns a reference to the current directory.This member should check for existing resources in the directory with the same name :

	//if a match is found, throw and exceptionand do nothing else;
	//if no match is found, add the resourceand update the absolute path location of the added resource with the directory's full absolute path.
	Directory& Directory::operator+=(Resource* res) {
		if (!find(res->name())) {
			m_contents.push_back(res);
			//update_parent_path(res->path());
			update_parent_path(res->name());
			return *this;
		}
		else throw std::exception();	
	}
	Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& flag) {
		Resource* temp{};
		for (auto i : m_contents) {
			if (!flag.empty() && flag[0] == OpFlags::RECURSIVE) {
				if (i->type() == NodeType::DIR)
					temp = dynamic_cast<Directory*>(i)->find(name, flag);
			}
			if (name == i->name()) //m_name
				return i;
		}
		return temp;
	}
	void Directory::remove(const std::string& name, const std::vector<OpFlags>& flag) {
		Resource* temp{};
		bool found = false;

		temp = find(name, flag);
		if(!temp)
			throw string(name + " does not exist in DIRECTORY_NAME");
		if (temp->type() == NodeType::DIR) {
			if(flag.empty())
				throw std::invalid_argument(name + " is a directory.Pass the recursive flag to delete directories.");
		}
		delete[] temp;
		temp = nullptr;
		for (size_t i = 0; i < count(); i++)
		{
			if (!m_contents[i])
				m_contents.erase(m_contents.begin() + i);
		}
		//----------------------------------------------------------------------------------
		//for (size_t i = 0; i < count(); i++)
		//{
		//	if (m_contents[i]->type() == NodeType::DIR)
		//		if (!flag.empty())
		//			temp = dynamic_cast<Directory*>(m_contents[i])->find(name, flag);
		//		else throw std::invalid_argument(name + " is a directory.Pass the recursive flag to delete directories.");
		//	else {
		//		if (m_contents[i]->name() == name) {
		//			delete m_contents[i];
		//			m_contents[i] = nullptr;
		//			m_contents.erase(m_contents.begin() + i);
		//		}
		//	}
		//	if (temp) {
		//		delete temp;
		//		temp = nullptr;
		//		for (size_t i = 0; i < count(); i++)
		//		{
		//			if (m_contents[i])
		//			m_contents.erase(m_contents.begin() + i);
		//		}
		//	}
		//	else {
		//		throw string(name + " does not exist in DIRECTORY_NAME");
		//	}
		//----------------------------------------------------------------------------------
		//for (size_t i = 0; i < count(); i++)
		//{
		//	if (m_contents[i]->name() == name) {
		//		if (m_contents[i]->type() == NodeType::DIR) {
		//			if (!flag.empty())
		//				dynamic_cast<Directory*>(m_contents[i])->find(name, flag); //RECURSIVE FLAG MUST BE SET ????????????
		//			else
		//				throw std::invalid_argument(name + " is a directory.Pass the recursive flag to delete directories.");
		//		}
		//		temp = m_contents[i];
		//		m_contents.erase(m_contents.begin() + i);
		//		delete temp;
		//		found = true;

		//	}
		//}
		//if (!found)
		//	throw string(name + " does not exist in DIRECTORY_NAME"); //replace with DATA

	}
	void Directory::display(std::ostream& ostr, const std::vector<FormatFlags>& flag) const {
		ostr << "Total size: " << size() << " bytes" << endl; //might be loop
		for (size_t i = 0; i < count(); i++)
		{
			if (m_contents[i]->type() == NodeType::DIR)
				ostr << "D | ";
			if (m_contents[i]->type() == NodeType::FILE)
				ostr << "F | ";
			ostr.width(15);
			ostr.setf(ios::left);
			ostr << m_contents[i]->name();
			ostr.unsetf(ios::left);
			ostr << " | ";
			if (!flag.empty()) {
				ostr.width(2);
				ostr.setf(ios::right);
				if(m_contents[i]->type() == NodeType::DIR)
					ostr << m_contents[i]->count();
				else ostr << ' ';
				ostr << " | ";
				//---------------------
				ostr.width(4);
				ostr << m_contents[i]->size();
				ostr << " bytes";
				ostr << " | ";
				ostr.unsetf(ios::right);
			}
			ostr << endl;
		}
	}
	//Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& flag) {
	//	Resource* temp{};
	//	for (auto i : m_contents) {
	//		if (!flag.empty() && flag[0] == OpFlags::RECURSIVE)
	//			if (i->type() == NodeType::DIR)
	//				temp = dynamic_cast<Directory*>(i)->find(name, flag);
	//		if (name == i->name()) //m_name
	//			//temp = i;
	//			return i;
	//	}
	//	return temp;
	//}
	Directory::~Directory() {
		for (auto i : m_contents) {
			delete i;
		}
	}

};