#pragma once

#include "ctl/static_flat_map.hpp"
#include "ctl/core/assert.hpp"
#include <algorithm>

namespace ctl {
    
    template<typename KeyType, typename ValueType, std::size_t Size>
    constexpr static_flat_map<KeyType, ValueType, Size>::static_flat_map(std::initializer_list<pair> list) {
        CTL_ASSERT(list.size() <= Size, "initializer_list size exceeds static storage capacity");

        std::size_t i = 0;
        m_size = list.size();
        for(auto& couple : list) {
            m_keys[i] = couple.m_key;
            m_values[i] = couple.m_value;
            i++;
        }
        
        sort();

    }
    
    template<typename KeyType, typename ValueType, std::size_t Size>
    inline ValueType& static_flat_map<KeyType, ValueType, Size>::operator[] (const KeyType& key) {
        auto endIt = m_keys.begin() + m_size;

        auto foundKey = find(key);
        
        if(foundKey != endIt) {
            int index = foundKey - m_keys.begin();
            return m_values[index];
        }

        if(m_size < capacity()) {
            insert(key, ValueType{});
            return (*this)[key];
        }

        CTL_PANIC("cannot insert max capcity reached container");
        
    }
    
    template<typename KeyType, typename ValueType, std::size_t Size>
    inline const ValueType& static_flat_map<KeyType, ValueType, Size>::operator[] (const KeyType& key) const noexcept {
        auto endIt = m_keys.begin() + m_size;
        auto foundKey = find(key);

        if(foundKey != endIt && *foundKey == key) {
            int index = foundKey - m_keys.begin();
            return m_values[index];
        }
        
        CTL_PANIC("Key not found");
        
    }
    
    template<typename KeyType, typename ValueType, std::size_t Size>
    inline ValueType& static_flat_map<KeyType, ValueType, Size>::at(const KeyType& key) {
        auto foundKey = find(key);
        auto endIt = m_keys.begin() + m_size;

        if(foundKey != endIt && *foundKey == key) {
            int index = foundKey - m_keys.begin();
            return m_values[index];
        }

        CTL_PANIC("Key not found");
    }
    
    template<typename KeyType, typename ValueType, std::size_t Size>
    inline const ValueType& static_flat_map<KeyType, ValueType, Size>::at(const KeyType& key) const noexcept {
        auto foundKey = find(key);
        auto endIt = m_keys.begin() + m_size;

        if(foundKey != endIt) {
            int index = foundKey - m_keys.begin();
            return m_values[index];
        }

        CTL_PANIC("Key not found");
    }
    
    template<typename KeyType, typename ValueType, std::size_t Size>
    inline void static_flat_map<KeyType, ValueType, Size>::insert(const KeyType& key, const ValueType& val) {
        auto endIt = m_keys.begin() + m_size;
        auto foundPosition = lowerBound(key);
        
        std::size_t index = foundPosition - m_keys.begin();
        if(foundPosition != endIt && *foundPosition == key) {
            m_values[index] = val;
            return;
        }

        CTL_ASSERT(m_size < Size, "cannot insert into a full container");
        
        for (std::size_t i = m_size; i > index; --i) {
            m_keys[i] = std::move(m_keys[i - 1]);
            m_values[i] = std::move(m_values[i - 1]);
        }

        m_keys[index] = key;
        m_values[index] = val;
        ++m_size;
    }

    template<typename KeyType, typename ValueType, std::size_t Size>
    inline void static_flat_map<KeyType, ValueType, Size>::unsortedInsert(const KeyType& key, const ValueType& val) {
        CTL_ASSERT(m_size < Size, "cannot insert into a full container");
        
        m_size++;
        m_keys[m_size - 1] = key;
        m_values[m_size - 1] = val;
    }

    template<typename KeyType, typename ValueType, std::size_t Size>
    constexpr void static_flat_map<KeyType, ValueType, Size>::sort() {
        std::array<std::size_t, Size> indexes{};
        for(std::size_t i = 0; i < m_size; i++) {
            indexes[i] = i;
        }

        std::sort(indexes.begin(), indexes.begin() + m_size, [&] (std::size_t a, std::size_t b) {
            return m_keys[a] < m_keys[b];
        });
        
        std::array<KeyType, Size> sortedKeys;
        std::array<ValueType, Size> sortedValues;

        for(std::size_t i = 0; i < m_size; i++) {
            sortedKeys[i] = std::move(m_keys[indexes[i]]);
            sortedValues[i] = std::move(m_values[indexes[i]]);
        }

        m_keys = std::move(sortedKeys);
        m_values= std::move(sortedValues);

    }

    template<typename KeyType, typename ValueType, std::size_t Size>
    bool static_flat_map<KeyType, ValueType, Size>::empty() const noexcept {
        if(m_size == 0) {
            return true;
        }

        return false;
    }

    template<typename KeyType, typename ValueType, std::size_t Size>
    std::size_t static_flat_map<KeyType, ValueType, Size>::size() const noexcept {
        return m_size;
    }

    template<typename KeyType, typename ValueType, std::size_t Size>
    std::size_t static_flat_map<KeyType, ValueType, Size>::capacity() const noexcept {
        return Size;
    }

    template<typename KeyType, typename ValueType, std::size_t Size>
    bool static_flat_map<KeyType, ValueType, Size>::contains(const KeyType& key) noexcept {
        auto endIt = m_keys.begin() + m_size;

        return find(key) != endIt;
    }

    template<typename KeyType, typename ValueType, std::size_t Size>
    std::span<const KeyType> static_flat_map<KeyType, ValueType, Size>::keys() const noexcept {
        return {m_keys.data(), m_size};
    }

    template<typename KeyType, typename ValueType, std::size_t Size>
    auto static_flat_map<KeyType, ValueType, Size>::lowerBound(const KeyType& key) {
        return std::lower_bound(m_keys.begin(), m_keys.begin() + m_size, key);
    }

    template<typename KeyType, typename ValueType, std::size_t Size>
    auto static_flat_map<KeyType, ValueType, Size>::lowerBound(const KeyType& key) const noexcept {
        return std::lower_bound(m_keys.begin(), m_keys.begin() + m_size, key);
    }

    template<typename KeyType, typename ValueType, std::size_t Size>
    auto static_flat_map<KeyType, ValueType, Size>::find(const KeyType& key) noexcept {
        auto endIt = m_keys.begin() + m_size;
        auto foundKey = lowerBound(key);
        
        if(foundKey != endIt && *foundKey == key) {
            return foundKey;
        }

        return endIt;
    }

    template<typename KeyType, typename ValueType, std::size_t Size>
    auto static_flat_map<KeyType, ValueType, Size>::find(const KeyType& key) const noexcept {
        auto endIt = m_keys.begin() + m_size;
        auto foundKey = lowerBound(key);
        
        if(foundKey != endIt && *foundKey == key) {
            return foundKey;
        }

        return endIt;
    }
}