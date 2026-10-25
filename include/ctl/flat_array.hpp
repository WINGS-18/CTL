#pragma once

#include <vector>

namespace ctl {

    template<typename T>
    class flat_array {
    private:
        std::vector<T> m_data;
        std::size_t m_rows;
        std::size_t m_cols;
    
    public:

    public:
        flat_array(std::size_t rows, std::size_t cols);
        flat_array(std::size_t rows, std::size_t cols, const T& completeInitialize);
        
        T& operator() (std::size_t x, std::size_t y);
        const T& operator() (std::size_t x, std::size_t y) const;

        std::size_t rows() const noexcept;
        std::size_t columns() const noexcept;

        auto begin() noexcept;
        auto end() noexcept;
        
        auto begin() const noexcept;
        auto end() const noexcept;

        void fill(const T& data);

    public:
        flat_array(const flat_array&) = default;
        flat_array& operator= (const flat_array&) = default;
    
        flat_array(flat_array&&) = default;
        flat_array& operator= (flat_array&&) = default;
    
        ~flat_array() = default;
    };

}


#include "ctl/flat_array.tpp"