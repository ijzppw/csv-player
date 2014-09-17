#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>

#include <climits>

#include "typ_liczba.h"
#include "main_funkcje.h"

using namespace std;
extern vector< vector<string> > main_containter;
extern DANE_liczba x_liczby;

DANE_liczba::DANE_liczba()
{
    //cout << "\nobiekt DANE_liczba utworzony!\n";
}

DANE_liczba::~DANE_liczba()
{
    cout << "\nobiekt DANE_liczba zniszczony!\n";
}


void DANE_liczba::add_values()
{
uint32_t i,j;

liczba_wartosc.resize(main_containter.size());

for (int i=0; i<main_containter.size(); i++)
{
    liczba_wartosc.at(i).resize(main_containter.at(i).size());
}

for (i=0; i<main_containter.size(); i++)
    {
        for (j=0; j<main_containter.at(i).size(); j++)
        {
            if(parse_item(main_containter.at(i).at(j)) == "...liczba")
            {
                liczba_wartosc.at(i).at(j) = atof(main_containter.at(i).at(j).c_str());
            }
            else liczba_wartosc.at(i).at(j) = NULL;

        }
    }
}




void DANE_liczba::show_all_data()
{
uint32_t i,j;

for (i=0; i<liczba_wartosc.size(); ++i)
    {

        for (j=0; j<liczba_wartosc.at(i).size(); ++j)
        {
           cout << "  [" << i<< "]["<< j << "]  ";
           cout << liczba_wartosc.at(i).at(j) << "\t";
        }
        cout << endl;
    }
}



void DANE_liczba::html_table_data()
{
    fstream plik;
    plik.open("table_liczby.html", ios::out);// otwieramy plik;


    uint32_t i,j;
    uint32_t x=liczba_wartosc.size()-1 ,y=0;

    for (i=0; i<liczba_wartosc.size(); ++i)
        {
            for (j=0; j<liczba_wartosc.at(i).size(); ++j)
            {
                if (j > y) y=j;
            }
        }

        plik << "<html><head></head><body>";
        plik << "<br/>PROJEKT CSV - liczby<br/><br/>";


        plik<<"<table rules=\"all\" style=\"width:100%; border-spacing:10px; background-color:#F0F0F0; border: 1px solid black;\">";

    if(x==0 )
    {
      plik << "<tr><td>brak danych do wyswietlenia!</td></tr>";
    }
    else
    {
       for (i=0; i<=x; ++i)
        {
            plik << "<tr>";
            plik << "<td>" << i+1 << "</td>";
            for (j=0; j<y; ++j)
            {
                if (j<liczba_wartosc.at(i).size())
                {
                    plik << "<td>" << liczba_wartosc.at(i).at(j) << "</td>";
                }
                else
                {
                    plik << "<td></td>";
                }
            }
            plik << "</tr>";
        }
    }

    plik << "</table></body></html>";
    plik.close();

}
