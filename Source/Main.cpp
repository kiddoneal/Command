#include <iostream>
#include <memory>
#include <cassert>
#include "Command.h"
#include "Void.h"
#include <cassert>

struct Counter
{
	// void return types must use Poco::Void()!
	Poco::Void add(int i) { count += i; return Poco::Void(); }
	Poco::Void sub(int i) { count -= i; return Poco::Void(); }

	int count = 0;
};

const int count = 100;
const int val = 10;
const int count2 = 40;

int main (int argc, char* argv[])
{
	Counter test;

	Commander com;

	for (int i = 0; i < count; i++)
	{
		// a command must have a do and an undo function pair
		com.addDo(&test, &Counter::add, true, val);
		com.addUndo(&test, &Counter::sub, val);
	}
	assert(test.count == val * count);

	com.undoAll();
	assert(test.count == 0);

	com.redoAll();
	assert(test.count == val * count);

	for (int i = 0; i < count2; i++)
		com.undoLast();
	assert(test.count == (val * count) - (count2 * val));

	com.redoAll();
	assert(test.count == val * count);

    return 0;
}
