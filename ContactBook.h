#include "Address.h"
#include "Contact.h"
#ifndef CONTACTBOOK_H
#define CONTACTBOOK_H

/*Preston Peck
CS 211
Project 1
*/

//Declare
class ContactBook {
    private:
        string ownerFirstName;
        string ownerLastName;
        Contact** contactBook;
        int size;
        int capacity;
        
        void grow();
        void sort();
    public:
        //Constructors
        ContactBook(); //Default
        ContactBook(string& of, string& ol, Contact**& cb, int& c);
        ContactBook(string& of, string& ol);
        
        //Copy Constructors
        ContactBook(const ContactBook& cb);
        
        //Assignment Overload
        void operator = (const ContactBook& cb);
        
        //Destructor
        ~ContactBook();
        
       //Accessors
	   string getOwnerFirst() const;
       string getOwnerLast() const; 
       Contact** getContactBook() const;
       int getSize() const;
       int getCapacity() const;
       
	   //Mutators
	   void setOwnerFirst(string& of);
       void setOwnerLast(string& ol);
	   void setContactBook(Contact**& c);
       void setSize(int& s);
       void setCapacity(int& c);
       
       //Utility
       friend istream& operator >> (istream& is, ContactBook& c); //void createContact();
       void deleteContact();
       void displayOne();
       void updateContact();
       void merge(ContactBook& other);
       friend ostream& operator << (ostream& os, const ContactBook& cb); //void displayAll();
};
#endif