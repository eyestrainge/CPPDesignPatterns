#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;



class PersonBuilder;



class Person
{
	string street_address, post_code, city;

	string company_name, position;
	int annual_income = 0;

	Person() {}

public:
	Person(Person&& other):
		street_address(move(other.street_address)),
		post_code(move(other.post_code)),
		city(move(other.city)),
		company_name(move(other.company_name)),
		position(move(other.position)),
		annual_income(other.annual_income)
	{}

	Person& operator=(Person&& other)
	{
		if (this == &other)
			return *this;
		street_address = move(other.street_address);
		post_code = move(other.post_code);
		city = move(other.city);
		company_name = move(other.company_name);
		position = move(other.position);
		annual_income = other.annual_income;
		return *this;
	}

	friend ostream& operator<<(ostream& os, const Person& obj)
	{
		return os
			<< "\nStreet Address: " << obj.street_address
			<< "\tPost Code: " << obj.post_code
			<< "\tCity: " << obj.city
			<< "\nCompany Name: " << obj.company_name
			<< "\tPosition: " << obj.position
			<< "\tAnnual Income: " << obj.annual_income;
	}

	static PersonBuilder create();

	friend class PersonBuilder;
	friend class PersonAddressBuilder;
	friend class PersonJobBuilder;
};
