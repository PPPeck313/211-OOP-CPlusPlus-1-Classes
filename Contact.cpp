#include "Address.h"
#include "Contact.h"
#include <iostream>
#include <string>
#include <regex>
using namespace std;

/*Preston Peck
CS 211
Project 1
*/

string checkPhone(string& p); //check and correct invalid phone format if necessary
string checkEmail(string& e); //check and correct invalid e-mail format if necessary

//Define
Contact::Contact(string& f, string& l, Address& a, string& p, string& e) {
	firstName = f;
	lastName = l;
	address = a;
	phone = (checkPhone(p));
    email = (checkEmail(e));
}

Contact::Contact() {
	firstName = "";
	lastName = "";
	address = Address();
	phone = "";
	email = "";
}

string Contact::getFirst() const {
    return firstName;
}

void Contact::setFirst(string& f) {
    firstName = f;
}

string Contact::getLast() const {
    return lastName;
}

void Contact::setLast(string& l) {
     lastName = l;
}

Address Contact::getAddress() const {
    return address;
}

void Contact::setAddress(Address& a) {
    address = a;
}

string Contact::getPhone() const {
    return phone;
}

void Contact::setPhone(string& p) {
    phone = checkPhone(p);
}

string Contact::getEmail() const {
    return email;
}

void Contact::setEmail(string& e) {
    email = checkEmail(e);
}

istream& operator >> (istream& is, Contact& c){
    cout<<"Enter contact's last name: ";
    is>>c.lastName;
    cout<<"Enter contact's first name: ";
    is>>c.firstName;
    is>>c.address;
    cout<<"Enter contact's phone number (without spaces): ";
    is>>c.phone;
	c.phone = checkPhone(c.phone);
    cout<<"Enter contact's e-mail: ";
    is>>c.email;
    c.email = checkEmail(c.email);
    cout<<endl;
    return is;
}

ostream& operator << (ostream& os, const Contact& c) {
    os<<"     Name: "<<c.lastName<<", "<<c.firstName<<endl
        <<"     Address: "<<c.address
        <<"     Phone Number: "<<c.phone<<endl
        <<"     E-mail: "<<c.email<<endl<<endl;
        return os;
}

//Comparators
const bool Contact::operator < (const Contact& other) const {
    if (lastName == "") {//would ordinarily return true, needed to move to back
        return false;
    }
    else if (other.lastName == "") {//would ordinarily return false, needed to move to back
        return true;
    }
    else if (lastName < other.lastName) {
        return true;
    }
    else if (lastName == other.lastName) {
        if (firstName < other.firstName) {
            return true;
        }
    }
    return false;
}

const bool Contact::operator > (const Contact& other) const {
    if (lastName == "") {//would ordinarily return false, needed to move to back
        return true;
    }
    else if (other.lastName == "") {//would ordinarily return true, needed to move to back
        return false;
    }
    else if (lastName > other.lastName) {
        return true;
    }
    else if (lastName == other.lastName) {
        if (firstName > other.firstName) {
            return true;
        }
    }
    return false;
}

const bool Contact::operator == (const Contact& other) const {
    if (lastName == other.lastName && firstName == other.firstName) {
        return true;
    }
    return false;
}

const bool Contact::operator != (const Contact& other) const {
    if (lastName != other.lastName) {
        return true;
    }
    else if (lastName == other.lastName) {
        if (firstName != other.firstName) {
           return true; 
        }
    }
    return false;
}

const bool Contact::operator <= (const Contact& other) const {
   if (lastName == "") {//would ordinarily return true, needed to move to back
        return false;
    }
    else if (other.lastName == "") {//would ordinarily return false, needed to move to back
        return true;
    }
    else if (lastName < other.lastName) {
        return true;
    }
    else if (lastName == other.lastName) {
        if (firstName < other.firstName || firstName == other.firstName) {
            return true;
        }
    }
    return false;     
}

const bool Contact::operator >= (const Contact& other) const {
    if (lastName == "") {//would ordinarily return false, needed to move to back
        return true;
    }
    else if (other.lastName == "") {//would ordinarily return true, needed to move to back
        return false;
    }
    else if (lastName > other.lastName) {
        return true;
    }
    else if (lastName == other.lastName) {
        if (firstName > other.firstName || firstName == other.firstName) {
            return true;
        }
    }
    return false;   
}

//Non-member functions
string checkPhone(string& p) {
    string tryAgain;
	while (regex_match(p, regex("\\d{3}-\\d{3}-\\d{4}")) == false) {
        cerr<<"Invalid phone #";
        cout<<", would you like to try again? (Y/N): ";
		cin>>tryAgain;
		while (tryAgain != "Y" && tryAgain != "N") {
			cout<<"Try again? (Y/N): ";
			cin>>tryAgain;
		}
		if (tryAgain == "N") {
			p = "";
            cout<<endl;
			break;
		}
		else {
			cout<<endl<<"Enter contact's phone number (hyphenated): ";
			cin>>p;
		} 
	}
    return p;
}

string checkEmail(string& e) {
    string tryAgain;
	while (regex_match(e, regex("[a-zA-Z0-9]+\\@[a-zA-Z0-9]+\\.(net|org|com|gov|edu)")) == false) {
        cerr<<"Invalid e-mail";
        cout<<", would you like to try again? (Y/N): ";
		cin>>tryAgain;
		while (tryAgain != "Y" && tryAgain != "N") {
			cout<<"Try again? (Y/N): ";
			cin>>tryAgain;
		}
		if (tryAgain == "N") {
			e = "";
            cout<<endl;
			break;
		}
		else {
			cout<<endl<<"Enter contact's e-mail: ";
			cin>>e;
		}
	}
    return e;
}