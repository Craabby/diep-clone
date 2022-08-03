#pragma once

#include <cassert>
#include <cstdint>
#include <iostream>
#include <optional>
#include <vector>

#include <Shared/Config.hh>

namespace shared
{
    template <typename T>
    struct Factory
    {
        struct Iterator
        {
            uint32_t index;
            std::optional<T> *value;
            Iterator(std::optional<T> *value, uint32_t index)
                : value(value),
                  index(index)
            {
            }

            T &operator*()
            {
                // __ASSERT((bool)value[index]);
                return **(value + index);
            }

            Iterator &operator++()
            {
                do
                    index++;
                while (index < MAX && !*(value + index));

                return *this;
            }

            Iterator &operator++(int)
            {
                do
                    index++;
                while (index < MAX && !*(value + index));
                return *this;
            }

            T *operator->()
            {
                return &**value;
            }

            bool operator==(const Iterator &other)
            {
                return index == other.index;
            }

            bool operator!=(const Iterator &other)
            {
                return index != other.index;
            }

            bool operator<(const Iterator &other)
            {
                return index < other.index;
            }
        };

        static constexpr uint32_t MAX = T::MAX_ITEMS;

        uint32_t startingId = 0;
        std::optional<T> *data = new std::optional<T>[MAX];

        Factory() = default;
        Factory(const Factory &) = delete;
        ~Factory()
        {
            delete[] data;
        }

        Iterator begin()
        {
            // // find the first existing entity
            // for (uint32_t id = 0; id < MAX; id++)
            // {
            //     if (Exists(id))
            //         return Iterator{id};
            // }
            // __ASSERT(false);
            return Iterator{data, 0};
        }

        Iterator end()
        {
            // // get the entity after the last valid one
            // for (uint32_t id = MAX - 1; id >= 0; id--)
            // {
            //     if (Exists(id))
            //         return Iterator{id + 1};
            // }
            // __ASSERT(false);

            return Iterator{data, MAX};
        }

        template <typename... Arguments>
        uint32_t Create(Arguments... args)
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

            __ASSERT(false);
        }

        template <typename... Arguments>
        void Create(uint32_t id, Arguments... args)
        {
            __ASSERT(Exists(id) == false);
            data[id].emplace(args...);
            Get(id).id = id;
        }
        void Delete(uint32_t id)
        {
            __ASSERT(Exists(id));
            data[id].reset();
            startingId = id;
        }

        bool Exists(uint32_t id) const
        {
            return (bool)data[id];
        }

        T &Get(uint32_t id)
        {
            __ASSERT(Exists(id));
            return *data[id];
        }
    };
}
