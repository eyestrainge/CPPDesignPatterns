#include <string>
#include <iostream>
#include <memory>
#include <sstream>
#include <functional>
#include <boost/serialization/serialization.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

using namespace std;

struct Address
{
    string street, city;
    int suite;

    friend ostream& operator<<(ostream& os, const Address& obj)
    {
        return os
            << "Street: " << obj.street << " "
            << "City: " << obj.city << " "
            << "Suite: " << obj.suite;
    }

private:
    friend class boost::serialization::access;

    template<class Ar>
    void serialize(Ar& ar, const unsigned int version)
    {
        ar & street;
        ar & city;
        ar & suite;
    }
};

struct Contact
{
    string name;
    Address* address = nullptr;

    friend ostream& operator<<(ostream& os, const Contact& obj)
    {
        return os
            << "Name: " << obj.name << " "
            << "Address: " << *obj.address;
    }

private:
    friend class boost::serialization::access;

    template<class Ar>
    void serialize(Ar& ar, const unsigned int version)
    {
        ar & name;
        ar & address; // no *
    }
};

int main()
{
    Contact john;
    john.name = "John Doe";
    john.address = new Address{ "123 East Dr", "London", 123 };

    auto clone = [](const Contact& c)
    {
        ostringstream oss;
        boost::archive::text_oarchive oa(oss);
        oa << c;
        string s = oss.str();

        istringstream iss(oss.str());
        boost::archive::text_iarchive ia(iss);
        Contact result;
        ia >> result;

        return result;
    };

    Contact jane = clone(john);
    jane.name = "Jane Doe";
    jane.address->street = "123B West Dr";
    jane.address->suite = 300;

    cout
        << john << endl
        << jane << endl;

    return 0;
}