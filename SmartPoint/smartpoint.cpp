#include "smartpoint.h"
void test1() 
{
	smartptr<int> ptr1;
	smartptr<double> ptr2;
	smartptr<bool> ptr3;
}

int main()
{
	// test1();
	
	{
	// std::unique_ptr<Entity> entity = new Entity(); // 错误
	// std::unique_ptr<Entity> entity(new Entity()); // 普通指针使用方法
		std::unique_ptr<Entity> entity = std::make_unique<Entity>(); // 最好使用这种
	// std::unique_ptr<Entity> e0 = entity; // 错误

		std::shared_ptr<Entity> sharedEntity = std::make_shared<Entity>();
		std::weak_ptr<Entity> e0 = sharedEntity; // 不会增加计数器
		entity->Print();
	}


	return 0;
}