#include "ctl/static_flat_map.hpp"
#include "ctl/core/assert.hpp"
#include <algorithm>

namespace ctl {
    
    template<typename KeyType, typename ValueType, std::size_t Size>
    constexpr static_flat_map<KeyType, ValueType, Size>::static_flat_map(std::initializer_list<pair> list) {
        CTL_ASSERT(list.size() <= Size, "initializer_list size exceeds static storage capacity");

        std::size_t i = 0;
        m_size = Size;
        for(auto& couple : list) {
            m_keys[i] = couple.m_key;
            m_values[i] = couple.m_value;
            i++;
        }
        
        sort();

    }
    
    template<typename KeyType, typename ValueType, std::size_t Size>
    inline ValueType& static_flat_map<KeyType, ValueType, Size>::operator[] (const KeyType& key) {
        auto foundKey = std::lower_bound(m_keys.begin(), m_keys.end(), key);
        
        if(foundKey != m_keys.end() && *foundKey == key) {
            int index = foundKey - m_keys.begin();
            return m_values[index];
        }

        CTL_PANIC("Key not found");
        
    }
    
    template<typename KeyType, typename ValueType, std::size_t Size>
    inline const ValueType& static_flat_map<KeyType, ValueType, Size>::operator[] (const KeyType& key) const{
        auto foundKey = std::lower_bound(m_keys.begin(), m_keys.end(), key);
        
        if(foundKey != m_keys.end() && *foundKey == key) {
            int index = foundKey - m_keys.begin();
            return m_values[index];
        }
        
        CTL_PANIC("Key not found");
        
    }
    
    template<typename KeyType, typename ValueType, std::size_t Size>
    inline static_flat_map<KeyType, ValueType, Size>::pair static_flat_map<KeyType, ValueType, Size>::at(std::size_t index) {
        CTL_ASSERT(index < m_size, "index out of range");
        return {m_keys[index], m_values[index]};
    }
    
    template<typename KeyType, typename ValueType, std::size_t Size>
    inline void static_flat_map<KeyType, ValueType, Size>::insert(const KeyType& key, const ValueType& val) {
        CTL_ASSERT(m_size < Size, "cannot insert into a full container");
        
        m_size++;
        m_keys[m_size - 1] = key;
        m_values[m_size - 1] = val;
    }

    template<typename KeyType, typename ValueType, std::size_t Size>
    constexpr void static_flat_map<KeyType, ValueType, Size>::sort() {
        auto tempKeys = m_keys;
        auto tempValues = m_values;

        std::sort(m_keys.begin(), m_keys.begin() + m_size);

        for(std::size_t i = 0; i < tempKeys.size(); i++) {
            for(std::size_t j = 0; j < m_keys.size(); j++) {
                if(tempKeys[i] == m_keys[j]) {
                    m_values[j] = tempValues[i];
                    break;
                }
            }
        }
    }


}