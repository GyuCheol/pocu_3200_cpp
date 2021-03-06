#include <cassert>
#include <iostream>
#include <vector>

#include "Storage.h"

using namespace lab11;

class Test
{
public:
	Test()
		: a(10)
	{
	}

	int a;
};

void test2()
{
	Storage<int> storage1(100, 5);
	Storage<int> storage2(std::move(storage1));

	assert(storage1.GetSize() == 0);
	assert(storage2.GetSize() == 100);

	assert(storage2.GetData()[0] == 5);

	Storage<int> storage3(0);

	storage3 = std::move(storage2);

	assert(storage2.GetSize() == 0);
	assert(storage3.GetSize() == 100);
	assert(storage3.GetData()[0] == 5);

	Storage<int> storage4(10);

	storage4 = storage3;

	assert(storage3.GetSize() == 100);
	assert(storage3.GetData()[0] == 5);
	assert(storage4.GetSize() == 100);
	assert(storage4.GetData()[0] == 5);

	Storage<int> storage5(storage4);

	assert(storage3.GetSize() == 100);
	assert(storage3.GetData()[0] == 5);
	assert(storage5.GetSize() == 100);
	assert(storage5.GetData()[0] == 5);

	Storage<int> storage6(100);

	storage6 = std::move(storage5);
	assert(storage5.GetSize() == 0);
	assert(storage5.GetData().get() == nullptr);
	assert(storage6.GetSize() == 100);
	assert(storage6.GetData()[0] == 5);

	Test t;
	Storage<Test> storage7(100, t);
}

int main()
{
	int a = 0;
	int& b = a;

	b = 10;

	std::cout << a << "," << b << std::endl;

	std::system("pause");

	test2();

	const unsigned int SIZE = 10000;

	Storage<int> storage1(SIZE);

	const std::unique_ptr<int[]>& data1 = storage1.GetData();

	for (int i = 0; i < SIZE; ++i)
	{
		assert(data1[i] == 0);
	}


	Storage<int> storage2(SIZE, 100);
	const std::unique_ptr<int[]>& data2 = storage2.GetData();

	for (int i = 0; i < SIZE; ++i)
	{
		assert(data2[i] == 100);
	}

	// using move constructor
	Storage<int> storage3(SIZE, 50);
	const std::unique_ptr<int[]>& data3 = storage3.GetData();

	assert(storage3.GetSize() == SIZE);

	for (int i = 0; i < SIZE; ++i)
	{
		assert(data3[i] == 50);
	}

	Storage<int> storage3Copy(std::move(storage3));
	const std::unique_ptr<int[]>& data3Copy = storage3Copy.GetData();

	assert(storage3Copy.GetSize() == SIZE);
	for (int i = 0; i < SIZE; ++i)
	{
		assert(data3Copy[i] == 50);
	}

	assert(storage3.GetData() == nullptr);
	assert(storage3.GetSize() == 0);

	Storage<char> storage4(SIZE, 'f');
	const std::unique_ptr<char[]>& data4 = storage4.GetData();

	assert(storage4.GetSize() == SIZE);

	for (int i = 0; i < SIZE; ++i)
	{
		assert(data4[i] == 'f');
	}

	Storage<char> storage4Copy = std::move(storage4);
	const std::unique_ptr<char[]>& data4Copy = storage4Copy.GetData();

	assert(storage4Copy.GetSize() == SIZE);

	for (int i = 0; i < SIZE; ++i)
	{
		assert(data4Copy[i] == 'f');
	}

	assert(storage4.GetData() == nullptr);
	assert(storage4.GetSize() == 0);

	const unsigned int SIZE2 = 5000;

	Storage<int> storage5(SIZE2);
	const std::unique_ptr<int[]>& data5 = storage5.GetData();

	for (int i = 0; i < SIZE2; ++i)
	{
		storage5.Update(i, SIZE2 - i - 1);
		assert(data5[i] == SIZE2 - i - 1);
	}

	return 0;
}