#pragma once
#include <iostream>
using namespace std;

class clsPerson
{
private:
	int _ID;
	string _firstName;
	string _lastName;
	string _email;
	string _phoneNumber;
	
public:
	clsPerson(int ID, string firstName, string lastName, string email, string phoneNumber)
	{
		_ID = ID;
		_firstName = firstName;
		_lastName = lastName;
		_email = email;
		_phoneNumber = phoneNumber;
	}


	int getID()
	{
		return _ID;
	}
	__declspec(property(get = getID)) int ID;

	void setFirstName(string firstName)
	{
		_firstName = firstName;
	}

	string getFirstName()
	{
		return _firstName;
	}

	__declspec(property(get = getFirstName, put = setFirstName)) string firstName;

	void setLastName(string lastName)
	{
		_lastName = lastName;
	}

	string getLastName()
	{
		return _lastName;
	}

	__declspec(property(get = getLastName, put = setLastName)) string lastName;

	void setEmail(string email)
	{
		_email = email;
	}

	string getEmail()
	{
		return _email;
	}

	__declspec(property(get = getEmail, put = setEmail)) string email;

	void setPhoneNumber(string phoneNumber)
	{
		_phoneNumber = phoneNumber;
	}

	string getPhoneNumber()
	{
		return _phoneNumber;
	}

	__declspec(property(get = getPhoneNumber, put = setPhoneNumber)) string phoneNumber;

	string getFullName()
	{
		return _firstName + " " + _lastName;
	}

	void print()
	{
		cout << "Info :-" << endl;
		cout << "--------------------" << endl;
		cout << " ID          : " << _ID << endl;
		cout << " First Name  : " << _firstName << endl;
		cout << " Last Name   : " << _lastName << endl;
		cout << " Full Name   : " << getFullName() << endl;
		cout << " E-Mail      : " << _email << endl;
		cout << " Phone Number: " << _phoneNumber << endl;
		cout << "--------------------" << endl;
	}

	void sendEmail(string subject, string body)
	{
		cout << endl;
		cout << "This Email message is being sent to: " << _email << endl;
		cout << "Subject: " << subject << endl;
		cout << "Body   : " << body << endl;
		cout << endl;
	}

	void sendSMS(string message)
	{
		cout << endl;
		cout << "This SMS message is being sent to: " << _phoneNumber << endl;
		cout << "Message: " << message << endl;
		cout << endl;
	}

};

