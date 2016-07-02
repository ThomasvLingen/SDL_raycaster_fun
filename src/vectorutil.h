#ifndef VECTORUTIL_H
#define VECTORUTIL_H

#include <cmath>

class VectorUtil
{
public:
    VectorUtil();

    static void rotate_vector(double* vector_x, double* vector_y, double radians);
};

#endif // VECTORUTIL_H
