#pragma once

template <typename T>
T exp(T x, unsigned degree) 
{
    return (degree > 0) ? x * exp(x, degree - 1) : 1;
}

inline unsigned nearest_multiple(int x, int multiple)
{
    x = ((x % multiple == 0) ? 0 : multiple) + x - x % multiple;
    return x;
};