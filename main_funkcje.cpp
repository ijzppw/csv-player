#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <cstdlib>
#include <climits>
#include "typ_data.h"
#include "typ_liczba.h"
#include "typ_tekst.h"
#include "main_funkcje.h"
using namespace std;


extern vector< vector<string> > main_containter;
extern DANE_data x_daty;
extern DANE_liczba x_liczby;
extern DANE_tekst x_teksty;

void read_file()
{
    main_containter.resize(0);

    fstream plik;
    plik.open("good.csv", ios::in);// otwieramy plik;

   if( plik.good() == false )
    {
       cout << "problem z plikiem !!!";
       exit(0);
    }

    else if( plik.good() == true )
    {
        string s;
        while ( !plik.eof())
        {
            getline(plik, s);
            s = s + '\n';
            cut_line(s);
        }
    }
plik.close();
classes_add_values();
}

vector<string> cut_line(string linia)
{
    vector <string> tymczasowy1;
    int dl = linia.length();
    int i=0;

    if(dl>0)
    {
        cout << "linia " <<  " :  " <<linia.substr(i, dl-i) << "\n";
        cout << "----------------------------------------------\n";

        while( linia.find(';', i) != string::npos )
        {
            tymczasowy1.push_back(linia.substr(i, linia.find(';', i) - i));
            i =  linia.find(';', i)+1;
        }
        tymczasowy1.push_back(linia.substr(i, dl-i-1));
    }
    main_containter.push_back(tymczasowy1);
return tymczasowy1;
}

string czy_data(string s)

