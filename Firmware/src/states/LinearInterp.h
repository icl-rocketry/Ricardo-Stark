#pragma once

template<typename T>
class LinearInterp
{
    public:
        LinearInterp(){};

        T calculate(T x1, T y1, T x2, T y2,T val)
        {
            return ((y2-y1)/(x2-x1))*(val-x1) + y1 ;
        }

};