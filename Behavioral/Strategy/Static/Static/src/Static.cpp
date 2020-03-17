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

template <typename LS>
struct TextProcessor
{
	explicit TextProcessor() :
		list_strategy{ make_unique<LS>() }
	{}

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

private:
	ostringstream oss;
	unique_ptr<LS> list_strategy;
};

int main()
{
	TextProcessor<MarkdownListStrategy> tpm;
	tpm.append_list({ "foob", "bar", "baz" });
	cout << tpm.str() << endl;

	TextProcessor<HtmlListStrategy> tph;
	tph.append_list({ "foob", "bar", "baz" });
	cout << tph.str() << endl;

	return 0;
}