#include "Address.h"
#include "Contact.h"
#include "ContactBook.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/*Preston Peck
CS 211
Project 1
Implement a program that will manage a several contact books of different people, using
the classes that you developed in homework assignments 2-6. The program should be
command-line interfaced.

Modify your contact book class in the following way:
1) Your add contact function will now add a contact in a sorted order
2) Your delete contact function will preserve the sorted order of the contacts
3) Provide a private sort function which will sort the contact list internally
4) Provide a merge function that will merge the second contact list into the first

Your main program will store up to 5 contact books read from a file. You will never have
more than 5 contact books in your project. The main program should start by reading the
file contactbooks.txt to create contact book objects dynamically and store them as
pointers in an array of capacity 5. The format of the file will be:

Owner-first-name|Owner-last-name
first-name|last-name|phone|email|home|street|apt|city|state|zip
first-name|last-name|phone|email|home|street|apt|city|state|zip
first-name|last-name|phone|email|home|street|apt|city|state|zip
endofbook|

The program will have a menu with the following options:

1) Create a New Contact Book (note: you will only be able to create up to five contact
books. If you attempt to create more, the program should report an error)
2) Remove a Contact Book (identified by owner’s name)
3) Display All Contact Books (in your system)
4) Merge Two Contact Books (both books are identified by owner’s name)
5) Select a Contact Book (identified by owner’s name) to perform following
operations:
    a) Add New Contact
    b) Delete Old Contact
    c) Display Contact Info
    d) Update Contact Info
    e) Display Entire Contact book
6) Exit

Note: When you start the program the contact books must be read in from a file called
contactbooks.txt. When you exit a program the contact books must be stored back to a
file called contactbooks.txt. Internally in your program contact books are stored in an
array of capacity 5.
*/

int open(ContactBook cb[], int& end);
int last(ContactBook cb[], int& end);
int searchOwner(ContactBook cb[], int& end);
void duplicate(ContactBook cb[], int& start, int& end);
bool createContactBook(ContactBook cb[], int& end);
bool deleteContactBook(ContactBook cb[], int& end);
void displayContactBooks(ContactBook cb[], int& end);

