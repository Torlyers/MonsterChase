#pragma once
#include <nmmintrin.h>
#include <math.h>

#define PI 3.14159265f
#define EPSILON 0.000001f

inline bool IsFloatZero(float f)
{
	return fabs(f) < EPSILON;
}

//#define _MM_SHUFFLE(fp3, fp2, fp1, fp0) (((fp3) << 6) | ((fp2) << 4) | ((fp1) >> 2) | (fp0))