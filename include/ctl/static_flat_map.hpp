#pragma once

#include <array>
#include <concepts>
#include <cstddef>
#include <span>

namespace ctl {

    template<typename, std::size_t, std::integral>
    class static_enum;
    
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
        inline const ValueType& at(const KeyType& key) const noexcept;

        void insert(const KeyType& key, const ValueType& val);
        
        bool empty() const noexcept;
        std::size_t size() const noexcept;
        std::size_t capacity() const noexcept;

        bool contains(const KeyType& key) noexcept;

        std::span<const KeyType> keys() const noexcept;
        
    private:
        auto lowerBound(const KeyType& key);
        auto lowerBound(const KeyType& key)const noexcept;
        auto find(const KeyType& key) noexcept;
        auto find(const KeyType& key) const noexcept;
        constexpr void sort();
        void unsortedInsert(const KeyType& key, const ValueType& val);
        
    public:
        static_flat_map() = default;
        static_flat_map(const static_flat_map&) = default;
        static_flat_map& operator= (const static_flat_map&) = default;
        
        static_flat_map(static_flat_map&&) = default;
        static_flat_map& operator= (static_flat_map&&) = default;
    
        ~static_flat_map() = default;

    private:
        template<typename, std::size_t, std::integral>
        friend class static_enum;
    };
}

#include "ctl/static_flat_map.tpp"