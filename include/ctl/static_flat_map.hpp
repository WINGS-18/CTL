#pragma once

#include <array>

namespace ctl {

    template<typename KeyType, typename ValType, std::size_t Size>
    class static_flat_map {
    private:
        std::array<KeyType, Size> m_keys;
        std::array<ValType, Size> m_values;

    public:
        struct pair {
            KeyType m_key;
            ValType m_value;
        };
        

    public:
        static_flat_map(std::initializer_list<pair> list);

        inline ValType& operator[] (const KeyType& key);
        inline pair at(std::size_t index);

    public:
        static_flat_map(const static_flat_map&) = default;
        static_flat_map& operator= (const static_flat_map&) = default;
    
        static_flat_map(static_flat_map&&) = default;
        static_flat_map& operator= (static_flat_map&&) = default;
    
        ~static_flat_map() = default;
    };
}

#include "ctl/static_flat_map.tpp"