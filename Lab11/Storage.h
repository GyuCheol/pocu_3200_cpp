#pragma once

#include <memory>

namespace lab11
{
	template<typename T>
	class Storage
	{
	public:
		Storage(unsigned int length);
		Storage(unsigned int length, const T& initialValue);
		Storage(Storage<T>&& other);
		Storage(const Storage<T>& other);

		Storage<T>& operator=(Storage<T>&& other);
		Storage<T>& operator=(Storage<T>& other);

		bool Update(unsigned int index, const T& data);
		const std::unique_ptr<T[]>& GetData() const;
		unsigned int GetSize() const;

	private:
		std::unique_ptr<T[]> mDataPtr;
		unsigned int mSize;
		
	};

	template<typename T> Storage<T>::Storage(unsigned int length)
		: mSize(length)
	{
		mDataPtr.reset(new T[length]);

		std::memset(mDataPtr.get(), 0, sizeof(T) * length);
	}

	template<typename T> Storage<T>::Storage(unsigned int length, const T& initialValue)
		: mSize(length)
	{
		mDataPtr.reset(new T[length]);

		for (size_t i = 0; i < length; i++)
		{
			mDataPtr[i] = initialValue;
		}
	}

	template<typename T> Storage<T>::Storage(Storage<T>&& other)
	{
		if (this != &other)
		{
			mSize = other.mSize;
			other.mSize = 0;
			mDataPtr = std::move(other.mDataPtr);
		}
	}

	template<typename T> Storage<T>::Storage(const Storage<T>& other)
		: mSize(other.mSize)
	{
		mDataPtr.reset(new T[mSize]);

		for (size_t i = 0; i < other.mSize; i++)
		{
			mDataPtr[i] = other.mDataPtr[i];
		}
	}

	template<typename T> Storage<T>& Storage<T>::operator=(Storage<T>&& other)
	{
		if (this != &other)
		{
			mSize = other.mSize;
			other.mSize = 0;
			mDataPtr = std::move(other.mDataPtr);
		}

		return *this;
	}

	template<typename T>
	Storage<T>& Storage<T>::operator=(Storage<T>& other)
	{
		if (this != &other)
		{
			mSize = other.mSize;
			mDataPtr.reset(new T[mSize]);

			for (size_t i = 0; i < other.mSize; i++)
			{
				mDataPtr[i] = other.mDataPtr[i];
			}
		}

		return *this;
	}

	template<typename T>
	bool Storage<T>::Update(unsigned int index, const T& data)
	{
		if (index >= mSize)
		{
			return false;
		}

		mDataPtr[index] = data;

		return true;
	}

	template<typename T>
	const std::unique_ptr<T[]>& Storage<T>::GetData() const
	{
		return mDataPtr;
	}

	template<typename T>
	unsigned int Storage<T>::GetSize() const
	{
		return mSize;
	}
	
}