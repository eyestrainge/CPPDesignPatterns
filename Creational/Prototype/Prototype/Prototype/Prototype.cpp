#include <string>
#include <iostream>



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

	Contact(const Contact& other):
		name(other.name),
		work_address(new Address{*other.work_address})
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



int main()
{
	//Address* addr = new Address{ "123 East Dr", "London" }; // Prototype

	//Contact john{ "John Doe", addr };
	//john.work_address->suite = 100;

	//Contact jane{ "Jane Doe", addr };
	//jane.work_address->suite = 123;

	//Contact jill{ jane };
	//jill.work_address->suite = 1000;

	//std::cout
	//	<< john << std::endl
	//	<< jane << std::endl
	//	<< jill << std::endl;

	//delete addr;



	Contact employee{ "", new Address{"123 East Dr", "London", 0} }; // Prototype

	Contact john{ employee };
	john.name = "John";
	john.work_address->suite = 100;
	
	Contact jane{ employee };
	jane.name = "Jane";
	jane.work_address->suite = 123;

	std::cout
		<< john << std::endl
		<< jane << std::endl;

	return 0;
}
