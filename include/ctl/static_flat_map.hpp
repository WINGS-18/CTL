#pragma once

#include <array>

namespace ctl {

    template<typename _Key, typename _Val, std::size_t _Size>
    class static_flat_map {
    private:
        std::array<_Key, _Size> m_keys;
        std::array<_Val, _Size> m_values;

    public:
        struct pair {
            _Key m_key;
            _Val m_value;

            pair(_Key key, _Val val)
                : m_key(key), m_value(val) {}
        };
        

    public:
        static_flat_map(std::initializer_list<pair> list);

        inline _Val& operator[] (_Key key);
        inline pair at(std::size_t index);
    };
}

#include "ctl/static_flat_map.tpp"