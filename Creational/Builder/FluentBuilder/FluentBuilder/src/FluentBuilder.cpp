#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <memory>

struct HtmlBuilder;

struct HtmlElement
{
	std::string name;
	std::string text;
	std::vector<HtmlElement> elements;
	const size_t indent_size = 2;

	HtmlElement() {}
	HtmlElement(const std::string& name, const std::string& text) :
		name{ name },
		text{ text }
	{}

	std::string e_str(int indent = 0) const
	{
		std::ostringstream oss;
		std::string ind(indent_size * indent, ' ');

		oss << ind << "<" << name << ">" << std::endl;

		if (text.size() > 0)
			oss << std::string(indent_size * (indent + 1), ' ') << text << std::endl;

		for (const auto& e : elements)
			oss << e.e_str(indent + 1);

		oss << ind << "</" << name << ">" << std::endl;

		return oss.str();
	}

	static HtmlBuilder build(std::string root_name);
};

struct HtmlBuilder
{
	HtmlElement root;

	HtmlBuilder(std::string name)
	{
		root.name = name;
	}

	operator HtmlElement() { return root; }

	HtmlBuilder& add_child(std::string child_name, std::string child_text)
	{
		HtmlElement e(child_name, child_text);
		root.elements.emplace_back(e);

		return *this;
	}
};

HtmlBuilder HtmlElement::build(std::string root_name)
{
	return HtmlBuilder(root_name);
}

int main()
{
	HtmlElement e = HtmlElement::build("ul")
		.add_child("li", "Hello ")
		.add_child("li", "Brave ")
		.add_child("li", "World!");

	std::cout << e.e_str() << std::endl;

	return 0;
}