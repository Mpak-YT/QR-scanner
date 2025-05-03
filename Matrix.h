#pragma once
#include <iostream>
//#include <stdexcept>

template <typename T>
class Matrix {
private:
    unsigned short width;
    unsigned short height;
    T** m;
    void clear() 
    {
        if (m != nullptr) 
        {
            for (unsigned short i = 0; i < height; ++i)
                delete[] m[i];
            delete[] m;
            //m = nullptr;
        }
    }

public:
    Matrix() : width(0), height(0), m(nullptr) {}

    ~Matrix() 
    {
        clear();
    }

    void resize_h(unsigned short new_height) 
    {
        clear();
        height = new_height;
        m = new T*[height];
    }

    void resize_w(unsigned short new_width) 
    {
        //clear();
        width = new_width;
        for (unsigned short i = 0; i < height; i++)
            m[i] = new T[width];
    }

    T& at(unsigned short row, unsigned short col) 
    {
        
        if (row >= height || col >= width) {
            throw std::out_of_range("Index out of range");
        }
        return m[row][col];
    }

    unsigned short get_width() const { return width; }
    unsigned short get_height() const { return height; }

    void rotate90() 
    { 
        Matrix<T> temp;
        temp.resize(height, width);
        for (unsigned short i = 0; i < height; ++i)
            for (unsigned short j = 0; j < width; ++j)
                temp.at(j, height - 1 - i) = m[i][j];
        *this = temp; 
    } 
    void reflectVertical() 
    { 
        for (unsigned short i = 0; i < height; ++i) 
            for (unsigned short j = 0; j < width / 2; ++j) 
                std::swap(m[i][j], m[i][width - 1 - j]);
    } 
    void reflectHorizontal() 
    { 
        for (unsigned short i = 0; i < height / 2; ++i) 
            for (unsigned short j = 0; j < width; ++j) 
                std::swap(m[i][j], m[height - 1 - i][j]);
    }
};