{
    //cout << "czy_data:  " << s << endl;
    unsigned short dl = s.length();

    if (dl != 10)
    {
        return "nie_data";
    }

    bool w1 = (isdigit(s[0]) && isdigit(s[1]) && isdigit(s[2]) && isdigit(s[3])
            && isdigit(s[5]) && isdigit(s[6]) && isdigit(s[8]) && isdigit(s[9])
            && s[4] == '-' && s[7] == '-' );

    if (w1 == 0)
    {
        return "nie_data";
    }
    int rok = atoi(s.substr(0,4).c_str());
    unsigned short miesiac = atoi(s.substr(5,2).c_str());
    unsigned short dzien = atoi(s.substr(8,2).c_str());

    bool w2 = (miesiac > 0  && miesiac <=12 && dzien > 0);

    if (w2 == 0)
    {
        return "nie_data";
    }

    int rok_p[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
    int rok_z[12] = {31,28,31,30,31,30,31,31,30,31,30,31};

    bool czy_przestepny = false;
    if((rok%4 == 0 && rok%100 != 0) || rok%400 == 0) czy_przestepny = true;

    if(
       (  czy_przestepny && dzien <= rok_p[miesiac-1]) ||
       ( !czy_przestepny && dzien <= rok_z[miesiac-1])
       )
    {
        return "data";
    }
return "nie_data";
}

string czy_liczba(string s)
{
    //cout << "czy_liczba:  " << s << endl;
    int dl = s.length();
    //cout << "dlugosc: " << dl << endl;

    bool w1 = ( dl == 1 && isdigit(s[0]) );
    bool w1_plus = ( dl>=1 && ( s[0] == '+' || s[0]=='-' || isdigit(s[0]) ) );

    unsigned int point_counter =0;
    unsigned int comma_counter =0;
    unsigned int nie_ok=0;

    if (dl==0)
    {
        return "nie_liczba";
    }
    else if (dl==1 && w1)
    {
        return "liczba";
    }

    else if (dl>1)
    {
        for (int i=1; i<dl; i++)
        {
            if ((s[i]) == '.')
            {
                point_counter++;
            }
            else if ((s[i]) == ',')
            {
                comma_counter++;
            }
            else if ( s[i] != ',' && s[i] != '.' && !isdigit(s[i]) )
            {
                nie_ok++;
                //cout << "nie_ok:  "<<nie_ok << endl;
            }
        }
    }
    if ( (point_counter + comma_counter) > 1 || nie_ok != 0 || !w1_plus)
    {
        return "nie_liczba";
    }

return "liczba";
}

string parse_item(string s)
{
    if(czy_data(s) == "data") return "...data";
    else if(czy_liczba(s) == "liczba") return "...liczba";

    return "...tekst";
}

void show_all()
{
uint32_t i,j;

for (i=0; i<main_containter.size(); ++i)
    {
        for (j=0; j<main_containter.at(i).size(); ++j)
        {
           cout << "  [" << i<< "]["<< j << "]  ";
           cout << main_containter.at(i).at(j) <<"\t";
        }
    cout << endl;
    }
}

void html_table()
{
fstream plik;
plik.open("table.html", ios::out);// otwieramy plik;


uint32_t i,j;
uint32_t x=main_containter.size()-1 ,y=0;

for (i=0; i<main_containter.size(); ++i)
    {
        for (j=0; j<main_containter.at(i).size(); ++j)
        {
            if (j > y) y=j;
        }
    }
    plik << "<html><head></head><body>";
    plik << "<br/>PROJEKT CSV<br/><br/>";
    plik<<"<table rules=\"all\" style=\"width:100%; border-spacing:10px; background-color:#F0F0F0; border:1 px solid\">";

if(x==0 )
{
  plik << "<tr><td>brak danych do wyswietlenia!</td></tr>";
}

else
{
    plik << "<tr><th>&nbsp;</th>";
    for (j=0; j<y; ++j)
    {
        plik << "<th style=\"background-color:yellow;\"> KOLUMNA: " << j+1 << "</th>";

    }
    plik <<"</tr>";


   for (i=0; i<x; ++i)
    {
        plik << "<tr>";
        plik << "<td>" << i+1 << "</td>";

        for (j=0; j<y; ++j)
        {

            if (j<main_containter.at(i).size())
            {
                if(parse_item(main_containter.at(i).at(j))=="...data")
                {
                    plik << "<td style=\"background-color:lightgrey;\">" << main_containter.at(i).at(j) << "</td>";
                }
                else if(parse_item(main_containter.at(i).at(j))=="...liczba")
                {
                    plik << "<td style=\"background-color:#ffcc66;\">" << main_containter.at(i).at(j) << "</td>";
                }
                else if(parse_item(main_containter.at(i).at(j))=="...tekst")
                {
                    plik << "<td style=\"background-color:#COD9D9;\">" << main_containter.at(i).at(j) << "</td>";
                }

            }
            else
            {
                plik << "<td style=\"background-color:black;\">&nbsp</td>";
            }
        }
        plik << "</tr>";
    }
}

    plik << "</table><br/></body></html>";
    plik.close();
}

void menu1()
{
    cout << "MENU:\n";
    cout << "1. ** wczytaj plik: \n";
    cout << "2. ** wyswietl wczytane dane\n";
    cout << "3. ** generowanie tabeli html\n";
    cout << "4. ** sprawdz format danych\n";
    cout << "5. ** dodaj wartosci do poszczegolnych klas\n";
    cout <<"\n\n";
    return;
}
//void dodatkowe_opcje()
//{
//string a[10];
//a[0] = "...moze pozniej\n";
//a[1] = "...na razie nie ma dodatkowych opcji\n";
//a[2] = "...oj, tego chyba jeszcze nie ma!";
//a[3] = "nie nie nie...moment. obecnie nad tym pracujemy!";
//a[4] = "3...2...1...oj, cos sie popsulo !";
//a[5] = "maybe later, alligator!";
//a[6] = "no i popsules/as !!! a mialo byc takie pieknie...";
//a[7] = "to se ne da";
//a[8] = "ta opcja jest jeszcze niedostepna";
//a[9] = "jojc... sie chyba cos wysypalo :/";
//cout << a[rand()%10];
//
//return;
//}

void dodatkowe_opcje()
{
    char wybor;

    while (wybor != '6')
    {
        cout << "MENU - LICZBY:\n";
        cout << "1. ** dodawanie\n";
        cout << "2. ** odejmowanie\n";
        cout << "3. ** mnozenie\n";
        cout << "4. ** dzielenie\n";
        cout << "5. ** powrot do menu\n";
        cout << "6. ** WYJSCIE \n + powrot do glownego menu ";
        cin>>wybor;


        switch(wybor)
        {
        case '1':
            cout <<"\nwybrana opcja: 1 -  dodawanie "<<endl;
            system("clear");
            x_liczby.dodaj_wartosc();
            cout << "\nok\n";
            break;
        case '2':
            cout <<"\nwybrana opcja: 2 -  odejmowanie "<<endl;
            system("clear");
            x_liczby.odejmij_wartosc();
            cout << "\nok\n";
            break;
        case '3':
            cout <<"\nwybrana opcja: 3 -  mnozenie "<<endl;
            system("clear");
            x_liczby.pomnoz_przez_wartosc();
            cout << "\nok\n";
            break;
        case '4':
            cout <<"\nwybrana opcja: 4 -  dzielenie "<<endl;
            system("clear");
            x_liczby.podziel_przez_wartosc();
            cout << "\nok\n";
            break;
        case '5':
            cout <<"\nwybrana opcja: 5 -  powrot do menu\n "<<endl;
            system("clear");
            dodatkowe_opcje();
            cout << "\nok\n";
            break;
        case '6':
            cout <<"\nwybrana opcja: 6 -  powrot do glownego menu\n "<<endl;
            system("clear");
            menu1();
            cout << "\nok\n";
            break;
        }
    }

}


void format_dane()
{
    string a;
    cout << "wpisz dane do porownania: ";
    cin.ignore();
    getline (cin,a);
    cout << "\nformat to:" << parse_item(a) << endl;
}

void main_check()
{
    cout << main_containter.at(0).at(0) << endl;
    cout << main_containter.at(0).at(1) << endl;
    cout << main_containter.at(0).at(2) << endl;
}

void classes_add_values()
{
    cout << "\n\n\n\nDATY:\n\n";

    x_daty.add_values();
    x_daty.show_all_data();
    x_daty.html_table_data();

    cout << "\n\n\n\nLICZBY:\n\n";

    x_liczby.add_values();
    x_liczby.show_all_data();
    x_liczby.html_table_data();

    cout << "\n\n\n\nTEKSTY:\n\n";

    x_teksty.add_values();
    x_teksty.show_all_data();
    x_teksty.html_table_data();
    return;
}
