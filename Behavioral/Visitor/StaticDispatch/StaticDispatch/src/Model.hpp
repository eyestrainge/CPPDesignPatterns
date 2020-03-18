#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iostream>
using namespace std;

struct Element
{
	virtual ~Element() = default;
	virtual void print(ostringstream& oss) const = 0;
};

struct TextElement : Element
{
	string text;

	explicit TextElement(const string& text) :
		text{ text }
	{}
};

struct Paragraph : TextElement
{
	explicit Paragraph(const string& text) :
		TextElement{ text }
	{}

	void print(ostringstream& oss) const override
	{
		oss << "<p>" << text << "</p>\n";
	}
};

struct ListItem : TextElement
{
	explicit ListItem(const string& text) :
		TextElement{ text }
	{}

	void print(ostringstream& oss) const override
	{
		oss << "<li>" << text << "</li>\n";
	}
};

struct List : vector<ListItem>, Element
{
	List(const initializer_list<value_type>& _Ilist) :
		vector<ListItem>{ _Ilist }
	{}

	void print(ostringstream& oss) const override
	{
		oss << "<ul>\n";
		for (auto li : *this)
			li.print(oss);
		oss << "</ul>\n";
	}
};