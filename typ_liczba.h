#ifndef TYP_LICZBA_H
#define TYP_LICZBA_H
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "typ_dane.h"
using namespace std;
class DANE_liczba : public DANE
{
    private:
    vector< vector<float> > liczba_wartosc;
    public:
    DANE_liczba();
    ~DANE_liczba();
    void add_values();
    void show_all_data();
    void html_table_data();
    void dodaj_wartosc();
    void odejmij_wartosc();
    void pomnoz_przez_wartosc();
    void podziel_przez_wartosc();
};
#endif
