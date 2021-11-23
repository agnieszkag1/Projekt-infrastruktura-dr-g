#include "funkcje.h"
#include "struktury.h"
#include <limits.h>

using namespace std;

bool czytanie_z_wiersza_polecen(int arg, char *argv[], string &nazwa_pliku_wejsciowego, string &nazwa_pliku_wyjsciowego) {
    bool sprawdzenie_i = false;
    bool sprawdzenie_o = false;

    for (int i = 0; i < arg; i++) {
        if (argv[i][0] == '-') {
            switch (argv[i][1]) {
                case 'i': {
                    if (sprawdzenie_i == false) {

                        cout << "Nazwa Pliku: " << argv[i + 1] << endl;
                        nazwa_pliku_wejsciowego = argv[i + 1];
                        sprawdzenie_i = true;
                    }
                    break;
                }
                case 'o': {
                    if (sprawdzenie_o == false) {
                        nazwa_pliku_wyjsciowego = argv[i + 1];
                        sprawdzenie_o = true;
                    }

                    break;
                }

                default:
                    cout << "BŁĄD ODCZYTU" << endl;
                    return false;
                    break;
            }
            i++;
        }

    }

    return sprawdzenie_o && sprawdzenie_i;
}

wezel *zwroc_miasto(string &nazwa_szukanego_miasta, vector<wezel *> &miasta_wezlowe) {

    for (auto &miasto : miasta_wezlowe)
    {
        if (miasto->nazwa == nazwa_szukanego_miasta) {
            return miasto;
        }
    }
    return nullptr;
}

vector<wezel *> zczytaj_z_pliku(string &nazwa) {
    int puste_linijki = 0;
    int niepoprawne_linijki = 0;
    vector<wezel *> miasta_wezlowe;

    ifstream plik(nazwa); //sprawdzenie, czy plik istnieje i czy da się go otworzyć

    if (plik) {
        cout << "[KOMUNIKAT: PLIK ZOSTAL OTWARTY POPRAWNIE]" << endl << endl;

        string linijka_pliku;


        while (getline(plik, linijka_pliku)) // tak długo jak można pobrać linijkę z pliku
        {
            if (linijka_pliku.size() > 0) // sprawdza rozmiar linijki, jeżli jest większy niż zero to sprawdza dane
            {
                stringstream ss(linijka_pliku);

                //miasto1 miasto2 cena
                string miasto1, miasto2;
                double cena;

                if (ss >> miasto1 >> miasto2
                       >> cena) // sprawdza czy w pliku znajdują sie dwie dany typu string i jedna zmienna typu double
                {
                    bool czy_istnieje = false;
                    wezel *miasto_z_pliku = zwroc_miasto(miasto1, miasta_wezlowe); // definiujemy wskaźnik i przkazujemy do funkcji miasto1 i sprawdzamy czy już jest w wektorze miast, funkcja przypisuje do wskaźnika nullptr albo nazwę miasta
                    if (!miasto_z_pliku) // jeśli miato1 nie istnieje
                    {
                        miasto_z_pliku = new wezel; // tworzymy nowy węzeł
                        miasto_z_pliku->nazwa = miasto1; // przypisujemy mu nazwę pobraną z pliku
                        miasta_wezlowe.push_back(miasto_z_pliku); // dopisujemy miasto na koniec listy z miastami 
                    }

                    wezel *miasto_docelowe = zwroc_miasto(miasto2, miasta_wezlowe); // przkazujemy do funkcji miasto2 i sprawdzamy czy już jest w wektorze miast

                    if (!miasto_docelowe) // jeżli miasto2 nie istnieje
                    {
                        miasto_docelowe = new wezel; // tworzymy nowy węzeł
                        miasto_docelowe->nazwa = miasto2; // przypisujemy mu nazwę pobraną z pliku
                        miasta_wezlowe.push_back(miasto_docelowe); // dopisujemy miasto na koniec listy z miastami
                    }

                    miasto_z_pliku->polaczenia.insert(pair<wezel *, double>(miasto_docelowe, cena)); // przypisuje do miasta1 z pliku połączenie z miastem2 i cene, zawsze przypisuje parę: para miasto -> cena
                   
                } else
                    {
                    niepoprawne_linijki++;
                    }
            } else 
            
                {
                puste_linijki++;
                }
        }

        cout << "|| Liczba pustych linijek: " << puste_linijki << " || Liczba niepoprawnie sformatowanych linijek: "
             << niepoprawne_linijki << " ||" << endl << endl;

        plik.close();

  
    } else {
        cout << "Pliku nie da sie otworzyc, sprawdz poprawnosc wprowadzonych parametrow lub lokalizacje pliku wejsciowego" << endl<<endl;
        cout << "Instrukcja wprowadzania danych: " << endl << "-i (nazwa pliku wejściowego).txt" << endl << "-o (nazwa pliku wyjsciowego).txt" << endl << endl;             
    }

    return miasta_wezlowe;


}

