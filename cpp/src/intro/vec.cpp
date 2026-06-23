#pragma once
#include <iostream>

template<typename T>
class Vector {
    private:
        T *data;
        size_t size;
        size_t capacity;
    public:
        Vector() : data(nullptr), size(0), capacity(0) { }
        explicit Vector(size_t initial_sz)
        {
            size = initial_sz;
            capacity = initial_sz;
            data = new T[capacity];
        }

        ~Vector() { delete[] data; }

        void push_back(const T& value)
        {
            if (size >= capacity)
            {
                size_t new_cap = (capacity == 0) ? 4 : capacity * 2;
                T* new_data = new T[new_cap];
                for (size_t i = 0; i < size; i++)
                    new_data[i] = data[i];
                delete[] data;
                data = new_data;
                capacity = new_cap;
            }

            data[size++] = value;
        }

        T& operator[](size_t index) { return data[index]; }
        size_t size() const { return size; }
        size_t capacity() const { return capacity; }
};
