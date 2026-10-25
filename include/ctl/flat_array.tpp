#include "ctl/flat_array.hpp"

namespace ctl {

    template<typename T>
    flat_array<T>::flat_array(std::size_t rows, std::size_t cols)
        : m_data(rows * cols), m_rows(rows), m_cols(cols) {}

    template<typename T>
    flat_array<T>::flat_array(std::size_t rows, std::size_t cols, const T& completeInitialize)
        : m_data(rows * cols, completeInitialize), m_rows(rows), m_cols(cols) {}

    template<typename T>
    inline T& flat_array<T>::operator() (std::size_t x, std::size_t y) {
        return m_data[(y * m_cols) + x];
    }

    template<typename T>
    inline const T& flat_array<T>::operator() (std::size_t x, std::size_t y) const{
        return m_data[(y * m_cols) + x];
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
    void flat_array<T>::fill(const T& data) {
        std::fill(begin(), end(), data);
    }

}