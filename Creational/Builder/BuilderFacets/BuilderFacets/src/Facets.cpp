#include "PersonAddressBuilder.h"
#include "PersonJobBuilder.h"

int main()
{
	Person p = Person::create()
		.lives().at("Address").with_postcode("12345").in("City")
		.works().at("Company").as_a("Position").earning(10e5);

	cout << p << endl;

	return 0;
}