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

void displayLocker(Parcel* n){
    while(n!=NULL){
        cout
        << "Locker id : "<< n->locker_id << endl
        << "Parcel id : "<< n->parcel_id << endl
        << "Phone : "<< n->phone << endl
        << "Pin : "<< n->pin << endl
        << endl;
        n=n->next;
    }
}

int main()
{
    Parcel *cendi_head = NULL,*cendi_tail = NULL;
    display(cendi_head);
    return 0;
}
