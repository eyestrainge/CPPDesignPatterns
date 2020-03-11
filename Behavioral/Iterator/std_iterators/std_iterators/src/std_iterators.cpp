#include <string>
#include <vector>
#include <iostream>
using namespace std;

void std_iterators()
{
	vector<string> games{ "Dark Souls", "Dark Souls 2", "Bloodborne", "Dark Souls 3", "Sekiro" };
	vector<string>::iterator it = games.begin();
	cout << "Game: " << *it << endl;

	++it;
	it->append(": Scholar of the First Sin");
	cout << "Game: " << *it << endl;

	while(++it != games.end())
		cout << "Game: " << *it << endl;

	for (auto ri = rbegin(games); ri != rend(games); ++ri)
	{
		cout << *ri;
		if (ri + 1 != rend(games))
			cout << ", ";
	}
	cout << endl;

	/*vector<string>::const_reverse_iterator cri = crbegin(games);
	*cri += ": Shadows Die Twice";
	vector<string>::reverse_iterator cri = crbegin(games);
	*cri += ": Shadows Die Twice";*/
}

int main()
{
	std_iterators();

	return 0;
}