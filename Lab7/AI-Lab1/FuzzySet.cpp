#include "FuzzySet.h"

float FuzzySet::FuzzyGrade(float value, float x0, float x1)
{
	float result = 0;
	float x = value;

	if (x <= x0)
	{
		result = 0;
	}
	else if (x > x1)
	{
		result = 1;
	}
	else
	{
		result = ((x - x0) / (x1 - x0));
	}
	return result;
}

float FuzzySet::FuzzyTriangle(float value, float x0, float x1, float x2)
{
	float result = 0;
	float x = value;

	if ((x <= x0) || (x >= x2))
	{
		result = 0;
	}
	else if (x == x1)
	{
		result = 1;
	}
	else if ((x > x0) && (x < x1))
	{
		result = ((x - x0) / (x1 - x0));
	}
	else
	{
		result = ((x2 - x) / (x2 - x1));
	}
	return result;
}

float FuzzySet::FuzzyTrapezoid(float value, float x0, float x1, float x2, float x3)
{
	float result = 0;
	float x = value;

	if ((x <= x0) || (x >= x3))
	{
		result = 0;
	}
	else if ((x >= x1) && (x <= x2))
	{
		result = 1;
	}
	else if ((x > x0) && (x < x1))
	{
		result = ((x - x0) / (x1 - x0));
	}
	else
	{
		result = ((x3 - x) / (x3 - x2));
	}
	return result;
}

float FuzzySet::FuzzyAND(float A, float B)
{
	return fmin(A, B);
}

float FuzzySet::FuzzyOR(float A, float B)
{
	return fmax(A, B);
}

float FuzzySet::FuzzyNOT(float A)
{
	return 1.0f - A;
}



