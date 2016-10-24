#include "Address.h"
#include "Contact.h"
#include "ContactBook.h"
#include <iostream>
#include <string>
using namespace std;

/*Preston Peck
CS 211
Project 1
*/

int searchName(Contact* c[], int& end);
void duplicate(Contact* c[], int& start, int& end);

//Define
void ContactBook::grow() {
    capacity = (capacity * 2) + 1;//0,1,3,7,15,31... from new
    Contact** temp = contactBook;
    contactBook = new Contact*[capacity];   
    for (int i = 0; i < size; i++) {
        contactBook[i] = temp[i];
    }
    delete[] temp;
}

void ContactBook::sort() {//Bubble sort
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size - 1 - i; ++j) {
            if (*contactBook[j] > *contactBook[j + 1]) {
                Contact* temp = contactBook[j];
                contactBook[j] = contactBook[j + 1];
                contactBook[j + 1] = temp;
            }
        }
    }
}

ContactBook::ContactBook() {
    ownerFirstName = "";
    ownerLastName = "";
    size = 0;
    capacity = 0;
    contactBook = NULL;
}

ContactBook::ContactBook(string& of, string& ol, Contact**& cb, int& c) {
    ownerFirstName = of;
    ownerLastName = ol;
    contactBook = cb;
    capacity = c;
    size = 0;
    if ((contactBook != NULL)) {
        for (int i = 0; i < capacity; i++) {
            if (cb[i]->getFirst() != "") {
                size++;
            }
        }
    }
}

ContactBook::ContactBook(string& of, string& ol) {
    ownerFirstName = of;
    ownerLastName = ol;
    size = 0;
    capacity = 0;
    contactBook = new Contact*[capacity];
}

ContactBook::ContactBook(const ContactBook& cb) {
    ownerFirstName = cb.ownerFirstName;
    ownerLastName = cb.ownerLastName;
    size = cb.size;
    capacity = cb.capacity;
    contactBook = new Contact*[capacity];
    for (int i = 0; i < size; i++) {
        contactBook[i] = cb.contactBook[i];
    }
    sort();
}
        
void ContactBook::operator = (const ContactBook& cb) {
    ownerFirstName = cb.ownerFirstName;
    ownerLastName = cb.ownerLastName;
    size = cb.size;
    capacity = cb.capacity;
    contactBook = new Contact*[capacity];
    for (int i = 0; i < size; i++) {
        contactBook[i] = cb.contactBook[i];
    }
    sort();
}
        
ContactBook::~ContactBook() {
    for (int i; i < capacity; i++) {
        delete contactBook[i];
    }
    delete[] contactBook;   
}

string ContactBook::getOwnerFirst() const {
    return ownerFirstName;
}
    
void ContactBook::setOwnerFirst(string& of) {
    ownerFirstName = of;
}

string ContactBook::getOwnerLast() const {
    return ownerLastName;
}
    
void ContactBook::setOwnerLast(string& ol) {
    ownerLastName = ol;
}
        
Contact** ContactBook::getContactBook() const {
    return contactBook;
}
    
void ContactBook::setContactBook(Contact**& cb) {
    if (contactBook != NULL) {
        delete[] contactBook;
    }
    contactBook = cb;
    sort();
}

int ContactBook::getSize() const {
    return size;
}

void ContactBook::setSize(int& s) {
    size = s;
}

int ContactBook::getCapacity() const {
    return capacity;
}

void ContactBook::setCapacity(int& c) {
    capacity = c;
}

istream& operator >> (istream& is, ContactBook& cb) {
    cout<<endl;
    if (cb.size == cb.capacity) {
        cb.grow();
    }
    cb.contactBook[cb.size] = new Contact();
    is>>*cb.contactBook[cb.size];
    cb.size++;
    cb.sort();
    return is;
}

