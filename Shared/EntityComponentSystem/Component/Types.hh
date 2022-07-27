#define DECLARE_COMPONENT_FIELD(type, ClassName, name) \
private:                                               \
    class Field##name                                  \
    {                                                  \
        type v;                                        \
        ClassName *owner;                              \
                                                       \
    public:                                            \
        Field##name(ClassName *owner);                 \
        type operator=(type x);                        \
        type operator+=(type x);                       \
        type operator*();                              \
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
    type ClassName::Field##name::operator=(type x)        \
    {                                                     \
        owner->updated = true;                            \
        return v = x;                                     \
    }                                                     \
                                                          \
    type ClassName::Field##name::operator+=(type x)       \
    {                                                     \
        return *this = v + x;                             \
    }                                                     \
                                                          \
    type ClassName::Field##name::operator*()              \
    {                                                     \
        return v;                                         \
    }
