#pragma once

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <optional>
#include <vector>
#include <set>

#include <Shared/Config.hh>

namespace shared
{
    template <typename T>
    struct Factory
    {
        struct Iterator
        {
            // uint32_t idIndex;
            Factory<T> *parent;
            std::set<uint32_t>::iterator idIterator;
            Iterator(Factory<T> *parent)
                : parent(parent),
                  idIterator(parent->usedIds.begin())
            {
            }

            T &operator*()
            {
                // __ASSERT(parent->data[parent->usedIds[idIndex]]);
                return *parent->data[*idIterator];
            }

            Iterator &operator++()
            {
                do
                    idIterator++;
                while (!parent->data[*idIterator] && idIterator != parent->usedIds.end());
                return *this;
            }

            Iterator &operator++(int)
            {
                do
                    idIterator++;
                while (!parent->data[*idIterator] && idIterator != parent->usedIds.end());
                return *this;
            }

            T *operator->()
            {
                return &**parent->data[*idIterator];
            }

            bool operator==(const Iterator &other)
            {
                return idIterator == other.idIterator;
            }

            bool operator!=(const Iterator &other)
            {
                return idIterator != other.idIterator;
            }

            bool operator<(const Iterator &other)
            {
                return idIterator != other.idIterator;
            }
        };

        static constexpr uint32_t MAX = T::MAX_ITEMS;

        uint32_t entitiesInUse = 0;
        // too large for the stack
        std::optional<T> *data = new std::optional<T>[MAX];
        // thank you for 1412 for suggesting this genius optimization
        std::vector<uint32_t> freeIds;
        std::set<uint32_t> usedIds;

        Factory()
        {
            freeIds.resize(MAX);
            for (uint32_t i = 0; i < MAX; i++)
                freeIds.at(i) = MAX - i - 1;
        };
        Factory(const Factory &) = delete;
        ~Factory()
        {
            delete[] data;
        }

        Iterator begin()
        {
            return Iterator{this};
        }

        Iterator end()
        {
            Iterator i{this};
            i.idIterator = usedIds.end();
            return i;
        }

        template <typename... Arguments>
        uint32_t Create(Arguments... args)
        {
            uint32_t id = (uint32_t)freeIds.back();
            usedIds.insert(id);
            freeIds.pop_back();
            entitiesInUse++;
            data[id].emplace(args...);
            Get(id).id = id;

            return id;
        }

        template <typename... Arguments>
        void Create(uint32_t id, Arguments... args)
        {
            __ASSERT(Exists(id) == false);
            entitiesInUse++;
            data[id].emplace(args...);
            usedIds.insert(id);
            freeIds.erase(std::find(freeIds.begin(), freeIds.end(), id));
            Get(id).id = id;

        }
        void Delete(uint32_t id)
        {
            __ASSERT(Exists(id));
            entitiesInUse--;
            data[id].reset();
            usedIds.erase(id);
            freeIds.push_back(id);
            
        }

        bool Exists(uint32_t id) const
        {
            if (id >= MAX)
                return false;
            return (bool)data[id];
        }

        T &Get(uint32_t id)
        {
            __ASSERT(Exists(id));
            return *data[id];
        }
    };
}
