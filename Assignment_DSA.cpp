/******************************************************************************
| Author 1 : Lee Xian Yang (SW01081013)                                        |
| Author 2 : Amirul Fikri bin Azman Zafri (CS01081173)                         |
| Author 3 : Vyner Nicholas Kayang (CS01081043)                                |
| Author 4 : Muhammad Ilham Bin Muhammad Redzuan Phua (SW01081025)             |
| Author 5 : Zulhilmi bin Zainuddin (SW01081669)                               |
| Author 6 : Muhammad Ikhwan Zarif Bin Mustaffa Kamal (SN01081024)             |
| Lang : C++                                                                   |
| Date Created : 7/12/2022                                                     |
*******************************************************************************/
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

using namespace std;
/*
    // - done
    ! - need help
    ? - question

    TITLE : POPBOX SYSTEM
   
    <0. SYSTEM>
    // : Create Linked List with 25 nodes
    // : Struct{Box Number(int), Parcel ID(string), Phone Number(string), PIN number(int), Next(*pointer)}
    // : Random Number Generator for PIN 

    <1. DEPOSIT PARCEL>
    // : When add parcel, system check from 1 until 25. If empty, fill that node. If reach NULL, terminate insertion.
    // : Get input -> Parcel ID, Phone Number
    TODO : If add parcel success, "notify" the owner of parcel

    <2.RETRIEVE PARCEL>
    // : When retrieve parcel, choose the box number
    // : Insert PIN Number (if wrong pin, reenter, max attempt 3 times, terminate)
    // : After retrive, clear the data of that node

    <3. DEBUG MODE>
    // : See all the box content
    // : Pick between show all box include empty box AND only non-empty box
*/
struct Parcel{
    int locker_id;
    string parcel_id;
    string phone;
    int pin;
    Parcel *next;
    Parcel *prev;
};

void header(){
    cout<< setfill('-') << left << setw(34) << "|" <<"|" <<endl;
    cout << setfill(' ') << setw(34) << "| UNITEN PARCEL MAILBOX SYSTEM" << "|"<< endl;
    cout<< setfill('-') << left << setw(34) << "|" <<"|" <<endl;
    for(int i=0;i<6;i++){
        switch(i){
            case 1:
                cout<< setfill(' ') << left << setw(34) << "| 1. Deposit Parcel" << "|"<<endl;
                break;
            case 2:
                cout<< setfill(' ') << left << setw(34) << "| 2. Retrieve Parcel" << "|"<<endl;
                break;
            case 3:
                cout<< setfill(' ') << left << setw(34) << "| 3. Debug" << "|"<<endl;
                break;
            case 4:
                cout<< setfill(' ') << left << setw(34) << "| 0. Exit" << "|"<<endl;
                break;
            default:
                    cout<< setfill(' ') << left << setw(34) << "|" <<"|" <<endl;
                    break;
        }
    }
    cout<< setfill('-') << left << setw(34) << "|" <<"|" <<endl;
}

void createLocker(Parcel **head,Parcel **tail, int s){
    for(int i =1;i<=25;i++){
        Parcel* n = new Parcel;
        n->locker_id = s+i;
        n->parcel_id = "";
        n->phone = "";
        n->pin = 0;
        n->next = NULL;
        n->prev = NULL;

        if(*head==NULL){
            *head = *tail = n;
        }else{
            (*tail)->next = n;
            n->prev = *tail;
            *tail = n;
        }
    }
}

int pinGenerator(){
    srand((unsigned) time(NULL));
    return 1000+rand()%8999;
}

void depositParcel(Parcel** head){
    string id,phone;
    

    cout << "Insert Parcel ID : ";
    cin >> id;
    cout << "Insert Phone Number (example : 012-3456789): ";
    cin >> phone;

    Parcel* n = *head;

    while(n!=NULL){
        if(n->parcel_id==""){
            n->parcel_id = id;
            n->phone = phone;
            n->pin = pinGenerator();
            cout << "Parcel successfully deposit to locker "<< n->locker_id <<"!"<<endl;
            break;
        }else{
            n = n->next;
        }
    }

    if(n==NULL){
        cout << "Locker full!";
    }
}

void retrieveParcel(Parcel **head){
    string phone;
    Parcel* n = *head;
    int pin;

    cout << "Enter Phone Number (example : 012-3456789): ";
    cin >> phone;

    while(n!=NULL){
        if(n->phone==phone){
                cout << "Enter the pin for locker "<< n->locker_id <<" : ";
                cin >> pin;
                if(pin != n->pin){
                    cout << "Wrong pin!" << endl;
                }else{
                    cout << "Pin correct! Please remove the parcel from the locker." << endl;
                    n->parcel_id = "";
                    n->phone = "";
                    n->pin = 0;
                }
                break;
            }else{
                n = n->next;
            }
    }

    if(n==NULL){
        cout << "Phone number doesn't exist!" << endl;
    }
}

void displaySingleLocker(Parcel *n){
    cout
    << "Locker id : "<< n->locker_id << endl
    << "Parcel id : "<< n->parcel_id << endl
    << "Phone : "<< n->phone << endl
    << "Pin : "<< n->pin << endl
    << "====================" << endl;
}

