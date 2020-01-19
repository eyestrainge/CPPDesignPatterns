#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <memory>

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
};

struct HtmlBuilder
{
	HtmlElement root;

	HtmlBuilder(std::string name)
	{
		root.name = name;
	}

	HtmlBuilder& add_child(std::string child_name, std::string child_text)
	{
		HtmlElement e(child_name, child_text);
		root.elements.emplace_back(e);

		return *this;
	}

	std::string b_str() const { return root.e_str(); }
};

int main()
{
	//// <p>Hello</p>
	//auto paragraph = "Hello";
	//std::string output;
	//output += "<p>";
	//output += paragraph;
	//output += "</p>";
	////std::cout << output << std::endl;
	//printf("<p>%s</p>\n\n", paragraph);

	//// <ul><li>Hello</li><li>World</li></ul>
	//std::string list[] = { "Hello ", "World!" };
	//std::ostringstream oss;
	//oss << "<ul>\n";
	//for (auto w : list)
	//	oss << "\t<li>" << w << "</li>\n";
	//oss << "</ul>";
	//printf(oss.str().c_str());

	HtmlBuilder builder("ul");
	builder
		.add_child("li", "Hello ")
		.add_child("li", "Brave ")
		.add_child("li", "World!");

	std::cout << builder.b_str() << std::endl;

	return 0;
}