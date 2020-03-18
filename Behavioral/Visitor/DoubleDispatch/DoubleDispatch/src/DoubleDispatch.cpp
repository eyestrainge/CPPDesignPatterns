#include "Model.hpp"

struct HtmlVisitor : Visitor
{
	void visit(const Paragraph& p) override
	{
		oss << "<p>" << p.text << "</p>\n";
	}	
	void visit(const ListItem& li) override
	{
		oss << "<li>" << li.text << "</li>\n";
	}
	void visit(const List& l) override
	{
		oss << "<ul>\n";
		for (auto x : l)
			x.accept(*this);
		oss << "</ul>\n";
	}

	string str() const override
	{
		return oss.str();
	}

private:
	ostringstream oss;
};

int main()
{
	Paragraph p{ "Here are some colors:" };
	ListItem red{ "Red" };
	ListItem green{ "Green" };
	ListItem blue{ "Blue" };
	List colors{ red, green, blue };

	vector<Element*> document{ &p, &colors };
	HtmlVisitor v;

	for (auto x : document)
		x->accept(v);

	cout << v.str() << endl;

	return 0;
}