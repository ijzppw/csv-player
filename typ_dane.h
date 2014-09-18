#ifndef TYP_DANE_H
#define TYP_DANE_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;
class DANE
{
    private:
    public:
    DANE(){};
    ~DANE(){};
    virtual void show_all_data() = 0;
};
#endif
