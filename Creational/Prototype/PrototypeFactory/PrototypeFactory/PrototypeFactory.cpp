#include <string>
#include <iostream>
#include <memory>



struct Address
{
	std::string street;
	std::string city;
	int suite;

	friend std::ostream& operator<<(std::ostream& os, const Address& obj)
	{
		return os
			<< "Street: " << obj.street << " "
			<< "City: " << obj.city << " "
			<< "Suite: " << obj.suite;
	}
};



struct Contact
{
	std::string name;
	Address* work_address;

	Contact(const std::string& name, Address* const work_address) :
		name(name),
		work_address(new Address{ *work_address })
	{}

	Contact(const Contact& other) :
		name(other.name),
		work_address(new Address{ *other.work_address })
	{}

	~Contact()
	{
		delete work_address;
	}

	friend std::ostream& operator<<(std::ostream& os, const Contact& obj)
	{
		return os
			<< "Name: " << obj.name << " "
			<< "Work Address: " << *obj.work_address;
	}
};



struct EmployeeFactory
{
	static Contact main, aux;

	static std::unique_ptr<Contact> NewMainOfficeEmployee(std::string name, int suite)
	{
		return NewEmployee(name, suite, main);
	}

	static std::unique_ptr<Contact> NewAuxOfficeEmployee(std::string name, int suite)
	{
		return NewEmployee(name, suite, aux);
	}

private:
	static std::unique_ptr<Contact> NewEmployee(std::string name, int suite, Contact& prototype)
	{
		auto result = std::make_unique<Contact>(prototype);
		result->name = name;
		result->work_address->suite = suite;

		return result;
	}
};

Contact EmployeeFactory::main{ "", new Address{"123 East Dr", "London", 0} };
Contact EmployeeFactory::aux{ "", new Address{"123B East Dr", "London", 0} };



int main()
{
	/*Contact john{ employee };
	john.name = "John";
	john.work_address->suite = 100;

	Contact jane{ employee };
	jane.name = "Jane";
	jane.work_address->suite = 123;*/



	auto john = EmployeeFactory::NewMainOfficeEmployee("John", 100);	
	auto jane = EmployeeFactory::NewAuxOfficeEmployee("Jane", 123);

	std::cout
		<< *john << std::endl
		<< *jane << std::endl;

	return 0;
}
