#include <stack>
#include <iostream>

int main()
{
	std::stack<int> s;
	s.push(123);
	s.push(124);

	auto x = s.top();
	std::cout << x << std::endl;

	s.pop();
	x = s.top();
	std::cout << x << std::endl;

	/*s.pop();
	x = s.top();
	std::cout << x << std::endl;*/

	return 0;
}