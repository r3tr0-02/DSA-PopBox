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
#include <iomanip>

using namespace std;
/*
    // - done
    ! - need help
    ? - question

    TITLE : POPBOX SYSTEM
   
    <0. SYSTEM>
    TODO : Create Linked List with 25 nodes
    TODO : Struct{Box Number(int), Parcel ID(string), Phone Number(string), PIN number(int), Next(*pointer)}
    TODO : Random Number Generator for PIN 

    <1. DEPOSIT PARCEL>
    TODO : When add parcel, system check from 1 until 25. If empty, fill that node. If reach NULL, terminate insertion.
    TODO : Get input -> Parcel ID, Phone Number
    TODO : If add parcel success, "notify" the owner of parcel

    <2.RETRIEVE PARCEL>
    TODO : When retrieve parcel, choose the box number
    TODO : Insert PIN Number (if wrong pin, reenter, max attempt 3 times, terminate)
    TODO : After retrive, clear the data of that node

    <3. DEBUG MODE>
    TODO : See all the box content
    TODO : Pick between show all box include empty box AND only non-empty box
*/
struct Parcel{
    int locker_id;
    string parcel_id;
    string phone;
    int pin;
    Parcel *next;
};

void header(){
    cout<< setfill('-') << left << setw(34) << "|" <<"|" <<endl;
    cout << setfill(' ') << setw(34) << "| UNITEN PARCEL MAILBOX SYSTEM" << "|"<< endl;
    cout<< setfill('-') << left << setw(34) << "|" <<"|" <<endl;
    for(int i=0;i<5;i++){
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
        n->pin = NULL;
        n->next = NULL;

        if(*head==NULL){
            *head = *tail = n;
        }else{
            (*tail)->next = n;
            *tail = n;
        }
    }
}

void depositParcel(Parcel** head){
    string id,phone;
    srand((unsigned) time(NULL));

    cout << "Insert Parcel ID : ";
    cin >> id;
    cout << "Insert Phone Number : ";
    cin >> phone;

    Parcel* n = *head;

    //do{
        //random_ping = rand()%9999;
        //string ran_id = id+to_string(ran);
        //string ran_phone = phone+to_string(ran);
        //core part
        while(n!=NULL){
            if(n->parcel_id==""){
                n->parcel_id = id;
                n->phone = phone;
                n->pin = rand()%9999;
                cout << "Parcel successfully deposit to locker "<< n->locker_id <<" !"<<endl;
                break;
            }else{
                n = n->next;
            }
        }
        //end core
    //}while(n!=NULL);

    if(n==NULL){
        cout << "Locker full!";
    }
}

void retrieveParcel(Parcel **head){
    string phone;
    Parcel* n = *head;
    int pin;

    cout << "Enter phone number : ";
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
                    n->pin = NULL;
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

void displayLocker(Parcel* n){
    cout << "==========LOCKER==========";
    while(n!=NULL){
        cout
        << "Locker id : "<< n->locker_id << endl
        << "Parcel id : "<< n->parcel_id << endl
        << "Phone : "<< n->phone << endl
        << "Pin : "<< n->pin << endl
        << endl;
        n=n->next;
    }
    cout << "\n=====END OF LOCKER=====";
}

void displayLockerEx(Parcel* n){
    cout << "==========LOCKER_EX==========";
    while(n!=NULL){
        if(n->parcel_id==""){
            n = n->next;
        }else{
            cout
            << "====================" << endl
            << "Locker id : "<< n->locker_id << endl
            << "Parcel id : "<< n->parcel_id << endl
            << "Phone : "<< n->phone << endl
            << "Pin : "<< n->pin << endl
            << endl;
            n=n->next;
        }
    }

    cout << "\n=====END OF LOCKER=====";
}


int main()
{  
    Parcel *cendi_head = NULL,*cendi_tail = NULL;
    createLocker(&cendi_head,&cendi_tail,10000);
    int input;

    do{
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
            cout << "\nYour input: ";
            cin >> input;

            switch(input){
            case 1:
                displayLocker(cendi_head);
                break;
            case 2:
                displayLockerEx(cendi_head);
                break;
            default:
                cout << "Wrong number" << endl << endl;
                break;
            }
            break;
        default:
            cout << "Wrong number" << endl << endl;
            break;
        }
    }while(true);


    return 0;
}
