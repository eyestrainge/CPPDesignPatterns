#include <string>
#include <vector>
#include <sstream>
#include <memory>
#include <iostream>
using namespace std;

enum class OutputFormat
{
	Markdown, Html
};

struct ListStrategy
{
	virtual ~ListStrategy() = default;
	virtual void start(ostringstream& oss) = 0;
	virtual void end(ostringstream& oss) = 0;
	virtual void add_list_item(ostringstream& oss, const string& item) = 0;
};

struct MarkdownListStrategy : ListStrategy
{
	void start(ostringstream& oss) override {}
	void end(ostringstream& oss) override {}
	void add_list_item(ostringstream& oss, const string& item) override
	{
		oss << " * " << item << "\n";
	}
};

struct HtmlListStrategy : ListStrategy
{
	void start(ostringstream& oss) override
	{
		oss << "<ul>" << "\n";
	}
	void end(ostringstream& oss) override
	{
		oss << "</ul>" << "\n";
	}
	void add_list_item(ostringstream& oss, const string& item) override
	{
		oss << "<li>" << item << "</li>" << "\n";
	}
};

struct TextProcessor
{
	void clear()
	{
		oss.str("");
		oss.clear();
	}

	string str() const { return oss.str(); }

	void append_list(const vector<string>& items)
	{
		list_strategy->start(oss);
		for (auto& item : items)
			list_strategy->add_list_item(oss, item);
		list_strategy->end(oss);
	}

	void set_output_format(OutputFormat format)
	{
		switch (format)
		{
		case OutputFormat::Markdown:
			list_strategy = make_unique<MarkdownListStrategy>();
			break;
		case OutputFormat::Html:
			list_strategy = make_unique<HtmlListStrategy>();
			break;
		}
	}

private:
	ostringstream oss;
	unique_ptr<ListStrategy> list_strategy;
};

int main()
{
	TextProcessor tp;
	tp.set_output_format(OutputFormat::Markdown);
	tp.append_list({ "foo", "bar", "baz" });
	cout << tp.str() << endl;

	tp.clear();
	tp.set_output_format(OutputFormat::Html);
	tp.append_list({ "foo", "bar", "baz" });
	cout << tp.str() << endl;

	return 0;
}