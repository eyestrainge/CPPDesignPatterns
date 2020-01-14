#include "DrinkFactory.h"



int main()
{
	DrinkFactory df;
	df.make_drink("tea");
	df.make_drink("coffee");

	DrinkWithVolumeFactory dvf;
	dvf.make_drink("tea");

	return 0;
}
