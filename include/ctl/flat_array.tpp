#pragma once

#include "ctl/flat_array.hpp"
#include "ctl/core/assert.hpp"

namespace ctl {

    template<typename T>
    flat_array<T>::flat_array(std::initializer_list<std::initializer_list<T>> list) {
        std::size_t rows = list.size();
        std::size_t cols = list.begin()->size();
        m_rows = rows;
        m_cols = cols;

        m_data.resize(rows * cols);
        int i = 0;
        for(const auto& row : list) {
            int j = 0;
            for(const auto& val : row) {
                (*this)(i, j) = val;
                j++;
            }
            i++;
        }
    }

    template<typename T>
    flat_array<T>::flat_array(std::size_t rows, std::size_t cols)
        : m_data(rows * cols), m_rows(rows), m_cols(cols) {}

    template<typename T>
    flat_array<T>::flat_array(std::size_t rows, std::size_t cols, const T& completeInitialize)
        : m_data(rows * cols, completeInitialize), m_rows(rows), m_cols(cols) {}

    template<typename T>
    inline T& flat_array<T>::operator() (std::size_t row, std::size_t col) {
        CTL_ASSERT(row < m_rows && col < m_cols, "index out of range");
        std::size_t index = (row * m_cols) + col;
        
        return m_data[index];
    }
    
    template<typename T>
    inline const T& flat_array<T>::operator() (std::size_t row, std::size_t col) const{
        CTL_ASSERT(row < m_rows && col < m_cols, "index out of range");
        std::size_t index = (row * m_cols) + col;

        return m_data[index];
    }

    template<typename T>
    inline std::size_t flat_array<T>::rows() const noexcept {
        return m_rows;
    }

    template<typename T>
    inline auto flat_array<T>::begin() noexcept {
        return m_data.begin();
    }

    template<typename T>
    inline auto flat_array<T>::end() noexcept {
        return m_data.end();
    }

    template<typename T>
    inline auto flat_array<T>::begin() const noexcept {
        return m_data.cbegin();
    }

    template<typename T>
    inline auto flat_array<T>::end() const noexcept {
        return m_data.cend();
    }

    template<typename T>
    inline std::size_t flat_array<T>::columns() const noexcept {
        return m_cols;
    }

    template<typename T>
    void flat_array<T>::fill(const T& data) noexcept {
        std::fill(begin(), end(), data);
    }

    template<typename T>
    void flat_array<T>::clear() noexcept {
        m_data.clear();
    }

}