//==============================================
// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           07.02.2022
//==============================================

#ifndef SDDS_COLLECTION_H_
#define SDDS_COLLECTION_H_
#include <iostream>
#include "Pair.h"


namespace sdds
{
    template <typename T, unsigned int CAPACITY>
    class Collection
    {
    protected:
        unsigned int m_elNum{};
        T m_objects[CAPACITY]{};
        T m_dummyObj{};
    public:
        virtual ~Collection();
        int size();
        void display(std::ostream& os = std::cout);
        virtual bool add(const T& item);
        virtual T operator[](size_t index);
    };

    template <typename T, unsigned int CAPACITY>
    Collection<T, CAPACITY>::~Collection() {

    }

    // size of collection
    template <typename T, unsigned int CAPACITY>
    int Collection<T, CAPACITY>::size() {
        return m_elNum;
    }

    //display collection and header
    template <typename T, unsigned int CAPACITY>
    void Collection<T, CAPACITY>::display(std::ostream& os) {
        os << "----------------------" << std::endl;
        os << "| Collection Content |" << std::endl;
        os << "----------------------" << std::endl;
        for (unsigned int i = 0; i < m_elNum; i++)
            os << m_objects[i] << std::endl;
        os << "----------------------" << std::endl;
    }

    //add data to collection
    template <typename T, unsigned int CAPACITY>
    bool Collection<T, CAPACITY>::add(const T& item) {
        if (m_elNum < CAPACITY) {
            m_objects[m_elNum++] = item;
            return true;
        }
        else return false;
    }

    //return element of collection if exist
    template <typename T, unsigned int CAPACITY>
    T Collection<T, CAPACITY>::operator[](size_t index) {
        if (index >= 0 && index <= CAPACITY - 1) {
            return m_objects[index];
        }
        else return m_dummyObj;
    }

    //specialization for Collection of Pairs
    template <>
    Pair Collection<Pair, 100>::operator[](size_t index){
        if (m_elNum > 0 && index >= 0 && index <= m_elNum - 1) {
            return m_objects[index];
        }
        else return m_dummyObj = Pair("No Key", "No Value");
    }
}
#endif // !SDDS_COLLECTION_H_