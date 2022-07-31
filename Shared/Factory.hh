#pragma once

#include <cstdint>
#include <iostream>
#include <vector>

#include <Shared/Optional.hh>

namespace shared
{
    template <typename T>
    struct Factory
    {
#define MAX T::MAX_ITEMS

        std::vector<Optional<T>> data;
        uint32_t startingId;

        Factory()
            : startingId(0)
        {
            data.resize(MAX);
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

        template <typename... Arguments>
        void Create(uint32_t id, Arguments... args)
        {
            assert(Exists(id) == false);
            data[id].Set(T{args...});
            Get(id).id = id;
        }
        void Delete(uint32_t id)
        {
            data[id]("tried to delete nonexistant entity");
            data[id].Delete();
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