void przygotuj_dane(vector<wezel *> &lista_miast) {
    for (int i = 0; i < lista_miast.size(); i++) {
        wezel *miasto = lista_miast.at(i); // z listy miast bierzemy jedno miasto

        miasto->odwiedzono = false;
        miasto->cena_od_miasta_poczatkowego = numeric_limits<double>::max(); // pobiera max wartość dla double i jako cene daje inf
    }
}

void relaksacja_krawedzi(wezel *miasto, wezel *miasto_poczotkowe) {
    for (auto &poloczenie: miasto->polaczenia) // dla każdego połączenia z węzła
    {
        double nowa_cena = miasto->cena_od_miasta_poczatkowego + poloczenie.second;

        if (miasto->cena_od_miasta_poczatkowego == numeric_limits<double>::max()) // przypadek kiedy graf jest rozlaczny
        {
            nowa_cena = numeric_limits<double>::max();
        }

        if (nowa_cena < poloczenie.first->cena_od_miasta_poczatkowego) {
            poloczenie.first->cena_od_miasta_poczatkowego = nowa_cena;
            auto para = std::pair<wezel *, double>(miasto, poloczenie.second);
            poloczenie.first->najtansze_polaczenie_z_wezla = para;
        }
    }
}

wezel *znajdz_najblizsze_miasto(wezel *obecny_wezel, vector<wezel *> &lista_miast) {
    wezel *najblzszy_wezel = nullptr;

    for (auto &polaczenie : obecny_wezel->polaczenia) // tak długo jak istnieja polaczenia dla danego węzła to je sprawdzaj
    {
        if (polaczenie.first->odwiedzono == false) {
            if (najblzszy_wezel) {
                if (polaczenie.first->cena_od_miasta_poczatkowego < najblzszy_wezel->cena_od_miasta_poczatkowego)
                    najblzszy_wezel = polaczenie.first;
            } else najblzszy_wezel = polaczenie.first;
        }
    }

    if (najblzszy_wezel) {
        return najblzszy_wezel;
    }

    // znalezienie najblizszego niepoloczonego z obecnym wezlem miasta

    for (auto &miasto : lista_miast) {
        if (miasto->odwiedzono == false) {
            if (najblzszy_wezel) {
                if (miasto->cena_od_miasta_poczatkowego < najblzszy_wezel->cena_od_miasta_poczatkowego)

                    najblzszy_wezel = miasto;

                else najblzszy_wezel = miasto;
            }
        }
    }

    return najblzszy_wezel;
}

void algorytm(vector<wezel *> &lista_miast, wezel *miasto_poczatkowe) {
    przygotuj_dane(lista_miast);
    miasto_poczatkowe->cena_od_miasta_poczatkowego = 0;

    relaksacja_krawedzi(miasto_poczatkowe, miasto_poczatkowe);
    miasto_poczatkowe->odwiedzono = true;

    wezel *obecne_miasto = znajdz_najblizsze_miasto(miasto_poczatkowe, lista_miast);

    while (obecne_miasto) {
        relaksacja_krawedzi(obecne_miasto, obecne_miasto);
        obecne_miasto->odwiedzono = true;
        obecne_miasto = znajdz_najblizsze_miasto(obecne_miasto, lista_miast);
    }
}

void zwroc_do_pliku(vector<wezel *> &lista_miast, string &nazwa_pliku_wyjsciowego) {
    ofstream plik(nazwa_pliku_wyjsciowego);
    if (plik) {
        for (auto &miasto : lista_miast) {
            auto poloczenie = miasto->najtansze_polaczenie_z_wezla;
            if (poloczenie.first != NULL)
                plik << miasto->nazwa << " " << poloczenie.first->nazwa << " " << poloczenie.second << endl;
        }
    }
}