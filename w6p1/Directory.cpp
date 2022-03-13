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
		for (size_t i = 0; i < count(); i++)
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
			for (size_t i = 0; i < count(); i++)
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
		}
		else throw std::exception();
		
	}
	//Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& flag = {}) {
	//	if (flag.empty()) {
	//		for (auto i : m_contents) {
	//			if (m_name == i.name())
	//				return &i;
	//		}
	//	}
	//	else {
	//		find
	//	}
	//	return nullptr;
	//}
	//Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& flag) {
	//	for (auto i : m_contents) {
	//		if (m_name == i.name())
	//			return &i;
	//	}
	//	if(!flag.empty()) {
	//		find(name);
	//	}
	//	return nullptr;
	//}
	//Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& flag) {
	//	Resource* temp{};
	//	for (int i = 0; i < count(); i++) {
	//		if (m_contents[i].type() == NodeType::DIR)
	//			temp = find(name, flag);
	//		if (m_name == m_contents[i].name())
	//			temp = &m_contents[i];
	//	}
	//	return temp;
	//}
	Resource* Directory::find(const std::string& name, const std::vector<OpFlags>& flag) {
		Resource* temp{};
			for (auto i : m_contents) {
				if (i->type() == NodeType::DIR)
					temp = find(name, flag);
				if (name == i->name()) //m_name
					//temp = i;
					return i;
			}
		return temp;
	}
	Directory::~Directory() {

	}
};