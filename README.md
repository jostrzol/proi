# PROI projekt: Sklep z artykułami budowlanymi

---
Dokumentacja znajduje się w pliku [Documentation.pdf](reference/Documentation.pdf)
Poniżej znajduje się diagram UML przedstawiający wszystkie klasy należące do biblioteki statycznej:
# ![UML_diagram](reference/Class_UML.png?raw=true)
---

##### Termin wykonania: 27.05.2021 12:15
###### Instrukcje
Proszę zasymulować działanie sklepu z artykułami budowlanymi, przyjmując następujące założenia:

1. W sklepie z artykułami budowlanymi znajduje się **m** kas, do których klienci mogą ustawiać się w kolejce. Czasem niektóre kasy są nieczynne. Kasę obsługuje jeden z **n** pracowników.

2. Klient może wejść lub wyjść ze sklepu, wybierać towary do kupienia, zadawać pytania pracownikom sklepu lub sprawdzać cenę towaru.

3. Towary sprzedawane w sklepie z artykułami budowlanymi dzieli się na kategorie wg rodzaju artykułu budowlanego.

4. Sklep z artykułami budowlanymi może wystawić potwierdzenie zapłaty w formie paragonu lub w formie faktury VAT.

##### PROI 21L - ogólne wymagania dotyczące projektów
1. Projekt powinien być realizowany systematycznie i zespołowo, co oznacza, że na Gitlabie powinny pojawiać się regularne commity (przynajmniej raz w tygodniu) oraz że powinny one być dodawane przez wszystkich członków zespołu, zgodnie z faktycznym podziałem obowiązków w grupie. Proszę wykorzystać możliwości Gita do pracy grupowej. W razie potrzeby skorzystania z dodatkowych informacji  na  temat  używania  Gita,  najlepiej  zasięgnąć  wiedzy  u  źródła,  tzn.  w oficjalnym podręczniku do Gita (https://git-scm.com/book/en/v2). Dobrym punktem startowym do realizacji projektu będą rozwiązania zadania nr 3.

2. Projekt polega na przeprowadzeniu symulacji działania danej organizacji (instytucji) w czasie. Upływ czasu może być modelowany poprzez zastosowanie pętli, której każdy obrót stanowi umowną jednostkę czasu.

3. Projekty są sformułowane w sposób ogólny, a podane założenia stanowią jedynie podstawowy schemat działania organizacji. Jedną z części zadania jest uszczegółowienie sposobu działania organizacji. Zalecane jest skonsultowanie przyjętych założeń przed oddaniem projektu. Możliwa jest też ewentualna modyfikacja założeń  sformułowanych w treści zadania po uzgodnieniu z prowadzącą.

4. Każdy  obiekt  wykorzystywany  w  symulacji  powinien  posiadać  identyfikator  umożliwiający rozróżnianie obiektów tego samego typu.
5. W  tym  projekcie  istotne  jest  wykorzystanie  różnorodnych  elementów  języka  C++,  dlatego w przypadku każdego z zadań należy:
    - zaprojektować hierarchię klas odpowiadającą treści zadania i przyjętym szczegółowym założeniom (wykorzystanie mechanizmów **dziedziczenia i polimorfizmu**, w tym funkcji wirtualnych);
    - zdefiniować **interfejsy** głównych klas z treści zadania (tych, które nie mają nadklas) poprzez utworzenie dla nich abstrakcyjnych klas bazowych z publicznymi metodami (wszystkie powinny być metodami czysto wirtualnymi);

    Interfejs jest rodzajem umowy między dostawcą klasy a jej użytkownikiem, która określa, jakie funkcje  klasa  będzie  realizować,  ale  nie  definiuje,  w  jaki  sposób  zostaną  one zaimplementowane. Oznacza to, że w interfejsie należy uwzględnić tylko elementy dostępne publicznie (metody) i tylko takie, które realizują pełne operacje – nie ma potrzeby uwzględniać metod pomocniczych. Interfejs powinien także zawierać destruktor czysto wirtualny.

    - wykorzystać **kolekcje z biblioteki STL** (wektory, listy, kolejki, zbiory itp);
    - wyświetlać  przebieg  symulacji  w  konsoli,  a  jednocześnie **zapisywać  go  do  pliku**. Wyświetlanie w konsoli powinno następować w takim tempie, by użytkownik zdążył przeczytać  wypisywany  komunikat.  W  komunikatach  należy  umieścić  identyfikatory obiektów biorących udział w danej akcji (np. „Klient nr 20 kupuje książkę nr 34 od pracownika nr 7”);
    - **wczytywać** parametry programu **z pliku oraz z argumentów wywołania programu** (ale żadnego parametru nie należy wczytywać w procesie interakcji z użytkownikiem);
    - zastanowić  się  nad  możliwymi przypadkami,  w  których  program  nie  będzie  działał poprawnie i zastosować do ich obsługi **mechanizm wyjątków**. Może to dotyczyć zarówno 
sposobu działania organizacji (jakaś sytuacja nie powinna się zdarzyć), jak i sposobu działania samego programu (np. nieudany odczyt/zapis do pliku).

**Uwaga**:  poprawne  wykorzystanie  wszystkich  ww.  mechanizmów  jest  ważniejsze  niż  stopień skomplikowania  symulacji.  Wymyślna  symulacja,  która  zawiera  tylko  szczątkowe  elementy wspomnianych konstrukcji, nie zrównoważy braku ich użycia.

6. Użytkownik powinien mieć możliwość ustawiania parametrów programu testującego, np. długości czasu symulacji (liczby iteracji), liczby obiektów danego typu biorących udział w symulacji (np. liczba obsługujących pracowników, liczba kas w sklepie).

7. W symulacji korzysta się z generatorów liczb pseudolosowych. Do generacji tych liczb proszę nie używać funkcji rand z biblioteki języka C, tylko **skorzystać z biblioteki \<random\>**. Generatory liczb pseudolosowych powinny być inicjowane innym ziarnem przy każdym uruchomieniu (uwaga na random_device, którego losowość zależy od implementacji!) – można wykorzystać do tego aktualny czas, najlepiej posługując się elementami biblioteki \<chrono\>. Przykład zastosowania elementów biblioteki \<chrono\> i \<random\> do generacji liczb pseudolosowych można znaleźć np.  pod  adresem http://www.cplusplus.com/reference/random/mersenne_twister_engine/operator()/.  Potrzebne  może  się  okazać  zastosowanie  generatora  liczb  pseudolosowych w połączeniu z określonym rozkładem, do czego również należy wykorzystać rozkłady dostępne w bibliotece \<random\>.

8. Do projektu należy dołączyć **dokumentację** projektową **w postaci pliku pdf**. Powinna ona zawierać:
    - imiona i nazwiska autorów oraz temat projektu (nie całą treść zadania);
    - opis wszystkich przyjętych założeń;
    - opis hierarchii klas oraz relacji pomiędzy nimi;
    - opis sposobu testowania programu (przeprowadzenia symulacji);
    - wskazanie wykorzystanych elementów biblioteki STL;
    - opis zidentyfikowanych sytuacji wyjątkowych i ich obsługi.

Dokumentacja powinna być krótka, ale przygotowana starannie – napisana **poprawnie w języku polskim**. Proszę pamiętać, że jakość dokumentacji również podlega ocenie.

9. Należy pamiętać o podziale programu na implementację klas i program testujący. Proszę też pamiętać o komentowaniu kodu. Kodu nie należy umieszczać w dokumentacji.

10. Ocena jest wystawiana po zapoznaniu się z dokumentacją i kodem źródłowym przez prowadzącą. 