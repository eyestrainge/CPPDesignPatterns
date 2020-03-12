#include "ChatRoom.h"
#include "Person.h"

int main()
{
	ChatRoom room;

	auto john = room.join(Person{ "John" });
	auto jane = room.join(Person{ "Jane" });

	john->say("Hi room");
	jane->say("Oh, hey John");

	auto jack = room.join(Person{ "Jack" });
	jack->say("Hi everyone!");

	jane->pm("Jack", "Glad you could join us, Jack");

	return 0;
}