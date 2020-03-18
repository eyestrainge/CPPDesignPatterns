#pragma once
#include <string>
#include <vector>
#include <typeindex>
#include <map>
#include <algorithm>
#include <sstream>
#include <iostream>
using namespace std;

struct Paragraph;
struct ListItem;
struct List;

struct Visitor
{
	virtual ~Visitor() = default;

	virtual void visit(const Paragraph& p) = 0;
	virtual void visit(const ListItem& p) = 0;
	virtual void visit(const List& p) = 0;

	virtual std::string str() const = 0;
};