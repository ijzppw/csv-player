#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <climits>

#include "main_funkcje.h"

#include "typ_dane.h"

#include "typ_data.h"
#include "typ_liczba.h"
#include "typ_tekst.h"


using namespace std;

vector< vector<string> > main_containter;
DANE_data x_daty;
DANE_liczba x_liczby;
DANE_tekst x_teksty;

int main()
{

cout << "PROJEKT CSV  v1.0\n\n";
    char wybor = '1';
    menu1();

    while (wybor != 'e')
    {
        cin.clear();

        cin.ignore(INT_MAX, '\n');
        cout << "\nwybierz opcje: [\'0\'-menu, \'x\'-dodatkowe opcje[liczby], \'r\'-clear, \'c\'-clear & menu]: ";
        cin >> wybor;

            while ( !cin.good() || ((wybor <'0' || wybor >'6')) && wybor!='e' && wybor!='r'
                   && wybor!='x' && wybor!='c');
            {
                switch(wybor)
                {
                    case '1':
                    cout <<"\nwybrana opcja: 1 -  read_file(); "<<endl;
                    read_file();
                    cout << "\nok\n";
                    break;

                    case '2':
                    cout <<"\nwybrana opcja: 2 -  show_all(); "<<endl;
                    show_all();
                    cout << "\nok\n";
                    break;

                    case '3':
                    cout <<"\nwybrana opcja: 3 -  html_table(); "<<endl;
                    html_table();
                    cout << "\n html_table()  - dane w pliku table.html\n";
                    cout << "\nok\n";
                    break;

                    case '4':
                    cout <<"\nwybrana opcja: 4 -  parse_item(string a); "<<endl;
                    format_dane();
                    cout << "\nok\n";
                    break;


                    case '6':
                    cout <<"\nwybrana opcja: 6 -  main_check(); "<<endl;
                    main_check();
                    cout << "\nok\n";
                    break;



                    case 'e':
                    cout << "\n\nprogram zakonczony pomyslnie" << "\n\n";
                    return 0;
                    break;

                    case 'r':
                    system("clear");
                    cout << "nacisnij enter";
                    break;

                    case 'x':
                    cout <<"\nwybrana opcja: x - dodatkowe opcje - liczby"<<endl;
                    dodatkowe_opcje();
                    break;

                    case 'c':
                    cout <<"\nwybrana opcja: c - clear&menu"<<endl;
                    system("clear");
                    menu1();
                    break;

                    case '0':
                    menu1();
                    break;
                }
            }
    }
    if (wybor == 'e')
    {
        cout << "\n\nprogram zakonczony pomyslnie" << "\n\n";
        return 0;
    }
return 0;
}

