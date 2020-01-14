#include <string>
#include <vector>
#include <iostream>
#include <fstream>



struct Journal
{
	std::string title;
	std::vector<std::string> entries;

	explicit Journal(const std::string& title) :
		title(title) {}

	void add(const std::string& entry)
	{
		entries.push_back(entry);
	}
};



struct PersistanceManager
{
	void save(const Journal& j, const std::string& filename)
	{
		std::ofstream ofs(filename);

		ofs << j.title << ":\n";
		for (const auto& entry : j.entries)
			ofs << "  " << entry << "\n";

		ofs.close();
	}
};



int main()
{
	Journal journal("Games");
	journal.add("Bloodborne");
	journal.add("Sekiro");
	journal.add("Dark Souls");

	PersistanceManager pm;
	pm.save(journal, "Platinums.txt");
	std::cout << "\nFile saved.\n\n" << std::endl;

	return 0;
}
