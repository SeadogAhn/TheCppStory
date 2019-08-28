#include "SmartPointer.h"

#include <iostream>
#include <string>

int main()
{
	message("create unique pointer one");
	std::unique_ptr<std::string> unique1(new std::string("unique one"));
	disp(unique1);

	message("make_unique two");
	auto unique2 = notstd::make_unique<std::string>("unique two");
	disp(unique1);
	disp(unique2);

	message("reset a to three");
	unique1.reset(new std::string("three"));
	disp(unique1);
	disp(unique2);

	message("move unique2 to unique3");
	auto unique3 = std::move(unique2);
	disp(unique1);
	disp(unique2);
	disp(unique3);

	message("reset unique1");
	unique1.reset();
	disp(unique1);
	disp(unique2);
	disp(unique3);

	message("reset unique3");
	unique3.reset();
	disp(unique1);
	disp(unique2);
	disp(unique3);

	message("end of scope");

	message("create shared_ptr");
	auto shared = std::make_shared<std::string>("thing");

	message("make several copies");
	auto c1 = shared;
	auto c2 = shared;
	auto c3 = shared;
	auto c4 = shared;
	auto c5 = shared;

	message("reference count is now 6");
	disp(shared);

	message("create weak_ptr");
	auto w1 = std::weak_ptr<std::string>(shared);
	disp(w1);

	message("destroy copies");
	c1.reset();
	c2.reset();
	c3.reset();
	c4.reset();
	c5.reset();

	message("reference count should be 1");
	disp(shared);

	message("check weak pointer");
	disp(w1);

	message("destroy shared");
	shared.reset();

	message("check weak pointer");
	disp(w1);

	message("end of scope");
}
