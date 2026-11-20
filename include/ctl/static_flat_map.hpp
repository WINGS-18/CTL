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
        constexpr static_flat_map(std::initializer_list<pair> list);

        inline ValueType& operator[] (const KeyType& key);
        inline const ValueType& operator[] (const KeyType& key) const noexcept;
        inline ValueType& at(const KeyType& key);
        inline ValueType& at(const KeyType& key) const noexcept;

        void insert(const KeyType& key, const ValueType& val);
        void unsortedInsert(const KeyType& key, const ValueType& val);

        constexpr void sort();

        bool empty() const noexcept;
        std::size_t size() const noexcept;
        std::size_t capacity() const noexcept;

    private:
        auto find(const KeyType& key) const noexcept;

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