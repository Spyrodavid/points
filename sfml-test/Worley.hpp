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
	float r5x = (rx + .5);
	float r5y = (ry + .5);
	float r6x = (rx + .5);
	float r6y = (ry + .5);
	float r7x = (rx + .5);
	float r7y = (ry - .5);
	float r8x = (rx - .5);
	float r8y = (ry + .5);
	float r9x = (rx - .5);
	float r9y = (ry - .5);


	double min_distance = 9999;
	for (size_t ix = -1; ix <= 1; ix++)
	{
		for (size_t iy = -1; iy <= 1; iy++)
		{
			float nx = rx + ix;
			float ny = ry + iy;

			int seed = floor(.5f * (nx + ny) * (nx + ny + 1) + ny);
			srand(seed);

			randx = nx + ((rand() * 1.f) / RAND_MAX);
			randy = ny + ((rand() * 1.f) / RAND_MAX);

			min_distance = min(sqrt(pow(nx - randx, 2) + pow(ny - randy, 2)) , min_distance);
		}
	}


	int r1seed = floor(.5f * (r1x + r1y) * (r1x + r1y + 1) + r1y);
	int r2seed = floor(.5f * (r2x + r2y) * (r2x + r2y + 1) + r2y);
	int r3seed = floor(.5f * (r3x + r3y) * (r3x + r3y + 1) + r3y);
	int r4seed = floor(.5f * (r4x + r4y) * (r4x + r4y + 1) + r4y);

	srand(r1seed);
	rand();
	randx = r1x + ((rand() * 1.f) / RAND_MAX) - .5;
	randy = r1y + ((rand() * 1.f) / RAND_MAX) - .5;
	float d1 = sqrt(pow(x - randx, 2) + pow(y - randy, 2));

	srand(r2seed);
	rand();
	randx = r2x + rand() * 1.f / RAND_MAX - .5;
	randy = r2y + rand() * 1.f / RAND_MAX - .5;
	float d2 = sqrt(pow(x - randx, 2) + pow(y - randy, 2));

	srand(r3seed);
	rand();
	randx = r3x + rand() * 1.f / RAND_MAX - .5;
	randy = r3y + rand() * 1.f / RAND_MAX - .5;
	float d3 = sqrt(pow(x - randx, 2) + pow(y - randy, 2));

	srand(r4seed);
	rand();
	randx = r4x + rand() * 1.f / RAND_MAX - .5;
	randy = r4y + rand() * 1.f / RAND_MAX - .5;
	float d4 = sqrt(pow(x - randx, 2) + pow(y - randy, 2));


	//cout << x << endl << rx << endl << r1x << endl << endl;

	//float ans = min(min(min(d1, d2), d3), d4) / radius;

	float ans = min(min(min(d1, d2), d3), d4) / radius;



	if (ans < 0) {
		ans = 0;
	}
	if (ans > 1) {
		ans = 1;
	}

	if (ans < .05) {
		return 1;
	}
	

	return pow(ans, power);
		
		
}



float Worley::noise(float x, float y)
{
	return Worley::noise(x, y, 1);
}