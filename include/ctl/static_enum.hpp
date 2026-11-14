#pragma once

#include "ctl/static_flat_map.hpp"

namespace ctl {

    template<typename KeyType, std::size_t Size, std::integral ValueType = int>
    class static_enum {
    private:
        static_flat_map<KeyType, ValueType, Size> m_data;

    public:
        static_enum(std::initializer_list<KeyType> keys);
        static_enum(std::initializer_list<KeyType> keys, ValueType startingValue);

        inline ValueType& operator[] (const KeyType& key);
        inline const ValueType& operator[] (const KeyType& key) const;

    private:
        static_flat_map<KeyType, ValueType, Size> initialize(std::initializer_list<KeyType> keys, ValueType startingValue);

    public:
        static_enum() = default;
        static_enum(const static_enum&) = default;
        static_enum& operator= (const static_enum&) = default;
    
        static_enum(static_enum&&) = default;
        static_enum& operator= (static_enum&&) = default;
    
        ~static_enum() = default;
    };

}

#include "ctl/static_enum.tpp"