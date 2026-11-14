#pragma once

#include <array>

namespace ctl {

    template<typename KeyType, typename ValueType, std::size_t Size>
    class static_flat_map {
    private:
        std::array<KeyType, Size> m_keys;
        std::array<ValueType, Size> m_values;
        std::size_t m_size = 0;

    public:
        struct pair {
            KeyType m_key;
            ValueType m_value;
        };
        

    public:
        static_flat_map(std::initializer_list<pair> list);

        inline ValueType& operator[] (const KeyType& key);
        inline const ValueType& operator[] (const KeyType& key) const;
        inline pair at(std::size_t index);

        void insert(const KeyType& key, const ValueType& val);

        void sortStaticFlatMap();

    public:
        static_flat_map() = default;
        static_flat_map(const static_flat_map&) = default;
        static_flat_map& operator= (const static_flat_map&) = default;
    
        static_flat_map(static_flat_map&&) = default;
        static_flat_map& operator= (static_flat_map&&) = default;
    
        ~static_flat_map() = default;
    };
}

#include "ctl/static_flat_map.tpp"