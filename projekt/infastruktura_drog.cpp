#include <iostream>
#include <vector>
#include "funkcje.h"
#include "struktury.h"

using namespace std;

int main(int arg, char *argv[]) {
    string nazwa_pliku_wejsciowego;
    string nazwa_pliku_wyjsciowego;

    cout << "|| PROGRAM, KTORY WYZNACZA NAJTANSZE MOZLIWE POLACZENIA MIAST SIECIA DROGOWA ||" << endl << endl;
    


    czytanie_z_wiersza_polecen(arg, argv, nazwa_pliku_wejsciowego, nazwa_pliku_wyjsciowego);

    vector<wezel *> lista_miast = zczytaj_z_pliku(nazwa_pliku_wejsciowego);

    for (auto &miasto : lista_miast) 
    {
        algorytm(lista_miast, miasto);
    }

    zwroc_do_pliku(lista_miast, nazwa_pliku_wyjsciowego);

    // Czyszczenie pamieci
    for (auto &wezel : lista_miast)
    {
        delete wezel;
    }

    return 0;
}