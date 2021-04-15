#include "cli.h"
#include <iostream>

using namespace std;


void separator(){
    cout << "\033[38;2;205;49;49m-\033[0m\033[38;2;202;52;52m-\033[0m"
            "\033[38;2;199;55;55m-\033[0m\033[38;2;196;58;58m-\033[0m"
            "\033[38;2;193;61;61m-\033[0m\033[38;2;190;64;64m-\033[0m"
            "\033[38;2;187;67;67m-\033[0m\033[38;2;184;70;70m-\033[0m"
            "\033[38;2;181;73;73m-\033[0m\033[38;2;178;76;76m-\033[0m"
            "\033[38;2;175;79;79m-\033[0m\033[38;2;172;82;82m-\033[0m"
            "\033[38;2;169;85;85m-\033[0m\033[38;2;166;88;88m-\033[0m"
            "\033[38;2;163;91;91m-\033[0m\033[38;2;160;94;94m-\033[0m"
            "\033[38;2;157;97;97m-\033[0m\033[38;2;154;100;100m-\033[0m"
            "\033[38;2;151;103;103m-\033[0m\033[38;2;148;106;106m-\033[0m"
            "\033[38;2;145;109;109m-\033[0m\033[38;2;142;112;112m-\033[0m"
            "\033[38;2;139;115;115m-\033[0m\033[38;2;136;118;118m-\033[0m"
            "\033[38;2;133;121;121m-\033[0m\033[38;2;130;124;124m-\033[0m"
            "\033[38;2;127;127;127m-\033[0m\033[38;2;124;130;130m-\033[0m"
            "\033[38;2;121;133;133m-\033[0m\033[38;2;118;136;136m-\033[0m"
            "\033[38;2;115;139;139m-\033[0m\033[38;2;112;142;142m-\033[0m"
            "\033[38;2;109;145;145m-\033[0m\033[38;2;106;148;148m-\033[0m"
            "\033[38;2;103;151;151m-\033[0m\033[38;2;100;154;154m-\033[0m"
            "\033[38;2;97;157;157m-\033[0m\033[38;2;94;160;160m-\033[0m"
            "\033[38;2;91;163;163m-\033[0m\033[38;2;88;166;166m-\033[0m"
            "\033[38;2;85;169;169m-\033[0m\033[38;2;82;172;172m-\033[0m"
            "\033[38;2;79;175;175m-\033[0m\033[38;2;76;178;178m-\033[0m"
            "\033[38;2;73;181;181m-\033[0m\033[38;2;70;184;184m-\033[0m"
            "\033[38;2;67;187;187m-\033[0m\033[38;2;64;190;190m-\033[0m"
            "\033[38;2;61;193;193m-\033[0m\033[38;2;58;196;196m-\033[0m"
            "\033[38;2;55;199;199m-\033[0m\033[38;2;52;202;202m-\033[0m"
            "\033[38;2;49;205;205m-\033[0m\n";
}

int numeric_choice(int upper_bound){
    int choice;
    string choice_s;
    bool is_number, is_in_bounds;
    do{
        is_in_bounds = 1;
        cin >> choice_s;
        do{
            is_number = 1;
            try{
                choice = stoi(choice_s);
            }
            catch(invalid_argument){
                cout << "Musisz podać liczbę całkowitą z zakresu 1 - ";
                cout << upper_bound << "." << endl;
                is_number = 0;
                cin >> choice_s;
            }
        } while(!is_number);
        if(choice > 0 && choice <= upper_bound){
            return choice;
        } else{
            cout << "Liczba całkowita musi być z zakresu 1 - ";
            cout << upper_bound << "." << endl;
            is_in_bounds = 0;
        }
    } while(!is_in_bounds);
}

void menu(int sector){
    switch(sector){
        case 1:
            cout << "                \033[1;3;31mTest Kasy Fiskalnej\033[0m" << endl;
            break;
        case 2:
            cout << "Wybierz z listy, co chcesz zrobić:" << endl;
            cout << "   \033[1;3;31m1.\033[0m  Sprawdź, czy kasy fiskalne są takie same" << endl;
            cout << "   \033[1;3;31m2.\033[0m  Sprawdź ludzi w kolejce" << endl;
            cout << "   \033[1;3;31m3.\033[0m  Zamień ludzi w kolejce" << endl;
            cout << "   \033[1;3;31m4.\033[0m  Sprawdź Id kasy fiskalnej" << endl;
            cout << "   \033[1;3;31m5.\033[0m  Zmień Id kasy fiskalnej" << endl;
            cout << "   \033[1;3;31m6.\033[0m  Sprawdź lokalizację kasy fiskalnej" << endl;
            cout << "   \033[1;3;31m7.\033[0m  Zmień lokalizację kasy fiskalnej" << endl;
            cout << "   \033[1;3;31m8.\033[0m  Sprawdź, kto obsługuje kasę" << endl;
            cout << "   \033[1;3;31m9.\033[0m  Zmień pracownika obsługującego kasę" << endl;
            cout << "   \033[1;3;31m10.\033[0m Sprawdź rachunek" << endl;
            cout << "   \033[1;3;31m11.\033[0m Zmień rachunek" << endl;
            cout << "   \033[1;3;31m12.\033[0m Otwórz kasę" << endl;
            cout << "   \033[1;3;31m13.\033[0m Zamknij kasę" << endl;
            cout << "   \033[1;3;31m14.\033[0m Zamknij program" << endl;
            break;
        case 3:
            cout << "                     \033[1;3;31mGoodbye!\033[0m" << endl;
            break;
    }
}
