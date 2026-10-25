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
        void setEndCharacters() {
            //loops through the buffer and inserts "\n" at exact end of the width sizes
            //it is indication that row ends.
            for(std::size_t i = 0; i < m_rows; i++) {
                m_data[(i * (m_cols + 1)) + m_cols] = '\n';
            }
        }

    public:
        inline char& operator() (int x, int y) {
            return m_data[(y * (m_cols + 1)) + x];
        }
    };
    
}