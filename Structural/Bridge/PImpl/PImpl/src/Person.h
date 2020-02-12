#pragma once

#include <stdio.h>
#include <string>
#include <iostream>

struct Person
{
	std::string name;

	struct PersonImpl;
	PersonImpl* impl;

	Person();
	~Person();

	void greet();
};