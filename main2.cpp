#include "cash_register.h"
#include "cli.h"
#include <iostream>
#include <vector>

using namespace std;

enum choices{
    CheckIfEqual = 1,
    CheckPeopleInQueue = 2,
    ChangePeopleInQueue = 3,
    CheckCashRegisterId = 4,
    ChangeCashRegisterId = 5,
    CheckCashRegisterLocation = 6,
    ChangeCashRegisterLocation = 7,
    CheckCashier = 8,
    ChangeCashier = 9,
    CheckBill = 10,
    ChangeBill = 11,
    OpenCashRegister = 12,
    CloseCashRegister = 13,
    ExitSignal = 14
};

enum menu_sector{
    MenuHeader = 1,
    MenuOptions = 2,
    MenuExit = 3
};

int main(){
	Product brick("cegła", 2, 0.23);
	Product hammer("młotek", 10, 0.08);
	vector<Product> bill1;
	bill1.push_back(brick);
	bill1.push_back(hammer);

	Product saw("piła", 15, 0.17);
	Product glue("klej", 8, 0.23);
	vector<Product> bill2;
	bill2.push_back(saw);
	bill2.push_back(glue);

	Person JanKowalski("Jan", "Kowalski", 70);
	Person ArturNowak("Artur", "Nowak", 71);
    Person MariaAntonina("Maria", "Antonina", 73);
    Person AdamSlowak("Adam", "Słowak", 6701);
    Person JuliuszMicki("Juliusz", "Micki", 6743);
    Person RobertCichy("Robert", "Cichy", 5421);
    Person WiktorSlynny("Wiktor", "Słynny", 5791);

	Queue queue1;
	queue1.push(AdamSlowak);
	queue1.push(JuliuszMicki);

	Queue queue2;
	queue2.push(RobertCichy);
	queue2.push(WiktorSlynny);

	Queue queue3;
	queue3 = queue1 + queue2;

	CashRegister cashregister1;
	cashregister1.change_id(6);
	cashregister1.change_location("Sektor A");
	cashregister1.change_cashier(JanKowalski);
	cashregister1.change_queue(queue1);
	cashregister1.change_bill(bill1);
	cashregister1.change_status(true);

	CashRegister cashregister2;
	cashregister2.change_id(7);
	cashregister2.change_location("Sektor B");
	cashregister2.change_cashier(ArturNowak);
	cashregister2.change_queue(queue2);
	cashregister2.change_bill(bill2);
	cashregister2.change_status(false);

    int choice;
    bool exit = false;
    separator();
    menu(MenuHeader);
    separator();
    while(!exit){
        menu(MenuOptions);
        choice = numeric_choice(14);
        separator();
        switch(choice){
            case CheckIfEqual:
                cout << "cashregister1 == cashregister2? ";
                cout << (cashregister1 == cashregister2) << endl;
                cout << "cashregister1 == cashregister1? ";
                cout << (cashregister1 == cashregister1) << endl;
                cout << "cashregister2 == cashregister2? ";
                cout << (cashregister2 == cashregister2) << endl;
                break;

            case CheckPeopleInQueue:
                cout << "queue1:\n" << queue1;
                separator();
                cout << "queue2:\n" << queue2;
                separator();
                cout << "queue3:\n" << queue3;
                break;

            case ChangePeopleInQueue:
                cout << "przed zamianą:\n" << queue3;
                queue3.switch_places(1, 3);
                cout << "po zamianie:\n" << queue3;
                break;

            case CheckCashRegisterId:
                cout << "cashregister1.id(): " << cashregister1.id();
                cout << endl;
                break;

            case ChangeCashRegisterId:
                cout << "cashregister1.id(): " << cashregister1.id();
                cout << endl;
                cashregister1.change_id(13);
                cout << "cashregister1.change_id(13)" << endl;
                cout << "cashregister1.id(): " << cashregister1.id();
                cout << endl;
                break;

            case CheckCashRegisterLocation:
                cout << "cashregister2.location(): " << cashregister2.location();
                cout << endl;
                break;

            case ChangeCashRegisterLocation:
                cout << "cashregister1.location(): " << cashregister1.location();
                cout << endl;
                cashregister1.change_location("Sektor C");
                cout << "cashregister1.change_location(\"Sektor C\")" << endl;
                cout << "cashregister1.location(): " << cashregister1.location();
                cout << endl;
                break;

            case CheckCashier:
                cout << "cashregister2.cashier(): " << cashregister2.cashier();
                cout << endl;
                break;

            case ChangeCashier:
                cout << "cashregister1.cashier(): " << cashregister1.cashier();
                cout << endl;
                cashregister1.change_cashier(MariaAntonina);
                cout << "cashregister1.change_cachier(MariaAntonina)" << endl;
                cout << "cashregister1.cashier(): " << cashregister1.cashier();
                cout << endl;
                break;

            case CheckBill:
                cout << "cashregister2.bill():\n";
                for(int i = 0; i < cashregister2.bill().size(); i++){
                    cout << cashregister2.bill().at(i);
                    if(i != (cashregister2.bill().size() - 1)){
                        cout << endl;
                    }
                }
                cout << endl;
                break;

            case ChangeBill:
                cout << "cashregister2.bill():\n";
                for(int i = 0; i < cashregister2.bill().size(); i++){
                    cout << cashregister2.bill().at(i);
                    if(i != (cashregister2.bill().size() - 1)){
                        cout << endl;
                    }
                }
                cout << endl;
                cashregister2.change_bill(bill1);
                cout << "cashregister2.change_bill(bill1)" << endl;
                cout << "cashregister2.bill():\n";
                for(int i = 0; i < cashregister2.bill().size(); i++){
                    cout << cashregister2.bill().at(i);
                    if(i != (cashregister2.bill().size() - 1)){
                        cout << endl;
                    }
                }
                cout << endl;
                break;

            case OpenCashRegister:
                cout << "cashregister2.status(): " << cashregister2.status();
                cashregister1.change_status(true);
                cout << endl;
                cout << "cashregister2.change_status(true)" << endl;
                cout << "cashregister2.status(): " << cashregister2.status();
                cout << endl;
                break;

            case CloseCashRegister:
                cout << "cashregister1.status(): " << cashregister1.status();
                cashregister1.change_status(false);
                cout << endl;
                cout << "cashregister1.change_status(false)" << endl;
                cout << "cashregister1.status(): " << cashregister1.status();
                cout << endl;
                break;

            case ExitSignal:
                menu(MenuExit);
                exit = true;
        }
        separator();
    }
	return 0;
}
