#pragma once
#include <math.h>
class FuzzySet
{
public:
	float FuzzyGrade(float value, float x0, float x1);
	float FuzzyTriangle(float value, float x0, float x1, float x2);
	float FuzzyTrapezoid(float value, float x0, float x1, float x2, float x3);

	float FuzzyAND(float A, float B);
	float FuzzyOR(float A, float B);
	float FuzzyNOT(float A);
};
