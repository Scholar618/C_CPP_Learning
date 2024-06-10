#pragma once
#include <iostream>
#include <memory>
template<class T>
class smartptr
{
public:
	smartptr(T* ptr = nullptr)
		:_ptr(ptr)
	{};
	~smartptr()
	{
		std::cout << "ptr delete..." << std::endl;
		if (_ptr)
			delete _ptr;

	}

private:
	T* _ptr;
};

class Entity
{
public:
	Entity()
	{
		std::cout << "Create Entity!" << std::endl;
	}
	~Entity()
	{
		std::cout << "Destroyed Entity!" << std::endl;
	}

	void Print() {};
};
