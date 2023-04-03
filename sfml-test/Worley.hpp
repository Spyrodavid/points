#pragma once

#include <cmath>

using namespace std;

class Worley
{
public:
	Worley();
	~Worley();

	float noise(float x, float y);
	float noise(float x, float y, float pow);
	void set_seed(int seed);

	
private:
	int seed;
};

Worley::Worley()
{
	seed = 0;
}

Worley::~Worley()
{
}

void Worley::set_seed(int seed)
{
	this->seed = seed;
}

float Worley::noise(float x, float y, float power)
{

	x /= 50;
	y /= 50;

	float randx;
	float randy;

	int radius = 1;

	float rx = round(x);
	float ry = round(y);

	float r1x = (rx + .5);
	float r1y = (ry + .5);
	float r2x = (rx + .5);
	float r2y = (ry - .5);
	float r3x = (rx - .5);
	float r3y = (ry + .5);
	float r4x = (rx - .5);
	float r4y = (ry - .5);

	int r1seed = floor(.5f * (r1x + r1y) * (r1x + r1y + 1) + r1y);
	int r2seed = floor(.5f * (r1x + r1y) * (r1x + r1y + 1) + r1y);
	int r3seed = floor(.5f * (r1x + r1y) * (r1x + r1y + 1) + r1y);
	int r4seed = floor(.5f * (r1x + r1y) * (r1x + r1y + 1) + r1y);

	srand(r1seed);
	
	randy = r1y + ((rand() * 1.f) / RAND_MAX) - .5;
	randx = r1x + ((rand() * 1.f) / RAND_MAX) - .5;
	float d1 = sqrt(pow(x - randx, 2) + pow(y - randy, 2));

	//cout << r1x - randx << endl;

	srand(r2seed);
	randx = r2x + rand() * 1.f / RAND_MAX - .5;
	randy = r2y + rand() * 1.f / RAND_MAX - .5;
	float d2 = sqrt(pow(x - randx, 2) + pow(y - randy, 2));

	srand(r3seed);
	randx = r3x + rand() * 1.f / RAND_MAX - .5;
	randy = r3y + rand() * 1.f / RAND_MAX - .5;
	float d3 = sqrt(pow(x - randx, 2) + pow(y - randy, 2));

	srand(r4seed);
	randx = r4x + rand() * 1.f / RAND_MAX - .5;
	randy = r4y + rand() * 1.f / RAND_MAX - .5;
	float d4 = sqrt(pow(x - randx, 2) + pow(y - randy, 2));


	//cout << x << endl << rx << endl << r1x << endl << endl;

	//float ans = min(min(min(d1, d2), d3), d4) / radius;

	float ans = min(min(min(d1, d2), d3), d4) / radius;

	return r1seed / 5.;


	if (ans < 0) {
		ans = 0;
	}
	if (ans > 1) {
		ans = 1;
	}

	if (ans > .2) {
		return 1;
	}
	else {
		return 0;
	}

	return pow(ans, power);
		
		
}



float Worley::noise(float x, float y)
{
	return Worley::noise(x, y, 1);
}