#include "Person.h"



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

Person::Person(ostream& out, istream& in)
{
	cout << "Enter Person details:" << endl;

	cout << "Name: ";
	char name[100];
	in.getline(name, 100);
	setName(name);

	cout << "Age: ";
	int ageUser;
	in >> ageUser;
	in.ignore();
	age = ageUser;

	cout << "Gender (M/F): ";
	char genderUser;
	in >> genderUser;
	in.ignore();
	gender = genderUser;

}

Person:: ~Person()
{
	delete[] name;
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
	out << "Name: " << p.name;
	out << ", Age: " << p.age;
	out << ", Gender: " << p.gender << endl;
}
