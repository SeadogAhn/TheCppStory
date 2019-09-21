#pragma once
#include <string>
#include <memory>
#include <iostream>
#include <cstdio>

using namespace std;

void message(const char * s) {
	printf("\n%s\n", s);
	fflush(stdout);
}

// display object value from unique_ptr
void disp(std::unique_ptr<std::string> & o) {
	if (o) puts(o->c_str());
	else puts("null");
	fflush(stdout);
}

// display object value from shared_ptr (with reference count)
void disp(const std::shared_ptr<std::string> & o) {
	if (o) printf("%s (%ld)\n", o->c_str(), o.use_count());
	else puts("[null]");
	fflush(stdout);
}

// display object value from weak_ptr (with reference count)
void disp(const std::weak_ptr<std::string> & o) {
	// must get a lock to use a weak_ptr
	size_t count = o.use_count(); // weak pointer count
	auto sp = o.lock();
	if (sp) printf("%s (w:%ld s:%ld)\n", sp->c_str(), (long)count, sp.use_count());
	else puts("[null]");
	fflush(stdout);
}

namespace notstd {
	template <typename T, typename P>
	std::unique_ptr<T> make_unique(P initializer) {
		return std::unique_ptr<T>(new T(initializer));
	}
}

void deleter(const std::string * o) {
	printf("deleter: ");
	if (o) printf("%s\n", o->c_str());
	else printf("[null]\n");
	fflush(stdout);
	delete o;
}
