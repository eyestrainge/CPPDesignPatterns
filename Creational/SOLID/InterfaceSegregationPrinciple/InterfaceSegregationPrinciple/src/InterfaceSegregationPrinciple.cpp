#include <vector>

struct Documents;

//struct IMachine
//{
//	virtual void print(std::vector<Documents*> docs) = 0;
//	virtual void scan(std::vector<Documents*> docs) = 0;
//	virtual void fax(std::vector<Documents*> docs) = 0;
//};
//
//struct MFP : IMachine
//{
//	void print(std::vector<Documents*> docs) override;
//	void scan(std::vector<Documents*> docs) override;
//	void fax(std::vector<Documents*> docs) override;
//};



struct IPrinter
{
	virtual void print(std::vector<Documents*> docs) = 0;
};

struct IScanner
{
	virtual void scan(std::vector<Documents*> docs) = 0;
};



struct Printer : IPrinter
{
	void print(std::vector<Documents*> docs) override;
};

struct Scanner : IScanner
{
	void scan(std::vector<Documents*> docs) override;
};



struct IMachine : IPrinter, IScanner {};



struct Machine : IMachine
{
	IPrinter& printer;
	IScanner& scanner;

	Machine(IPrinter& printer, IScanner& scanner) :
		printer{ printer },
		scanner{ scanner }
	{}

	// simply proxying functionality from this decorator class
	void print(std::vector<Documents*> docs) override
	{
		printer.print(docs);
	}
	void scan(std::vector<Documents*> docs) override
	{
		scanner.scan(docs);
	}
};