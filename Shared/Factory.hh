#pragma once

#include <cstdint>
#include <iostream>

namespace shared
{
    template <class T>
    class Factory
    {
#define MAX T::MAX_ITEMS

        uint32_t startingId;
        T *data[MAX] = {nullptr};

    public:
        Factory()
            : startingId(0)
        {
        }

        ~Factory()
        {
        }

        template <typename... Arguments>
        uint32_t Create(Arguments... args)
        {
            for (uint32_t i = 0; i < MAX; i++)
            {
                uint32_t id = (startingId + i) % MAX;
                if (Exists(id))
                    continue;

                data[id] = new T(args...);

                Get(id)->id = id;

                startingId = (startingId + 1) % MAX;

                return id;
            }

            std::cout << "ran out of ids" << std::endl;
            exit(1);
        }

        void Delete(uint32_t id)
        {
            delete data[id];
            data[id] = nullptr;
        }

        bool Exists(uint32_t id)
        {
            return data[id] != nullptr;
        }

        T *Get(uint32_t id)
        {
            return data[id];
        }
#undef MAX
    };
}