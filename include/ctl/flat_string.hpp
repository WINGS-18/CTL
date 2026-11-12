#pragma once

#include <string>

namespace ctl {

    class flat_string {
    private:
        std::string m_data;
        std::size_t m_rows;
        std::size_t m_cols;

    public:
        flat_string(std::size_t rows, std::size_t cols, char defaultValue) : m_rows(rows), m_cols(cols) {
            m_data.assign((rows * cols) + rows, defaultValue);
            setEndCharacters();
        }
        
        const std::string& getData() const noexcept {
            return m_data;
        }
        
    private:
        void setEndCharacters() noexcept {
            //loops through the buffer and inserts "\n" at exact end of the width sizes
            //it is indication that row ends.
            for(std::size_t i = 0; i < m_rows; i++) {
                (*this)(i, m_cols) = '\n';
            }
        }

    public:
        inline char& operator() (std::size_t row, std::size_t col) {
            return m_data[(row * (m_cols + 1)) + col];
        }
    };
    
}