#pragma once

#include <cassert>
#include <cstdint>
#include <iostream>
#include <optional>
#include <vector>

namespace shared
{
    template <typename T>
    struct Factory
    {
#define MAX T::MAX_ITEMS

        std::optional<T> *data = new std::optional<T>[MAX];
        uint32_t startingId;

        Factory()
            : startingId(0)
        {
        }

        Factory(const Factory &) = delete;

        ~Factory()
        {
        }

        template <typename... Arguments>
        uint32_t Create(Arguments...args)
        {
            for (uint32_t i = 0; i < MAX; i++)
            {
                uint32_t id = (startingId + i) % MAX;
                if (Exists(id))
                    continue;
                data[id].emplace(args...);
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
            data[id].emplace(args...);
            Get(id).id = id;
        }
        void Delete(uint32_t id)
        {
            assert(Exists(id));
            data[id].reset();
        }

        bool Exists(uint32_t id) const
        {
            return (bool)data[id];
        }

        T &Get(uint32_t id)
        {
            assert(Exists(id));
            return *data[id];
        }
#undef MAX
    };
}
