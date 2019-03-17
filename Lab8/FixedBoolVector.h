#pragma once

#include <cstdint>

namespace lab8 {

	template <size_t N>
	class FixedVector<bool, N> {
	public:
		FixedVector();
		~FixedVector();

		bool Add(bool value);
		bool Remove(bool find);
		const bool Get(unsigned int index);
		int GetIndex(bool find);
		size_t GetSize();
		size_t GetCapacity();

		bool operator[](int index);

	private:
		enum { BIT_SIZE = sizeof(uint32_t) * 8};

		uint32_t* mValues;
		size_t mArraySize;
		size_t mSize = 0;
	};

	template <size_t N>
	bool FixedVector<bool, N>::Add(bool value)
	{
		
		if (mSize == N) 
		{
			return false;
		}
		
		int pos = mSize / BIT_SIZE;
		int id = mSize % BIT_SIZE;

		if (value == true)
		{
			mValues[pos] |= (1 << id);
		}
		else
		{
			mValues[pos] &= ~(1 << id);
		}

		mSize++;

		return true;
	}

	template <size_t N>
	bool FixedVector<bool, N>::operator[](int index)
	{
		return Get(index);
	}

	template <size_t N>
	bool FixedVector<bool, N>::Remove(bool value)
	{
		int index = GetIndex(value);

		if (index == -1)
		{
			return false;
		}

		int pos = index / BIT_SIZE;
		int id = index % BIT_SIZE;

		uint32_t left = mValues[pos] % (1 << id);
		uint32_t right = mValues[pos] >> (id + 1);

		mValues[pos] = left + (right << id);
		if (pos < (mArraySize - 1))
		{
			mValues[pos] |= (mValues[pos + 1] % 2) << (BIT_SIZE - 1);
		}

		for (size_t i = pos + 1; i < mArraySize; i++)
		{
			mValues[i] = mValues[i] >> 1;
			if (i < (mArraySize - 1))
			{
				mValues[i] |= (mValues[i + 1] % 2) << (BIT_SIZE - 1);
			}
		}

		mSize--;

		return true;
	}

	template <size_t N>
	const bool FixedVector<bool, N>::Get(unsigned int index)
	{
		int pos = index / BIT_SIZE;
		int id = index % BIT_SIZE;

		return mValues[pos] & (1 << id);
	}

	template <size_t N>
	int FixedVector<bool, N>::GetIndex(bool find)
	{
		for (size_t i = 0; i < mSize; i++)
		{
			if (find == Get(i))
			{
				return i;
			}
		}

		return -1;
	}

	template <size_t N>
	size_t FixedVector<bool, N>::GetSize()
	{
		return mSize;
	}

	template <size_t N>
	size_t FixedVector<bool, N>::GetCapacity()
	{
		return N;
	}

	template <size_t N>
	FixedVector<bool, N>::FixedVector()
	{
		mArraySize = N / BIT_SIZE;

		if (N % BIT_SIZE != 0)
		{
			mArraySize++;
		}

		mValues = new uint32_t[mArraySize] { 0, };
	}

	template <size_t N>
	FixedVector<bool, N>::~FixedVector()
	{
		delete[] mValues;
	}

}

