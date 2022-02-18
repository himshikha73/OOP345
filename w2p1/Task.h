//==============================================
// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           27.01.2022
//==============================================

#ifndef SDDS_TASK_H_
#define SDDS_TASK_H_
#include <iostream>
#include <chrono>

namespace sdds
{
    class Task
    {
    public:
        std::string m_name;
        std::string m_timeUnits;
        std::chrono::steady_clock::duration m_duration;
    };
}
#endif // !SDDS_TASK_H_
