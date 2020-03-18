#include "Model.hpp"

int main()
{
	Paragraph p{ "Here are some colors:" };
	ListItem red{ "Red" };
	ListItem green{ "Green" };
	ListItem blue{ "Blue" };
	List colors{ red, green, blue };

	vector<Element*> document{ &p, &colors };
	ostringstream oss;
	for_each(document.begin(), document.end(),
		[&](const Element* e) { e->print(oss); });

	cout << oss.str() << "\n";

	return 0;
}