# 智能指针

## 1、概念

C++中引入智能指针的主要目的是为了解决**内存管理**的问题，传统的指针（裸指针）在使用时需要<u>手动分配和释放内存</u>，容易出现**内存泄漏**和**悬挂指针**等问题。智能指针通过封装裸指针，并提供自动内存管理功能，使得内存资源可以更安全、高效地管理。

## 2、内存泄漏

有人说，我每次记得将**new**过的指针**delete**，是不是就可以不使用智能指针了呢？智能指针怪麻烦的！但有些时候指针不是你想delete他就真的delete了

我举个例子：

```c
#include <iostream>
#include <string>
#include <memory>

using namespace std;


// 1、动态分配内存，没有释放就return
void memoryLeak1() {
	string *str = new string("动态分配内存！");
	return;
}

// 2、动态分配内存，虽然有些释放内存的代码，但是被半路截胡return了
int memoryLeak2() {
	string *str = new string("内存泄露！");

	// ...此处省略一万行代码

	// 发生某些异常，需要结束函数
	if (1) {
		return -1;
	}
	// 另外，使用try、catch结束函数，也会造成内存泄漏！
	

	delete str;	// 虽然写了释放内存的代码，但是遭到函数中段返回，使得指针没有得到释放
	return 1;
}


int main(void) {

	memoryLeak1();

	memoryLeak2();

	return 0;
} 

```

对于第二种内存泄漏，在代码中发现异常需要结束函数，后面的delete并没有执行，此时指针并没有释放，即会导致内存泄漏。

## 3、智能指针原理

智能指针本质是一个**类模板**它可以创建任意的类型的指针对象，当智能指针对象使用完后***\*，对象就会自动调用析构函数去释放该指针所指向的空间\****。如下所示：

![屏幕截图 2024-06-10 121244](https://github.com/Scholar618/C_CPP_Learning/blob/main/imgs/smartPoint1.png)

这样即可自己写一个简易的智能指针：

```c
#pragma once
#include <iostream>
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

```

测试：

```c
#include "smartpoint.h"
void test1() 
{
	smartptr<int> ptr1;
	smartptr<double> ptr2;
	smartptr<bool> ptr3;
}

int main()
{
	test1();
	return 0;
}
```

结果：

![屏幕截图 2024-06-10 121959](https://github.com/Scholar618/C_CPP_Learning/blob/main/imgs/smartPoint2.png)

## 4、常见智能指针

### 1、auto_ptr

std::auto_ptr是C++98标准中提供的智能指针，它是独占式智能指针，已经过时，在这里不深究

### 2、unique_ptr

std::unique_ptr是C++11标准引入的智能指针，其核心思想是**独占所有权**（exclusive ownership）和资源管理的责任。

核心思想（**禁止拷贝和可以Move**）：

- **独占所有权**：std::unique_ptr独占所管理的指针资源，**同一时间只能有一个std::unique_ptr拥有该资源**。当std::unique_ptr被销毁或转移所有权时，它会自动释放所管理的资源，确保资源在适当的时候被正确释放，避免资源泄漏。
- **确保资源的释放**：std::unique_ptr通过在析构函数中自动调用delete来释放所管理的资源。这意味着，无论是通过正常的控制流还是异常的控制流，只要std::unique_ptr被销毁，资源都会得到释放，避免了手动释放资源的繁琐和可能的遗漏。
- **禁止拷贝**：std::unique_ptr禁止拷贝构造函数和拷贝赋值运算符的使用，以确保同一时间只有一个std::unique_ptr拥有资源的所有权。这样可以防止多个智能指针同时管理同一块资源，避免了资源的重复释放和悬挂指针的问题。
- **支持移动Move语义**：std::unique_ptr支持移动构造函数和移动赋值运算符，**允许资源的所有权从一个std::unique_ptr对象转移到另一个对象**，避免了资源的不必要拷贝。

unique_ptr创建：

```c
int main()
{
	{
	// std::unique_ptr<Entity> entity = new Entity(); // 错误
	// std::unique_ptr<Entity> entity(new Entity()); // 普通指针使用方法
		std::unique_ptr<Entity> entity = std::make_unique<Entity>(); // 最好使用这种
    // std::unique_ptr<Entity> e0 = entity; // 错误
		entity->Print();
	}

	return 0;
}
```

```c
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

```

离开作用域前，打印Create Entity!；离开作用域后，打印Destroyed Entity!

查看unique_ptr函数，会发现拷贝和构造函数都被删除，这是编译器防止程序员**自掘坟墓**，做出的提示！

![屏幕截图 2024-06-10 132314](https://github.com/Scholar618/C_CPP_Learning/blob/main/imgs/smartPoint3.png)

### 3、shared_ptr

使用unique_ptr最大的缺点即是不能拷贝指针，所以，如果你喜欢**分享**，可以使用shared_ptr来弥补缺陷！

核心思想：

> 当复制或拷贝时，**引用计数**加1，当智能指针析构时，**引用计数**减1，如果计数为零，代表已经没有指针指向这块内存，那么我们就释放它！这就是 shared_ptr 采用的策略！

```c
int main()
{
	// test1();
	
	{
		std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>();
		std::shared_ptr<Entity> e0 = sharedEntity; // 正确，增加引用计数
		entity->Print();
	}


	return 0;
}
```



### 4、weak_ptr

可以与shared一起使用，对于shared来说，它不会增加计数器，

```c
int main()
{
	{
		std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>();
		std::weak_ptr<Entity> e0 = sharedEntity; // 不会增加计数器
		entity->Print();
	}


	return 0;
}
```

常见的智能指针即这几种，后面可能会手写智能指针，看后面更新吧！
