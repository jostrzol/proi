#include <iostream>
#include <fstream>
#include <sstream>

#include "object_generator.h"
#include "simulation.h"

using namespace std;

void generateNames(string fname);
void generateAddresses(string fname);
void generateItems(string fname);

int main(int argc, char *argv[])
{
    const int nArgs = 3;

    if (argc != nArgs)
    {
        cout << "Expected " << nArgs - 1 << " arguments, not " << argc - 1 << "\n";
        cout << "Usage:\t" << argv[0] << " nCashRegisters nCashWorkers\n";
        return -1;
    }

    unsigned int nCashRegisters;
    unsigned int nWorkers;
    try
    {
        nCashRegisters = stoi(argv[1]);
        nWorkers = stoi(argv[2]);
    }
    catch (invalid_argument &)
    {
        cout << "All arguments are expected to be unsigned integers\n";
        return -1;
    }

    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    mt19937 gen(seed);

    Shop shop(0, "DIY Shop");

    ObjectGenerator og(gen, shop);

    string fname = "names.txt";
    auto f = ifstream(fname);
    if (f.fail())
    {
        f.close();
        generateNames(fname);
        f.open(fname);
    }
    og.ReadNames(f);
    f.close();

    fname = "addresses.txt";
    f.open(fname);
    if (f.fail())
    {
        f.close();
        generateAddresses(fname);
        f.open(fname);
    }
    og.ReadAddresses(f);
    f.close();

    fname = "items.csv";
    f.open(fname);
    if (f.fail())
    {
        f.close();
        generateItems(fname);
        f.open(fname);
    }
    try
    {
        og.ReadItems(f);
    }
    catch (ErrorCSV &e)
    {
        f.close();
        cout << "Error reading items.csv: " << e.what() << "\n";
        return -1;
    }
    f.close();

    og.GenerateShopInfo();
    Person manager = og.GeneratePerson();
    shop.SetManager(&manager);

    og.AddCashRegisters(nCashRegisters);
    og.AddWorkers(nWorkers);
    size_t nCustomers = max<size_t>(og.RemainingRandomPeople(), nWorkers);
    og.AddCustomers(nCustomers);

    shop.SetCloseTime(chrono::hours(15));

    Simulation sim(gen, shop);

    auto logfile = ofstream("log.txt");
    sim.SetLogfile(&logfile);

    int nTurns = 0;
    string line;
    stringstream ss;
    cout << "Generated the following shop:\n\n";
    cout << shop.Details();
    cout << "\nHow many turns to simulate?\n> ";
    while (nTurns <= 0)
    {
        getline(cin, line);
        ss = stringstream(line);
        ss >> nTurns;
        if (!ss || nTurns <= 0)
            cout << "Incorrect value!\n> ";
    }

    logfile << "Generated the following shop:\n\n";
    logfile << shop.Details();
    logfile << "\nTurns to simulate: " << nTurns << ".\n";

    sim.Run(nTurns);

    logfile.close();

    return 0;
}

void generateNames(string fname)
{
    auto f = ofstream(fname);
    f << R"RAW(Maurycy Wojciechowski
Dominika Pietrzak
Przemysław Pietrzak
Olimpia Błaszczyk
Julian Kwiatkowski
Izabela Szymańska
Henryk Kołodziej
Urszula Michalak
Jarosław Krajewska
Milena Nowak
Dominik Kwiatkowski
Sylwia Woźniak
Aleksander Szewczyk
Natasza Zawadzka
Konrad Baran
Bogusława Witkowska
Borys Czerwiński
Ida Kucharska
Mieszko Czerwiński
Marysia Woźniak
Marcel Wiśniewski
Teresa Tomaszewska
Ryszard Tomaszewski
Magdalena Sobczak
Gniewomir Duda
Urszula Sikorska
Karol Stępień
Asia Kowalska
Ernest Szymański
Oksana Makowska
Kryspin Malinowski
Aleksander Borkowski
Aleks Zawadzki
Gniewomir Makowski
Bogumił Kaczmarczyk
Artur Laskowska
Maksymilian Dąbrowski
Eryk Kamiński
Alfred Baran
Marian Kowalczyk
Filip Lewandowski
Lucjan Kwiatkowski
Dorian Włodarczyk
Aleks Baranowski
Denis Witkowski
Jakub Cieślak
Dariusz Woźniak
Magda Krupa
Wiktoria Pawlak
Marcelina Wróblewska
Blanka Brzezińska
Alicja Chmielewska
Anna Zakrzewska
Anastazja Stępień
Iga Lewandowska
Oktawia Szymańska
Dorota Kołodziej
Monika Andrzejewska
Konstancja Walczak
Julita Walczak
Zuzanna Ostrowska
Kaja Mazur
Alisa Kołodziej
Aniela Jasińska)RAW";
    f.close();
}