//Use
int main() {
    ofstream outfile;
    ifstream data;
    ifstream capacity;
    data.open("contactbooks.txt");
    if (!data.is_open()) {
        cerr<<"File failed to open!"<<endl;
        return 0;
    }
    capacity.open("contactbooks.txt");
    
    int length = 5;
    string storeData;
    string storeCapacity;
    string option;
    string option2;
    
    ContactBook cbArray[5];
    int counterContactBook = 0;
    
    while(!data.eof() && counterContactBook != length) {
        getline(data, storeData, '|');//initial check
        getline(capacity, storeCapacity);//Owner-first-name|Owner-last-name does not equate to a contact
        
        int cap = 0;
        while (storeCapacity != "endofbook|") {
            getline(capacity, storeCapacity);
            if (storeCapacity != "endofbook|") {
                cap++;
            }
        }
        
        getline(capacity, storeCapacity);//\n return between contact books
        
        cbArray[counterContactBook] = ContactBook();
            
        cbArray[counterContactBook].setCapacity(cap);
        cbArray[counterContactBook].setSize(cap);
        
        cbArray[counterContactBook].setOwnerFirst(storeData);
        
        getline(data, storeData);
        cbArray[counterContactBook].setOwnerLast(storeData);
             
        Contact** cb = new Contact*[cbArray[counterContactBook].getCapacity()];
        
        int counterContact = 0;
        while (storeData != "endofbook") {      
            cb[counterContact] = new Contact();
             
            getline(data, storeData, '|');
            if (storeData != "endofbook") {
                cb[counterContact]->setFirst(storeData);
              
                getline(data, storeData, '|');
                cb[counterContact]->setLast(storeData);
        
                getline(data, storeData, '|');
                cb[counterContact]->setPhone(storeData);
        
                getline(data, storeData, '|');
                cb[counterContact]->setEmail(storeData);
        
                Address a;
                getline(data, storeData, '|');
                a.setHome(storeData);
        
                getline(data, storeData, '|');
                a.setStreet(storeData);
        
                getline(data, storeData, '|');
                a.setApt(storeData);
        
                getline(data, storeData, '|');
                a.setCity(storeData);
        
                getline(data, storeData, '|');
                a.setState(storeData);
        
                getline(data, storeData);
                a.setZip(storeData);

                cb[counterContact]->setAddress(a);
            
                counterContact++;
            }
        }
        getline(data, storeData);//last '|' to \n
        getline(data, storeData);//\n return between contact books
        
        cbArray[counterContactBook].setContactBook(cb);
        
        counterContactBook++;
    }
    data.close();
    capacity.close();

    cout<<endl<<"Welcome to Project 1!"<<endl<<endl
        
        <<"     1) Create New Contact Book"<<endl
        <<"     2) Remove Contact Book"<<endl
        <<"     3) Display All Contact Books"<<endl
        <<"     4) Merge Two Contact Books"<<endl
        <<"     5) Select Contact Book"<<endl
        <<"     6) Exit"<<endl<<endl
        
        <<"Please select an option from the menu above (1/2/3/4/5/6): ";
    cin>>option;
        
    while (option != "6") {
        while (option != "1" && option != "2" && option != "3" && option != "4" && option != "5" && option != "6") {
			cout<<"Please select an option from the menu above (1/2/3/4/5/6): ";
			cin>>option;
        }
        
        if (option == "1") {//Create
            if (createContactBook(cbArray, length)) {
                counterContactBook++;
            }
        }
        
        else if (option == "2") {//Delete
            if (deleteContactBook(cbArray, length)) {
                counterContactBook--;
            }  
        }
        
        else if (option == "3") {//Display all
            displayContactBooks(cbArray, length); 
        }
        
        else if (option == "4") {//Merge
            int cb1;
            int cb2;
            cout<<"Destination book:"<<endl;
            cb1 = searchOwner(cbArray, length);
            duplicate(cbArray, cb1, length);
            if (cb1 == length) {
                cout<<"Merge failed!"<<endl
                    <<"Name was not found!"<<endl<<endl;
            }
            else {
                cout<<"Source book:"<<endl;
                cb2 = searchOwner(cbArray, length);
                duplicate(cbArray, cb2, length);
                if (cb2 == length) {
                    cout<<"Merge failed!"<<endl
                        <<"Name was not found!"<<endl<<endl;
                }
                else if (cb1 == cb2) {
                    cout<<"Merge failed!"<<endl
                        <<"Selected the same contact book!"<<endl<<endl;
                }
                else {
                    cbArray[cb1].merge(cbArray[cb2]);
                    delete[] cbArray[cb2].getContactBook();
                    cbArray[cb2] = ContactBook();
                    counterContactBook--;
                }
            }
        }
                  
        else if (option == "5"){
            int index = searchOwner(cbArray, length);
            duplicate(cbArray, index, length);
            if (index < length) { 
                cout<<"Welcome to Contact Book #"<<index + 1<<"!"<<endl<<endl
        
                    <<"     a) Add New Contact"<<endl
                    <<"     b) Delete Old Contact"<<endl
                    <<"     c) Display Contact Info"<<endl
                    <<"     d) Update Contact Info"<<endl
                    <<"     e) Display Entire Contact List"<<endl
                    <<"     f) Exit"<<endl<<endl
            
                    <<"Please select an option from the menu above (a/b/c/d/e/f): ";
                    cin>>option2;
        
                while (option2 != "f") {
                    while (option2 != "a" && option2 != "b" && option2 != "c" && option2 != "d" && option2 != "e" && option2 != "f") {
			            cout<<"Please select an option from the menu above (a/b/c/d/e/f): ";
			            cin>>option2;
                    }
                
                    if (option2 == "a") {//Create
                        cin>>cbArray[index]; 
                    }
        
                    else if (option2 == "b") {//Delete
                        cbArray[index].deleteContact();  
                    }
        
                    else if (option2 == "c") {//Display one
                        cbArray[index].displayOne(); 
                    }
        
                    else if (option2 == "d") {//Update
                        cbArray[index].updateContact();  
                    }
        
                    else if (option2 == "e") {//Display all
                        cout<<cbArray[index]; 
                    }
                
                    cout<<"Operation completed!"<<endl
                        <<"Returning to submenu..."<<endl<<endl
                
                        <<"     a) Add New Contact"<<endl
                        <<"     b) Delete Old Contact"<<endl
                        <<"     c) Display Contact Info"<<endl
                        <<"     d) Update Contact Info"<<endl
                        <<"     e) Display Entire Contact List"<<endl
                        <<"     f) Exit"<<endl<<endl
            
                        <<"Please select an option from the menu above (a/b/c/d/e/f): ";
                    cin>>option2;
                }
            }
            else {
                cout<<"Selection failed!"<<endl
                    <<"Name was not found!"<<endl;
            }
            cout<<endl;
        }
        
        cout<<"Operation completed!"<<endl
            <<"Returning to main menu..."<<endl<<endl

            <<"     1) Create New Contact Book"<<endl
            <<"     2) Remove Contact Book"<<endl
            <<"     3) Display All Contact Books"<<endl
            <<"     4) Merge Two Contact Books"<<endl
            <<"     5) Select Contact Book"<<endl
            <<"     6) Exit"<<endl<<endl
            
            <<"Please select an option from the menu above (1/2/3/4/5/6): ";
        cin>>option;
    }
    outfile.open("contactbooks.txt");
    for (int i = 0; i <= last(cbArray, length); i++) {
        if (cbArray[i].getOwnerFirst() != "") {//reliant on no empty strings for owner info
            outfile<<cbArray[i].getOwnerFirst()<<"|"
                <<cbArray[i].getOwnerLast()<<endl;
            for (int j = 0; j < cbArray[i].getSize(); j++) {
                outfile<<cbArray[i].getContactBook()[j]->getFirst()<<"|"
                    <<cbArray[i].getContactBook()[j]->getLast()<<"|"
                    <<cbArray[i].getContactBook()[j]->getPhone()<<"|"
                    <<cbArray[i].getContactBook()[j]->getEmail()<<"|"
                    <<cbArray[i].getContactBook()[j]->getAddress().getHome()<<"|"
                    <<cbArray[i].getContactBook()[j]->getAddress().getStreet()<<"|"
                    <<cbArray[i].getContactBook()[j]->getAddress().getApt()<<"|"
                    <<cbArray[i].getContactBook()[j]->getAddress().getCity()<<"|"
                    <<cbArray[i].getContactBook()[j]->getAddress().getState()<<"|"
                    <<cbArray[i].getContactBook()[j]->getAddress().getZip()<<endl;
            }
            if (i == last(cbArray, length)) {
                outfile<<"endofbook|";
                outfile.flush();
            }
            else {
                outfile<<"endofbook|"<<endl<<endl;
                outfile.flush();
            }
        }
    }
    outfile.close();
    return 0;
}

