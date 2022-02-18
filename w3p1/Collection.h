#ifndef SDDS_COLLECTION_H_
#define SDDS_COLLECTION_H_
#include <iostream>
#include "Pair.h"


namespace sdds
{
    template <typename T, unsigned int CAPACITY>
    class Collection
    {
    private:
        T m_objects[CAPACITY]{};
        int m_elNum{};
        T m_dummyObj;
        int m_capacity;
    public:
        Collection();
        int size();
        void display(std::ostream& os = std::cout);
        bool add(const T& item);
        T operator[](size_t index) const;
    };

    template <typename T, unsigned int CAPACITY>
    Collection<T, CAPACITY>::Collection() : m_capacity{ CAPACITY }, m_dummyObj{} {
        m_capacity = CAPACITY;
    }

    template <typename T, unsigned int CAPACITY>
    int Collection<T, CAPACITY>::size() {
        return m_elNum;
    }

    template <typename T, unsigned int CAPACITY>
    void Collection<T, CAPACITY>::display(std::ostream& os) {
        /*displayHeader(os);*/
        os << "----------------------" << std::endl;
        os << "| Collection Content |" << std::endl;
        os << "----------------------" << std::endl;
        for (int i = 0; i < m_elNum; i++)
            os << m_objects[i] << std::endl;
    }

    template <typename T, unsigned int CAPACITY>
    bool Collection<T, CAPACITY>::add(const T& item) {
        if (m_elNum < m_capacity) {
            m_objects[m_elNum++] = item;
            return true;
        }
        else return false;
    }

    template <typename T, unsigned int CAPACITY>
    T Collection<T, CAPACITY>::operator[](size_t index) const {
        if (index >= 0 && index <= m_capacity - 1) {
            return m_objects[index];
        }
        else return m_dummyObj;
    }
    //template <typename T, unsigned int CAPACITY>
    //std::ostream& operator<<(std::ostream& ostr, const T& rO) {
    //    os << rO;
    //}
}
#endif // !SDDS_COLLECTION_H_