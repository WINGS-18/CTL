#include "ctl/static_enum.hpp"

namespace ctl {

    template<typename KeyType, std::size_t Size, std::integral ValueType>
    static_enum<KeyType, Size, ValueType>::static_enum(std::initializer_list<KeyType> keys)
        : m_data(initialize(keys, ValueType {0})) {}

    template<typename KeyType, std::size_t Size, std::integral ValueType>
    static_enum<KeyType, Size, ValueType>::static_enum(std::initializer_list<KeyType> keys, ValueType startingValue)
        : m_data(initialize(keys, startingValue)) {}

    template<typename KeyType, std::size_t Size, std::integral ValueType>
    inline ValueType& static_enum<KeyType, Size, ValueType>::operator[] (const KeyType& key) {
        return m_data[key];
    }

    template<typename KeyType, std::size_t Size, std::integral ValueType>
    inline const ValueType& static_enum<KeyType, Size, ValueType>::operator[] (const KeyType& key) const {
        return m_data[key];
    }

    template<typename KeyType, std::size_t Size, std::integral ValueType>
    static_flat_map<KeyType, ValueType, Size> static_enum<KeyType, Size, ValueType>::initialize(std::initializer_list<KeyType> keys, ValueType startingValue) {
        static_flat_map<KeyType, ValueType, Size> map;
        for(const auto& key : keys) {
            map.insert(key, startingValue++);
        }

        map.sortStaticFlatMap();
        
        return map;
    }
}