#include "Vector.hpp"
#include <iostream>
#include <string>

using namespace std;

struct Score {
	double Korean;
	double English;
	double Math;
};

ostream& operator<<(ostream& os, const Score& s)
{
	os << s.Korean << ',' << s.English << ',' << s.Math;
	return os;
}

template <typename Container>
void print(const Container& c, const string& str = "")
{
	cout << str << ':';
	for (const auto& v : c) {
		cout << v << ',';
	}
	cout << endl;
}

int main()
{
	Vec<int> vec1{ 1,2,3,4,5 };
	Vec<int> vec2{ 6,7,8,9,10 };

	print(vec1, "vec1");
	print(vec2, "vec2");

	cout << vec1.size() << ',' << vec1.capacity() << endl;
	cout << vec2.size() << ',' << vec2.capacity() << endl;

	copy(vec2.begin(), vec2.end(), std::back_inserter(vec1));
	print(vec1, "vec1");
	cout << vec1.size() << ',' << vec1.capacity() << endl;

	vec1 = move(vec2);
	print(vec1, "vec1");
	print(vec2, "vec2");
	cout << vec1.size() << ',' << vec1.capacity() << endl;
	cout << vec2.size() << ',' << vec2.capacity() << endl;

	Vec<int> vec3{ move(vec1) };
	print(vec1, "vec1");
	print(vec3, "vec3");
	cout << vec1.size() << ',' << vec1.capacity() << endl;
	cout << vec3.size() << ',' << vec3.capacity() << endl;

	vec3.push_back(1);
	cout << vec3.size() << ',' << vec3.capacity() << endl;

	for (int i = 0; i < 20; ++i) {
		vec3.push_back(i);
		cout << vec3.size() << ',' << vec3.capacity() << endl;
	}

	Vec<Score> vec4{ {10,20,30}, {11,21,32}, {12,22,33} };
	print(vec4, "vec4");
}
