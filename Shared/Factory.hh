#pragma once

#include <algorithm>
#include <std/algorithm.hh>
#include <cassert>
#include <cstdint>
#include <iostream>
#include <std/optional.hh>
#include <std/vector.hh>
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
        std2::Optional<T> *data = new std2::Optional<T>[MAX];
        // thank you for 1412 for suggesting this genius optimization
        std2::Vector<uint32_t> freeIds;
        std::set<uint32_t> usedIds;

        Factory()
        {
            freeIds.Resize(MAX);
            for (uint32_t i = 0; i < MAX; i++)
                freeIds[i] = MAX - i - 1;
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
            uint32_t id = freeIds[freeIds.Size() - 1];
            usedIds.insert(id);
            freeIds.Erase(freeIds.Size() - 1);
            entitiesInUse++;
            data[id].Emplace(args...);
            Get(id).id = id;

            return id;
        }

        template <typename... Arguments>
        void Create(uint32_t id, Arguments... args)
        {
            __ASSERT(Exists(id) == false);
            entitiesInUse++;
            data[id].Emplace(std2::Forward<Arguments>(args)...);
            usedIds.insert(id);
            freeIds.Erase<true>((size_t)(std2::Find(freeIds.begin(), freeIds.end(), id) - freeIds.begin()));
            Get(id).id = id;

        }
        void Delete(uint32_t id)
        {
            __ASSERT(Exists(id));
            entitiesInUse--;
            data[id].Delete();
            usedIds.erase(id);
            freeIds.Emplace(id);
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
