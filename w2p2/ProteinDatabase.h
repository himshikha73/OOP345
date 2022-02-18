//==============================================
// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           31.01.2022
//==============================================

#ifndef SDDS_PROTEINDATABASE_H_
#define SDDS_PROTEINDATABASE_H_
#include <iostream>
namespace sdds
{
    class ProteinDatabase
    {
    private:
        
        std::string* m_strings{};
    public:
        ProteinDatabase();
        ProteinDatabase(const std::string fileName);
        size_t size() const; // returns the number of protein sequences stored in the current object
        std::string operator[](size_t index) const; //returns a copy of the protein sequence at the index received as the function parameter
        operator bool() const;
        ProteinDatabase(const ProteinDatabase& rightOperand); // copy constructor
        ProteinDatabase(ProteinDatabase&& rightOperand);  // move copyconstructor
        ProteinDatabase& operator=(const ProteinDatabase& rightOperand); // copy assignment operator
        ProteinDatabase& operator=(ProteinDatabase&& rightOperand); // move assignment operator
        ~ProteinDatabase();
    };
}
#endif // !SDDS_PROTEINDATABASE_H_