void generateAddresses(string fname)
{
    auto f = ofstream(fname);
    f << R"RAW(ul. Krótka 30, Warszawa
ul. Szeroka 126, Zielona Góra
ul. Piękna 67, Katowice
al. Jana Pawła II 110, Łódź
ul. Długa 132, Zielona Góra
ul. Wąska 162, Wrocław
ul. Polna 178, Katowice
ul. Leśna 132, Warszawa
ul. Słoneczna 72, Zielona Góra
ul. Krótka 84, Lublin
ul. Szkolna 139, Katowice
ul. Ogrodowa 112, Lublin
ul. Lipowa 29, Warszawa
ul. Łąkowa 1, Wrocław
ul. Brzozowa 83, Katowice
ul. Kwiatowa 5, Wrocław
ul. Kościelna 29, Lublin
ul. Sosnowa 51, Warszawa
ul. Zielona 188, Wrocław
ul. Parkowa 165, Lublin
ul. Akacjowa 36, Wrocław
ul. Kolejowa 125, Warszawa
ul. Martuszewskiego Edwarda 44, Olsztyn
ul. Dziesięciny 81, Białystok
ul. Księdza Bończyka Norberta 18, Mysłowice
ul. Oleandrów 84, Warszawa
ul. Barona Henryka 108, Częstochowa
ul. Podleska 27, Kraków
ul. Romantyczna 114, Szczecin
ul. Kmieca 119, Kraków
ul. Szeligowskiego Tadeusza 105, Lublin
ul. Świdnicka 62, Wrocław
ul. Sielawy 113, Katowice
ul. Wróblewskiego Zygmunta 95, Zielona Góra
ul. Kaczmarczyka Alojzego 49, Kraków
ul. Strażacka 141, Łódź
ul. Chłapowskiego Dezyderego Adama 47, Warszawa
ul. Fasolowa 70, Warszawa
ul. Puszczykowa 74, Szczecin
ul. Smolna 69, Katowice
Al. Paderewskiego Ignacego 111, Wrocław
ul. Śniadeckich 12, Poznań
ul. Generała Ziętka Jerzego 54, Mysłowice
ul. Czeczota Jana 139, Warszawa
ul. Piłsudskiego 115, Sosnowiec
ul. Micińskiego Tadeusza 148, Kraków
ul. Chłodna 85, Bytom
ul. Plebańska 136, Będzin
ul. Al. Lisieckiego Kazimierza "Dziadka" 45, Warszawa
ul. Adama 149, Katowice
ul. Łysogórska 97, Warszawa
ul. Kolorowa 108, Rzeszów
ul. Dolna 45, Białystok
ul. Milenijna 50, Lublin
ul. Wadowicka 14, Szczecin
ul. Czerskiego Michała 107, Bydgoszcz
ul. Tama Pomorzańska 38, Szczecin
ul. Studzienna 73, Warszawa
ul. Grażyny 20, Łódź
ul. Laszki Bolesława 118, Olsztyn
ul. Skłodowskiej Curie Marii 7, Białystok
ul. Ciesielska 65, Radom
ul. Warmińska 132, Olsztyn
ul. Olszewskiego Przemysława 74, Olsztyn)RAW";
    f.close();
}

void generateItems(string fname)
{
    auto f = ofstream(fname);
    f << R"RAW(ItemID,ItemName,ItemCategory,ItemUnit,ItemUnitPrice,ItemUnitTax,ItemAmount
0,door,home,pcs.,123.00,0.23,200
1,sink,plumbing,pcs.,259.99,0.23,200
2,bricks,construction,kg,2.50,0.23,200
3,window,home,pcs.,111.50,0.23,200
4,oil,misc,l,5.50,0.23,200)RAW";
    f.close();
}