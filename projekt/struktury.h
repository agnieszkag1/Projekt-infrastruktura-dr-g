#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <limits.h>

/// Struktora, która ilustuje miasto węzłowe (pojednyńcze miasto) i wszystkie możliwe połączenia z nim oraz ceny. 
/// 
/// Struktura przechowuje nazwę miasta węzłowego i wszystkie możliwe połączenia w postaci mapy (listy par) miast,
/// z którymi miasto węzłowe jest połączone oraz ceny tych połączeń). Struktura ta później jest wykorzystywana przy algorytmie. 



struct wezel {	
	std::string nazwa; /*!< Nazwa miasta węzłowego */
	std::map <wezel*, double> polaczenia; /*!< Mapa, która przechowuje listę par, w tym przypadku para to nazwa miasta, z którym miasto węzłowe jest połączone oraz cena połączenia tych miast */
	double cena_od_miasta_poczatkowego; /*!< Zmienna, która jest wykorzystywana przy algorytmie, jest to cena od miasta do węzła */
	bool odwiedzono = false; /*!< Zmienna, która służy do sprawdzenia czy dane miasto zostało już odwiedzone */
	std::pair<wezel*, double> najtansze_polaczenie_z_wezla; /*!< Zmienna, która przechowuje parę, która przechowuje najtańsze połączenie */
};


