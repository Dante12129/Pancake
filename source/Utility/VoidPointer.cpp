#include "include\Pancake\Utility\VoidPointer.hpp"

#include <stdexcept>

namespace pcke
{
    VoidPointer::VoidPointer(unsigned new_size) : size(new_size)
    {
        if(size == 0)
            throw std::runtime_error("Size zero passed to VoidPointer.");
        else if(size == 1)
        {
            data = new char;
            array = false;
        }
        else if(size > 1)
        {
            data = new char[size];
            array = true;
        }
    }
    VoidPointer::VoidPointer(VoidPointer&& other) : data(other.data), array(other.array)
    {
        if(data)
        {
            if(array)
                delete[] data;
            else
                delete data;
            data = nullptr;
        }

        other.data = nullptr;
        other.array = false;
    }
    VoidPointer::~VoidPointer()
    {
        if(data)
        {
            if(array)
                delete[] data;
            else
                delete data;
            data = nullptr;
        }
    }

    VoidPointer& VoidPointer::operator=(VoidPointer&& other)
    {
        if(data)
        {
            if(array)
                delete[] data;
            else
                delete data;
            data = nullptr;
        }

        data = other.data;
        array = other.array;

        other.data = nullptr;
        other.array = false;

        return *this;
    }

    void* VoidPointer::get()
    {
        return static_cast<void*>(data);
    }
    const void* VoidPointer::get() const
    {
        return static_cast<void*>(data);
    }

    unsigned VoidPointer::getSize() const
    {
        return size;
    }
}
