#include "Person.h"
#include <fstream>



Person::Person(const char* pName, int theAge, char gen)
{
	setName(pName);
	age = theAge;
	gender = gen;
}

Person::Person(const Person& other)
{
	setName(other.name);
	age = other.age;
	gender = other.gender;
}

Person::Person(Person&& other)noexcept
{
	name = other.name;
	other.name = nullptr;

	age = other.age;
	gender = other.gender;
}

Person:: ~Person()
{
	delete[] name;
}

Person::Person(ifstream& in)
{
	char tmp; 
	in >> name >> tmp >> age >> tmp >> gender;
}

void Person::saveToFile(ofstream& out) const
{
	out << name << DEL << age << DEL << gender << endl;
}


Person& Person::operator=(const Person& p)
{
	if (this != &p)
	{
		setName(p.name);
		age = p.age;
		gender = p.gender;
	}
	return *this;
}

const Person& Person::operator=(Person&& p)noexcept
{
	if (this != &p)
	{
		name = p.name;
		p.name = nullptr;

		age = p.age;
		gender = p.gender;
	}
	return *this;
}

Person& Person::operator++()
{
	age++;
	return *this;
}

const char* Person::getName() const
{
	return name;
}

int Person::getAge() const
{
	return age;
}

char Person::getGender() const
{
	return gender;
}

void Person::setName(const char* pName)
{
	if (name != nullptr)
		delete[] name;

	name = _strdup(pName);
}

ostream& operator<<(ostream& out, const Person& p)
{
	p.print(out);
	return out;
}

void Person::print(ostream& out) const
{
	out << "Name: " << name;
	out << ", Age: " << age;
	out << ", Gender: " << gender << endl;
}
