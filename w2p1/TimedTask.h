//==============================================
// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           27.01.2022
//==============================================

#ifndef SDDS_TIMEDTASK_H_
#define SDDS_TIMEDTASK_H_
#include <iostream>
//#include "Task.h"
#include <chrono>

namespace sdds
{

    const int MAX_TASKS_NUM = 10;



    class TimedTask
    {
    private:
        struct Task {
            std::string m_name;
            std::string m_timeUnits;
            std::chrono::steady_clock::duration m_duration;
        } m_tasks[MAX_TASKS_NUM]{};
        int m_recordsNum{};
        std::chrono::steady_clock::time_point m_startTime;
        std::chrono::steady_clock::time_point m_stopTime;
        //Task m_arr[];

    public:
        TimedTask();
        //~TimedTask();
        //TimedTask(const TimedTask& rightOperand);
        //TimedTask& operator=(const TimedTask& rightOperand);
        void startClock();
        void stopClock();
        void addTask(const char* taskName);
        std::ostream& write(std::ostream& ostr)const;

        //void display()const;
        //void read(std::istream& is);
        //operator bool() const;
        friend std::ostream& operator<<(std::ostream& ostr, const TimedTask& rightOperand);
    };

    
}
#endif // !SDDS_TIMEDTASK_H_
