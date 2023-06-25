#pragma once
#include <iostream>
using namespace std;

class Person
{

protected:
	char* name;
	int age;
	char gender; //  F - female,  M - male
	


	virtual void print(ostream& out)const;

public:

	Person(const char* pName, int theAge, char gen);				//c'tor
	Person(const Person& other);									// copy c'tor
	Person(Person&& other) noexcept;								//  move copy c'tor
	Person(ostream& out, istream& in); //c'tor create with user (talks with the user)
	virtual ~Person();                                                            // d'tor

	Person& operator =(const Person& p);							// operator =
	const Person& operator =(Person&& p) noexcept;					// operator move =

    friend ostream& operator <<(ostream& out, const Person& p);		// operaor <<
	Person& operator ++();											// operator ++ for age

	const char* getName()const;
	int getAge()const;
	char getGender()const;

	void setName(const char* name);
};

