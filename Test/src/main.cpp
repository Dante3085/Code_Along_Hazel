
// ----Bitfield stuff----

//#include <iostream>
//
//#define BIT(x) (1 << x)
//
//enum EventCategory
//{
//	None = 0,
//	EventCategoryApplication = BIT(0),
//	EventCategoryInput = BIT(1),
//	EventCategoryKeyboard = BIT(2),
//	EventCategoryMouse = BIT(3),
//	EventCategoryMouseButton = BIT(4)
//};
//
//bool IsInCategory(int categoryFlags, EventCategory category)
//{
//	return categoryFlags & category;
//}
//
//int main()
//{
//	std::cout << std::boolalpha << IsInCategory(3, EventCategoryApplication) << std::endl;
//	std::cout << std::boolalpha << IsInCategory(16, EventCategoryMouseButton) << std::endl;
//	std::cin.get();
//}

// -----Smart Pointer-----
// Smart Pointers automate usage of new and delete.

#include <memory>
#include <iostream>

struct Point2D
{
	int x;
	int y;

	Point2D(int x = 0, int y = 0)
		: x(x), y(y)
	{
		std::cout << "Constructed" << std::endl;
	}

	~Point2D()
	{
		std::cout << "Deleted" << std::endl;
	}
};

int main()
{
	{
		// Heap allocated Point2D gets destroyed when going out of this scope.
		std::unique_ptr<Point2D> uniquePoint2D = std::make_unique<Point2D>();
	}

	{
		std::shared_ptr<Point2D> shared1;
		{
			// Heap allocated Point2D gets destroyed when all the shared_ptrs pointing to it
			// have gone out of scope. When reference count is 0.
			std::shared_ptr<Point2D> shared2 = std::make_shared<Point2D>();
			shared1 = shared2;

			// Weak Pointers to not increase reference count. They dont have shared ownership.
			std::weak_ptr<Point2D> weakPtr = shared2;
		}
	}
	std::cout << "Hello World" << std::endl;
}