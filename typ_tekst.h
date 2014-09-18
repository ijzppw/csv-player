#ifndef TYP_TEKST_H
#define TYP_TEKST_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "typ_dane.h"
using namespace std;
class DANE_tekst : public DANE
{
    private:
    vector< vector<string> > tekst_wartosc;
    public:
    DANE_tekst();
    ~DANE_tekst();
    void add_values();
    void show_all_data();
    void html_table_data();
};
#endif
