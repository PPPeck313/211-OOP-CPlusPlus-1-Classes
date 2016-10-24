#include "Address.h"
#ifndef CONTACT_H
#define CONTACT_H

/*Preston Peck
CS 211
Project 1
*/

//Declare
class Contact {
	private:
       string lastName;
       string firstName;
	   Address address;
	   string phone;
	   string email;
       
    public:
       //Constructors
       Contact(); //Default
       Contact(string& f, string& l, Address& a, string& p, string& e);
       
       //Accessors
	   string getFirst() const;
       string getLast() const; 
       Address getAddress() const;
       string getPhone() const;
       string getEmail() const;
       
	   //Mutators
	   void setFirst(string& f);
       void setLast(string& l);
	   void setAddress(Address& a);
	   void setPhone(string& p);
       void setEmail(string& e);
       
       //Input
       friend istream& operator >> (istream& is, Contact& c); //Guided mutator for all of an object's parameters
       
       //Output
       friend ostream& operator << (ostream& os, const Contact& c); //Display contact
       
       //Comparators
       const bool operator < (const Contact& other) const;
       const bool operator > (const Contact& other) const;
       const bool operator == (const Contact& other) const;
       const bool operator != (const Contact& other) const;
       const bool operator <= (const Contact& other) const;
       const bool operator >= (const Contact& other) const;
};
#endif