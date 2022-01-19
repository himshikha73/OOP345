//==============================================
// Name:           Volodymyr Labliuk
// Student Number: 147302202
// Email:          vlabliuk@myseneca.ca
// Section:        NBB
// Date:           16.01.2022
//==============================================

#ifndef SDDS_FOODORDER_H_
#define SDDS_FOODORDER_H_
#include <iostream>
namespace sdds
{
    class FoodOrder
    {
    private:
        char m_customerName[10]{};
        char* m_description{};
        double m_price;
        bool m_dailySpecial;
    public:
        FoodOrder();
        ~FoodOrder();
        void display()const;
        void read(std::istream& is);
        operator bool() const;
    };

    extern double g_taxrate;
    extern double g_dailydiscount;
}
#endif // !SDDS_FOODORDER_H_
