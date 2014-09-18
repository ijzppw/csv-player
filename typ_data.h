#ifndef TYP_DATA_H
#define TYP_DATA_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "typ_dane.h"
using namespace std;
class DANE_data : public DANE
{
    private:
    vector< vector<string> > data_wartosc;
    public:
    DANE_data();
    ~DANE_data();
    void add_values();
    void show_all_data();
    void html_table_data();
};
#endif
