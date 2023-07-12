#pragma once
#include <iostream>
#include "Save.h"

using namespace std;
#define MAX_NAME_LEN 100



class Person: public Save
{
protected:
	char* name;
	int age;
	char gender; //  F - female,  M - male
	


	virtual void print(ostream& out)const;

public:

	Person(const char* pName, int theAge, char gen);	//c'tor
	Person(const Person& other);	// copy c'tor
	Person(Person&& other) noexcept;	//  move copy c'tor
	virtual ~Person();	// d'tor
	
	//read and write from file
	Person(ifstream& in); 
	virtual void saveToFile(ofstream& out)const;
	

	Person& operator =(const Person& p);							// operator =
	const Person& operator =(Person&& p) noexcept;					// operator move =

    friend ostream& operator <<(ostream& out, const Person& p);		// operaor <<
	Person& operator ++();											// operator ++ for age

	const char* getName()const;
	int getAge()const;
	char getGender()const;

	void setName(const char* name);
};

