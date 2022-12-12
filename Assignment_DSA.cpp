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
#include <string>
#include <regex>

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

void lockerImage(){
    int number = 1;

    for(int k=0;k<5;k++){ //do this for 5 row
        for(int j=1;j<=3;j++){ //create each column
            if(j%2==1){ // the frame
                for(int i=0;i<5;i++){
                cout<< setfill('-') << left << setw(6) << "|" <<"|";
                }
            }else{ // the inside with number labeling
                for(int i=0;i<5;i++){
                    if(number<10){
                        cout<< setfill(' ') << left << setw(3) << "|" << number++ <<right << setw(3) <<"|";
                    }else{
                        cout<< setfill(' ') << left << setw(2) << "|" << number++ <<right << setw(3) <<"|";
                    }
                }
            }
        cout <<endl;
        }
    }
}

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
        n->locker_id = s + i;
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

int pinGenerator(int min,int max){
    return min+rand()%max;
}

class PhoneValidator
{
private:
  regex phoneNumberRegex; // Regular expression for validating phone numbers

public:
  // Constructor
  PhoneValidator() : phoneNumberRegex("^\\+?60[\\d]{9,10}$") {}

  // Method to validate a phone number
  bool isValid(string phone)
  {
    return regex_match(phone, phoneNumberRegex);
  }
};


void depositParcel(Parcel** head){
    string id,phone;
    PhoneValidator validator;
    
    cout << "Insert Parcel ID : ";
    cin >> id;
    do{
        cin.ignore();
        cout << "Insert Phone Number (example : +6013456789): ";
        getline(cin, phone);
        if (validator.isValid(phone))
        {
            cout << "Valid Malaysian phone number" << endl;
            break;
        }
        else
        {
            cout << "Invalid Malaysian phone number" << endl;
        }
        cin.ignore();
    }while(true);
    
    

    Parcel* n = *head;

    while(n!=NULL){
        if(n->parcel_id==""){
            n->parcel_id = id;
            n->phone = phone;
            n->pin = pinGenerator(1000,8999);
            cout << "Parcel successfully deposit to locker "<< n->locker_id <<"!"<<endl;
            cout << "Locker pin : " << n->pin << endl;        
            break;
        }else{
            n = n->next;
        }
    }

    if(n==NULL){
        cout << "Locker full!";
    }
}


//!!PIN VALIDATION
void retrieveParcel(Parcel **head){
    string phone;
    Parcel* n = *head;
    int pin;

    cout << "Insert Phone Number (example : +6013456789): ";
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
         << "1. Phone Number" << endl
         << "2. Parcel ID" << endl
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
         << "1. Phone Number" << endl
         << "2. Parcel ID" << endl
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

void autoFill(Parcel** head){
    string id[5] = {"SPXMY000","SPE000","TSXMY000","POPMY000","HUIMY000,000000,PL000, MY0000, DHLMY000"};
    string phone = "+6018010";

    Parcel* n = *head;

    do{
        string new_id = id[pinGenerator(0,5)]+to_string(pinGenerator(1000,8999));
        string new_phone = phone+to_string(pinGenerator(1000,8999));
        //core part
        while(n!=NULL){
            if(n->parcel_id==""){
                n->parcel_id = new_id;
                n->phone = new_phone;
                n->pin = pinGenerator(1000,8999);
                break;
            }else{
                n = n->next;
            }
        }
        //end core
    }while(n!=NULL);

    if(n==NULL){
        cout << "\n!!!!!!!!!!Auto Fill Complete!!!!!!!!!!" << endl;
    }
}

int main()
{  
    Parcel *cendi_head = NULL,*cendi_tail = NULL;
    createLocker(&cendi_head,&cendi_tail,0);
    int input;
    srand(time(NULL));

    do{
        cout << endl;
        lockerImage();
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
            cout << "\n4. Update parcel information";
            cout << "\n9. Random Generate all Locker Information";
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
            case 4:
                updateParcel(&cendi_head);
                break;
            case 9:
                autoFill(&cendi_head);
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
