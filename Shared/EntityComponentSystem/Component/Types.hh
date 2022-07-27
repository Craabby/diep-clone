#define DECLARE_COMPONENT_FIELD(type, name) \
private:                                    \
    type m_##name;                          \
                                            \
public:                                     \
    type name();                            \
    type name(type);

#define DEFINE_COMPONENT_FIELD(type, ClassName, name) \
    type ClassName::name()                            \
    {                                                 \
        return m_##name;                              \
    }                                                 \
                                                      \
    type ClassName::name(type x)                      \
    {                                                 \
        m_##name = x;                                 \
        updated = true;                               \
        return x;                                     \
    }