void displayAllLocker(Parcel* n){
    cout << "==========LOCKER==========" << endl;
    while(n!=NULL){
        displaySingleLocker(n);
        n=n->next;
    }
    cout << "\n=====END OF LOCKER=====" << endl;
}

void displayAllLockerEx(Parcel* n){
    cout << "==========LOCKER_EX==========" <<endl;
    while(n!=NULL){
        if(n->parcel_id==""){
            n = n->next;
        }else{
            displaySingleLocker(n);
            n=n->next;
        }
    }
    cout << "\n=====END OF LOCKER=====" << endl;
}

void find_parcel(Parcel* n){
    int input;
    string string_input;

    cout << "\nFind parcel using?" << endl
         << "\n1. Phone Number" << endl
         << "\n2. Parcel ID" << endl
         << "\nYour input: ";
    cin >> input;

    switch (input)
    {
    case 1:
        cout << "\nInsert Phone Number (example : 012-3456789) : ";
        cin >> string_input; 

        while(n!=NULL){
            if(n->phone!=string_input){
                n = n->next;
            }else{
                displaySingleLocker(n);
                break;
            }
        }

        if(n==NULL){
            cout << "No phone number matched!" << endl;
        }
        break;
    case 2:
        cout << "\nInsert Parcel ID : ";
        cin >> string_input; 

        while(n!=NULL){
            if(n->parcel_id!=string_input){
                n = n->next;
            }else{
                displaySingleLocker(n);
                break;
            }
        }

        if(n==NULL){
            cout << "No Parcel ID matched!" << endl;
        }

        break;
    default:
        break;
    }

}

void updateParcel(Parcel** head){
    int input;
    string string_input;
    Parcel* n = *head;

    cout << "\nMethod to find parcel" << endl
         << "1. Phone Number"
         << "2. Parcel ID"
         << "Your input: ";
    cin >> input;

    switch (input)
    {
    case 1:
        cout << "\nInsert Phone Number (example,012-3456789): ";
        cin >> string_input;

        while(n!=NULL){
            if(n->phone!=string_input){
                n = n->next;
            }else{
                displaySingleLocker(n);

                cout << "\nWhat to edit" << endl
                     << "1. Phone Number"
                     << "2. Parcel ID"
                     << "Your input: ";
                cin >> input;

                switch(input)
                {
                case 1:
                    cout << "\nInsert New Phone Number (example : 012-3456789): ";
                    cin >> string_input;
                    n->phone = string_input;
                    cout << "\nPhone Number updated!";
                    break;
                case 2:
                    cout << "\nInsert New Parcel ID: ";
                    cin >> string_input;
                    n->parcel_id = string_input;
                    cout << "\nParcel ID updated!";
                    break;
                default:
                    break;
                }

            }
        }

        if(n==NULL){
            cout << "No phone number matched!" << endl;
        }
        break;

    case 2:
        cout << "\nInsert Parcel ID : ";
        cin >> string_input;

        while(n!=NULL){
            if(n->parcel_id!=string_input){
                n = n->next;
            }else{
                displaySingleLocker(n);
                cout << "\nWhat to edit" << endl
                     << "1. Phone Number"
                     << "2. Parcel ID"
                     << "Your input: ";
                cin >> input;

                 switch(input)
                {
                case 1:
                    cout << "\nInsert New Phone Number (example : 012-3456789): ";
                    cin >> string_input;
                    n->phone = string_input;
                    cout << "\nPhone Number updated!";
                    break;
                case 2:
                    cout << "\nInsert New Parcel ID: ";
                    cin >> string_input;
                    n->parcel_id = string_input;
                    cout << "\nParcel ID updated!";
                    break;
                default:
                    break;
                }
            }
        }

        if(n==NULL){
            cout << "No Parcel ID matched!" << endl;
        }

        break;

    default:
        break;
    }
}

int main()
{  
    Parcel *cendi_head = NULL,*cendi_tail = NULL;
    createLocker(&cendi_head,&cendi_tail,10000);
    int input;

    do{
        cout << endl;
        header();
        cout << endl;
        cout << "Your input: ";
        cin >> input;

        switch(input){
        case 1:
            depositParcel(&cendi_head);
            cout <<endl << endl;
            break;
        case 2:
            retrieveParcel(&cendi_head);
            cout <<endl << endl;
            break;
        case 3:
            cout << "\nDebug Mode :";
            cout << "\n1. Show all locker";
            cout << "\n2. Show all locker (excluding empty)";
            cout << "\n3. Find parcel";
            cout << "\nYour input: ";
            cin >> input;

            switch(input){
            case 1:
                displayAllLocker(cendi_head);
                break;
            case 2:
                displayAllLockerEx(cendi_head);
                break;
            case 3:
                find_parcel(cendi_head);
                break;
            default:
                cout << "Wrong number" << endl << endl;
                break;
            }
            break;
        case 0:
            break;
        default:
            cout << "Wrong number" << endl << endl;
            break;
        }
    }while(input!=0);


    return 0;
}