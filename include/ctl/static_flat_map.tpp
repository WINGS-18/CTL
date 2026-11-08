#include "ctl/static_flat_map.hpp"
#include <algorithm>
#include <iostream>
namespace ctl {
    
    template<typename _Key, typename _Val, std::size_t _Size>
    static_flat_map<_Key, _Val, _Size>::static_flat_map(std::initializer_list<pair> list) {
        std::size_t i = 0;
        
        for(auto& couple : list) {
            m_keys[i] = couple.m_key;
            m_values[i] = couple.m_value;
            i++;
        }

        auto tempKeys = m_keys;
        auto tempValues = m_values;

        std::sort(m_keys.begin(), m_keys.end());

        for(std::size_t i = 0; i < tempKeys.size(); i++) {
            for(std::size_t j = 0; j < m_keys.size(); j++) {
                if(tempKeys[i] == m_keys[j]) {
                    m_values[j] = tempValues[i];
                    break;
                }
            }
        }

    }
    
    template<typename _Key, typename _Val, std::size_t _Size>
    inline _Val& static_flat_map<_Key, _Val, _Size>::operator[] (_Key key) {
        auto foundKey = std::lower_bound(m_keys.begin(), m_keys.end(), key);
        
        if(foundKey != m_keys.end() && *foundKey == key) {
            int index = foundKey - m_keys.begin();
            return m_values[index];
        }
        
    }
    
    template<typename _Key, typename _Val, std::size_t _Size>
    inline static_flat_map<_Key, _Val, _Size>::pair static_flat_map<_Key, _Val, _Size>::at(std::size_t index) {
        return {m_keys[index], m_values[index]};
    }

}