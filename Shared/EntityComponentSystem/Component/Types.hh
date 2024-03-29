#include <iostream>

#define DECLARE_COMPONENT_FIELD(type, ClassName, name) \
private:                                               \
    class Field##name                                  \
    {                                                  \
        type v = 0;                                    \
        ClassName *owner;                              \
                                                       \
    public:                                            \
        Field##name(ClassName *owner);                 \
        Field##name(const Field##name &) = delete;     \
        void operator=(type x);                        \
        void operator+=(type x);                       \
        void operator/=(type x);                       \
        void operator*=(type x);                       \
        void operator++();                             \
        void operator++(int);                          \
        type operator*();                              \
        operator type() { return v; }                  \
    };                                                 \
                                                       \
public:                                                \
    Field##name name{this};

#define DEFINE_COMPONENT_FIELD(type, ClassName, name)     \
    ClassName::Field##name::Field##name(ClassName *owner) \
        : owner(owner)                                    \
    {                                                     \
    }                                                     \
                                                          \
    void ClassName::Field##name::operator=(type x)        \
    {                                                     \
        if (v != x)                                       \
            owner->updated = true;                        \
        v = x;                                            \
    }                                                     \
                                                          \
    void ClassName::Field##name::operator+=(type x)       \
    {                                                     \
        *this = v + x;                                    \
    }                                                     \
                                                          \
    void ClassName::Field##name::operator/=(type x)       \
    {                                                     \
        *this = v / x;                                    \
    }                                                     \
                                                          \
    void ClassName::Field##name::operator*=(type x)       \
    {                                                     \
        *this = v * x;                                    \
    }                                                     \
                                                          \
    type ClassName::Field##name::operator*()              \
    {                                                     \
        return v;                                         \
    }                                                     \
                                                          \
    void ClassName::Field##name::operator++()             \
    {                                                     \
        *this = ++v;                                      \
    }                                                     \
                                                          \
    void ClassName::Field##name::operator++(int)          \
    {                                                     \
        *this = ++v;                                      \
    }
