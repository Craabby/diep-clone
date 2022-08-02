#pragma once

#include <algorithm>
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
        static constexpr uint32_t MAX = T::MAX_ITEMS;

        uint32_t startingId;
        std::optional<T> *data = new std::optional<T>[MAX];
        // 1412 came up with this clever optimization
        std::vector<uint32_t> freeIds;

        Factory()
            : startingId(0)
        {
            freeIds.resize(MAX);
            for (uint32_t i = 0; i < MAX; i++)
                freeIds[i] = MAX - i - 1;
        }

        Factory(const Factory &) = delete;

        ~Factory()
        {
            delete[] data;
        }

        template <typename... Arguments>
        uint32_t Create(Arguments... args)
        {
            // cast, otherwise it will return a refrence somehow
            uint32_t id = (uint32_t)freeIds.back();
            freeIds.pop_back();
            data[id].emplace(args...);
            Get(id).id = id;

            startingId = (startingId + 1) % MAX;

            return id;
        }

        template <typename... Arguments>
        void Create(uint32_t id, Arguments... args)
        {
            assert(Exists(id) == false);
            data[id].emplace(args...);
            freeIds.erase(std::find(freeIds.begin(), freeIds.end(), id));
            Get(id).id = id;
        }
        void Delete(uint32_t id)
        {
            assert(Exists(id));
            freeIds.push_back(id);
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
