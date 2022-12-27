#pragma once

#include "DynamicArray.h"

template <typename INF> class Matrix : public DynamicArray<INF>
{
private:
    unsigned _width;
    unsigned _height;

public:
    Matrix() : DynamicArray<INF>(0) 
    {
        _width = 0;
        _height = 0;
    }

    Matrix(unsigned width, unsigned height) : DynamicArray<INF>(width * height)
    {
        _width = width;
        _height = height;
    }

    INF& operator ()(unsigned row, unsigned col)
    {
        return DynamicArray<INF>::operator[](row * _width + col);
    }

    unsigned GetWidth()
    {
        return _width;
    }

    unsigned GetHeight()
    {
        return _height;
    }

    int Resize(unsigned width, unsigned height)
    {
        _width = width;
        _height = height;
        return DynamicArray<INF>::Resize(width * height);
    }

    void FillRandom(unsigned width, unsigned height, INF seed)
    {
        srand((unsigned)time(NULL));
        unsigned size = width * height;
        for (unsigned i = 0; i < size; ++i)
        {
            INF val = rand() * seed;
            DynamicArray<INF>::operator[](i) = val ? val : val + 1;
        }
    }

    void FillFixed(unsigned width, unsigned height, INF val)
    {
        unsigned size = width * height;
        for (unsigned i = 0; i < size; ++i)
        {
            DynamicArray<INF>::operator[](i) = val;
        }
    }
};