void ContactBook::deleteContact() {
    if (contactBook != NULL && size != 0) {
        int index = searchName(contactBook, size);
        if (index < size) {
            duplicate(contactBook, index, size);
            cout<<"Deleting contact #"<<index + 1<<"..."<<endl<<endl;
            delete contactBook[index];//destroy object
            contactBook[index] = new Contact();//NULL?
            sort();
            size--;
        }    
        else {   
            cerr<<"Deletion failed!"<<endl
                <<"Name was not found!"<<endl<<endl;
        }  
    }
    else {
        cerr<<endl<<"Deletion failed!"<<endl
            <<"Contact book is empty!"<<endl<<endl;
    }   
}//Contact is now ONLY identified by last name and first name for the sake of simplification

void ContactBook::displayOne() {
    if (contactBook != NULL && size != 0) {
    int index = searchName(contactBook, size);
        if (index < size) {
            duplicate(contactBook, index, size);
            cout<<"Displaying contact #"<<index + 1<<"..."<<endl<<endl
                <<*contactBook[index];
        }
        else {
            cerr<<"Display failed!"<<endl
                <<"Name was not found!"<<endl<<endl;
        }
    }
    else {
        cerr<<endl<<"Display failed!"<<endl
            <<"Contact book is empty!"<<endl<<endl;
    }
}//Contact is now ONLY identified by last name and first name for the sake of simplification

void ContactBook::updateContact() {
    if (contactBook != NULL && size != 0) {
        int index = searchName(contactBook, size);
        if (index < size) {
            duplicate(contactBook, index, size);
            cout<<"Updating contact #"<<index + 1<<"..."<<endl<<endl;
            cin>>*contactBook[index];
            sort();
        }
        else {
            cerr<<"Update failed!"<<endl
                <<"Name was not found!"<<endl<<endl;
        }
    }
    else {
        cerr<<endl<<"Update failed!"<<endl
            <<"Contact book is empty!"<<endl<<endl;
    }
}//Contact is now ONLY identified by last name and first name for the sake of simplification

ostream& operator << (ostream& os, const ContactBook& cb) {
    os<<endl<<"Owner: "<<cb.ownerLastName<<", "<<cb.ownerFirstName<<endl<<endl;
    if ((cb.contactBook != NULL) && (cb.size != 0)) {//preliminary check
        os<<"The following contacts are stored in this contact book:"<<endl<<endl;
        for (int i = 0; i < cb.size; i++) {
            os<<"     Contact #"<<i + 1<<endl
              <<*cb.contactBook[i];
        }
        os<<"     "<<cb.size<<" total contact(s) found"<<endl<<endl;
    }
    else {
        os<<"Contact book is empty!"<<endl<<endl;
    }
    return os;
}

void ContactBook::merge(ContactBook& other) {
    if ((other.contactBook != NULL)) {
        int temp = size;
        size = (size + other.size);
        while (size >= capacity) {
            grow();
        }
        for (int i = temp, j = 0; i < size && j < other.size; i++, j++) {
            contactBook[i] = other.contactBook[j];
        }
    }
    sort();
}

//Non-class functions
int searchName(Contact* c[], int& end) {
    string l;
    string f;
    cout<<"Enter contact's last name: ";
    cin>>l;
    cout<<"Enter contact's first name: ";
    cin>>f;
    cout<<endl;
    for (int i = 0; i < end; i++) {
        if (c[i]->getLast() == l && c[i]->getFirst() == f) {
            return i;
        }
    }
    return end;
}

void duplicate(Contact* c[], int& start, int& end) {
    int copies = 1;
    for (int i = start + 1; i < end; ++i) {
        if (c[i]->getFirst() == c[start]->getFirst() && c[i]->getLast() == c[start]->getLast()) {
            copies++;
        }
        if (i == end - 1 && copies > 1) {
            cout<<copies<<" contacts associated with this name"<<endl 
                <<"Returning first detected instance..."<<endl<<endl;
        }
    }
}