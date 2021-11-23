#ifndef FUNKCJE_H
#define FUNKCJE_H

#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>
#include "funkcje.h"
#include "struktury.h"

using namespace std;

/// Funkcja, która zajmuje się zczytywaniem parametrów z wiersza poleceń.
/// 
/// Funkcja sprawdza poprawność podanych parametrów i zwraca prawdę (jeśli są poprawne) lub fałsz (jeśli są błędne) 
/// @param arg ilość argumentów przekazanych 
/// @param argv[] wskaźnik na tablicę parametrów 
/// @param nazwa_pliku_wejsciowego do funkcji przekazujemy nazwę pliku tekstowego (wejściowego), zmienna typu string
/// @param nazwa_pliku_wyjsciowego do funkcji przekazujemy nazwę pliku tekstowego (wyjściowego), zmienna typu string
/// @returns jeźli miasto już znajduje się na liście to zwraca nullptr, jeśli miasto jeszcze nie znajduje się na liście to zwraca jego nazwę
bool czytanie_z_wiersza_polecen(int arg, char *argv[], string &nazwa_pliku_wejsciowego, string &nazwa_pliku_wyjsciowego);

/// Funkcja służąca do sprawdzenia, czy zczytane z pliku miasto istnieje już na liście miast.
/// 
/// Jeżli miasto istnieje już na liście to funkcja zwraca pusty wskaźnik, jeśli miasto jeszcze nie istnieje na liście miast to dopisuje je do listy. 
/// @param nazwa_szukanego_miasta to zmienna typu string, która przechwuje nazwę miasta, które zczytaliśmy z pliku i przekazujemy do funkcji
/// @param miasta_wezlowe to zmienna typu vector<wezel*> (wektor wskaźników na węzeł), która zawiera listę miast węzłowych, które zostały już zczytane z pliku
/// @returns jeśli miasto już znajduje się na liście to zwraca jego nazwę, jeśli miasto jeszcze nie znajduje się na liście to zwraca nullptr
wezel * zwroc_miasto(string &nazwa_szukanego_miasta, vector<wezel *> &miasta_wezlowe);

/// Funkcja służąca do odczytania danych z pliku oraz umieszczenia ich w strukturze. Wykorzystuje funkcję zwroc_miasto.
/// 
/// Funkcja zczytuje dane z pliku za pomocą stringstream po linijce i sprawdza poprawność danych w danej linijce, 
/// jeśli dane są poprawne to sprawdza czy dane miasta istnieją już w strukturze, jeśli nie to dla danego miasta tworzy nowy węzeł
/// @param nazwa to zmienna typu string przechowująca nazwę pliku wejściowego wraz z jego rozszerzeniem
/// @returns zwraca zmienną typu vector<wezel*> (wektor węzłów), która przechowuje listę miast węzłowych i ich połączenia z innymi mistami.
vector<wezel *> zczytaj_z_pliku(string &nazwa);


/// Funkcja, która przygotowywuje dane, aby później można było wykorzystać je w algorytmie.
/// 
/// Funkcja ceny (cena_od_misata_początkowego) ustawia na nieskończoność i zmienia status odwiedzenia na false. Ustawia im wartość maksymalną dla double.
/// @param lista_miast zmienna typu vector<wezel*>, która zawiera listę miast
void przygotuj_dane(vector<wezel *> &lista_miast);

/// Funkcja służąca do szukania czy istnieje jakieś tańsze połączenie do węzła. Tańsze połączenia są zapamiętywane przez węzeł.
/// 
/// Funkcja sprawdza ceny połączeń z węzła i jeżli znalazł krótszą trase to wpisuje tą trase jako połączenie.
/// @param miasto zmienna typu wskaźnik na wezel, przechowuje nawę miasta
/// @param miasto_poczatkowe zmienna typu wskaźnik na wezel, przechowuje nawę miasta poczatkowego
void relaksacja_krawedzi(wezel *miasto, wezel *miasto_poczotkowe);

/// Funkcja, która sprawdza czy miasto zostało odwiedzone a następnie sprawdza najtańsze połącznia z nim.
/// 
/// Funkcja służąca do szukania najbliższego (najtańszego) miasta połączonego z węzłem lub najtańszego połącznia.  
/// @param obecny_wezel zmienna typu wskaźnik na wezel, miasto które obecnie sprawdzamy
/// @param lista_miast zmienna typu vector<wezel*>, która zawiera listę miast
/// @returns zwraca miasto, z którym połączenie jest najtańsze.
wezel *znajdz_najblizsze_miasto(wezel *obecny_wezel, vector<wezel *> &lista_miast);

/// Funkcja wykorzystująca algorytm Dijkstry.
/// 
/// Wykorzystuje funkcję przygotuj_dane(), relaksacja_krawedzi() oraz znajdz_najblizsze_miasto().
/// Algorytm działa, dla każego miasta i jak wykryje mniejszą cenę to zapisuje z jakeigo połączenia ona pochodzi.
/// @param lista_miast zmienna typu vector<wezel*>, która zawiera listę miast
/// @param miasto_poczatkowe zmienna typu wskaźnik na wezel
/// @returns zwraca miasto, z którym połączenie jest najtańsze.
void algorytm(vector<wezel *> &lista_miast, wezel *miasto_poczatkowe);

/// Funkcja, która zwraca dane do pliku wyściowego.
///   
/// @param lista_miast zmienna typu vector<wezel*>, która zawiera listę miast
/// @param nazwa_pliku_wyjsciowego zmienna typu string, która przechowuje nazwę pliku wyjściowego
void zwroc_do_pliku(vector<wezel *> &lista_miast, string &nazwa_pliku_wyjsciowego);


#endif
