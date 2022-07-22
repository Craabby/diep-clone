#pragma once

#include <cstdint>
#include <iostream>
#include <vector>

#include <Shared/Optional.hh>

namespace shared
{
    template <class T>
    class Factory
    {
#define MAX T::MAX_ITEMS

        uint32_t startingId;
        std::vector<Optional<T>> data;

    public:
        Factory()
            : startingId(0)
        {
            data.reserve(MAX);
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

                data[id].Set(T{args...});
                Get(id).id = id;

                startingId = (startingId + 1) % MAX;

                return id;
            }

            assert(false);
        }

        void Delete(uint32_t id)
        {
            data[id]("tried to delete nonexistant entity").Delete();
        }

        bool Exists(uint32_t id)
        {
            return data[id].Exists();
        }

        T &Get(uint32_t id)
        {
            return data[id]("tried to get nonixistant entity");
        }
#undef MAX
    };
}