int open(ContactBook cb[], int& end) {
    for (int i = 0; i < end; i++) {
         if (cb[i].getOwnerFirst() == "") {
             return i;
         }
    }
    return end;
}

int last(ContactBook cb[], int& end) {
    int last = -1;
    for (int i = 0; i < end; i++) {
         if (cb[i].getOwnerFirst() != "") {
            last = i;
         }
    }
    return last;
}

int searchOwner(ContactBook cb[], int& end) {
    string ol;
    string of;
    cout<<"Enter owner's last name: ";
    cin>>ol;
    cout<<"Enter owner's first name: ";
    cin>>of;
    cout<<endl;
    for (int i = 0; i < end; i++) {
        if (cb[i].getOwnerLast() == ol && cb[i].getOwnerFirst() == of) {
            return i;
        }
    }
    return end;
}

void duplicate(ContactBook cb[], int& start, int& end) {
    int copies = 1;
    for (int i = start + 1; i < end; i++) {
        if (cb[i].getOwnerFirst() == cb[start].getOwnerFirst() && cb[i].getOwnerLast() == cb[start].getOwnerLast()) {
            copies++;
        }
        if (i == end - 1 && copies > 1) {
            cout<<copies<<" contact books associated with this name"<<endl 
                <<"Returning first detected instance..."<<endl<<endl;
        }
    }
}

bool createContactBook(ContactBook cb[], int& end) {
    int index = open(cb, end);
    if (index < end) {
        cout<<"Creating contact book #"<<index + 1<<"..."<<endl<<endl;
        string ol;
        string of;
        cb[index] = ContactBook();
        cout<<"Enter owner's last name: ";
        cin>>ol;
        cb[index].setOwnerLast(ol);
        cout<<"Enter owner's first name: ";
        cin>>of;
        cout<<endl;
        cb[index].setOwnerFirst(of);
        return true;
    }
    else {
        cerr<<endl<<"Creation failed!"<<endl
            <<"Collection is full!"<<endl<<endl;
        return false;
    }
}

bool deleteContactBook(ContactBook cb[], int& end) {
    int counter = 0;
    for (int i = 0; i < end; i++) {
        if (cb[i].getOwnerFirst() == "") {
            counter++;
        }
    }
    if (counter != end) {
        int index = searchOwner(cb, end);
        if (index < end) {
            duplicate(cb, index, end);
            cout<<"Deleting contact book #"<<index + 1<<"..."<<endl<<endl;
            for (int i = 0; i < cb[index].getSize(); i++) {
                delete cb[index].getContactBook()[i];
            }
            delete[] cb[index].getContactBook();
            cb[index] = ContactBook();
            return true;   
        }
        else {   
            cerr<<"Deletion failed!"<<endl
                <<"Name was not found!"<<endl<<endl;
            return false;
        }
    }
    else {   
        cerr<<endl<<"Deletion failed!"<<endl
            <<"Collection is empty!"<<endl<<endl;
        return false;
    } 
}

void displayContactBooks(ContactBook cb[], int& end) {
    cout<<endl;
    int counter = 0;
    for (int i = 0; i < end; i++) {
        if (cb[i].getOwnerFirst() != "") {
            cout<<"Contact book #"<<i + 1
                <<cb[i];
            counter++;
        }
    }
    if (counter != 0) {
       cout<<counter<<" total contact book(s) found"<<endl<<endl; 
    }
    else {
        cerr<<"Display failed!"<<endl
            <<"No contact books exist!"<<endl<<endl;
    }
}