#ifndef VOIDPOINTER_HPP
#define VOIDPOINTER_HPP

namespace pcke
{
    class VoidPointer
    {
        public:
            VoidPointer() = default;
            VoidPointer(unsigned new_size);
            VoidPointer(const VoidPointer&) = delete;
            VoidPointer(VoidPointer&& other);
            ~VoidPointer();

            VoidPointer& operator =(const VoidPointer& other) = delete;
            VoidPointer& operator =(VoidPointer&& other);

            void* get();
            const void* get() const;

            unsigned getSize() const;

        private:
            char* data = nullptr;
            bool array = false;
            unsigned size = 0;
    };
}

#endif // VOIDPOINTER_HPP
