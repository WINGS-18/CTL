#pragma once

#include "ctl/ring_buffer.hpp"
#include "ctl/core/assert.hpp"

namespace ctl {

    template<typename T>
    ring_buffer<T>::ring_buffer(std::size_t capacity)
        : m_data(capacity), m_capacity(capacity) {}

    template<typename T>
    std::vector<T>& ring_buffer<T>::getData() noexcept {
        return m_data;
    }
    
    template<typename T>
    const std::vector<T>& ring_buffer<T>::getData() const noexcept {
        return m_data;
    }

    template<typename T>
    std::size_t ring_buffer<T>::size() const noexcept {
        return m_size;
    }

    template<typename T>
    std::size_t ring_buffer<T>::capacity() const noexcept {
        return m_capacity;
    }
    
    template<typename T>
    void ring_buffer<T>::push(const T& data) noexcept {
        CTL_ASSERT(m_size < m_capacity, "cannot push into a full container");
        
        m_data[m_tail] = data;
        
        m_tail = (m_tail + 1) % m_capacity;
        ++m_size;
    }
    
    template<typename T>
    void ring_buffer<T>::push(T&& data) noexcept {
        CTL_ASSERT(m_size < m_capacity, "cannot push into a full container");
        
        m_data[m_tail] = std::move(data);
        
        m_tail = (m_tail + 1) % m_capacity;
        ++m_size;
    }
    
    template<typename T>
    T& ring_buffer<T>::emplace_back() noexcept {
        CTL_ASSERT(m_size < m_capacity, "emplace_back() called on full container");

        T& data = m_data[m_tail];
        m_tail = (m_tail + 1) % m_capacity;
        ++m_size;

        return data;
    }
    
    template<typename T>
    void ring_buffer<T>::pop() noexcept {
        CTL_ASSERT(m_size > 0, "cannot pop into a full container");

        m_head = (m_head + 1) % m_capacity;
        --m_size;
    }

    template<typename T>
    T& ring_buffer<T>::front() noexcept {
        CTL_ASSERT(m_size > 0, "front() called on empty container");
        
        return m_data[m_head];
    }
    
    template<typename T>
    T& ring_buffer<T>::front() const noexcept {
        CTL_ASSERT(m_size > 0, "front() called on empty container");
        
        return m_data[m_head];
    }
    
    template<typename T>
    T& ring_buffer<T>::back() noexcept {
        CTL_ASSERT(m_size > 0, "back() called on empty container");

        return (*this)[m_size - 1];
    }
    
    template<typename T>
    T& ring_buffer<T>::back() const noexcept {
        CTL_ASSERT(m_size > 0, "back() called on empty container");

        return (*this)[m_size - 1];
    }
    
    template<typename T>
    void ring_buffer<T>::clear() noexcept {
        m_head = 0;
        m_tail = 0;
        m_size = 0;
    }

    template<typename T>
    bool ring_buffer<T>::empty() const noexcept {
        return m_size == 0;
    }

    template<typename T>
    T& ring_buffer<T>::operator[] (std::size_t index) {
        CTL_ASSERT(index < m_size, "index out of range");
        
        auto logicalIndex = (m_head + index) % m_capacity;
        return m_data[logicalIndex];
    }
    
    template<typename T>
    const T& ring_buffer<T>::operator[] (std::size_t index) const {
        CTL_ASSERT(index < m_size, "index out of range");
        
        auto logicalIndex = (m_head + index) % m_capacity;
        return m_data[logicalIndex];
    }

}