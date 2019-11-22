#include <cstdio>
#include <cmath>
#include <ctime>
#include <random>

using namespace std;

double nextTime(double rnd, double rateParameter)
{
    return -log(1.0 - rnd) / rateParameter;
}

int main()
{
	int i;
	double rate = 0.02;
	random_device rd;
	mt19937 generator(rd());
	uniform_real_distribution<> distribution(0.0,1.0);

	for (i=0 ; i< 10 ; i++ ) {
		printf("%f\n", nextTime(distribution(generator), rate));
	}

	return 0;
}
