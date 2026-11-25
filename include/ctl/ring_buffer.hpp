/**
 * ring_buffer class provides various methods to use array like a queue.
 * Provides excellent cache locality and even the classis templated meaning can be used for any data type storage.
 */

#pragma once

#include <cstddef>
#include <vector>

namespace ctl {

    template<typename T>
    class ring_buffer {
    private:
        std::vector<T> m_data;
        std::size_t m_head {0};
        std::size_t m_tail {0};
        std::size_t m_size {0};
        std::size_t m_capacity {0};

    public:
        ring_buffer(std::size_t capacity);

        std::size_t size() const noexcept;
        std::size_t capacity() const noexcept;
        
        void push(const T& data) noexcept;
        void push(T&& data) noexcept;
        
        T& emplace_back() noexcept;

        void pop() noexcept;

        T& front() noexcept;
        const T& front() const noexcept;
        T& back() noexcept;
        const T& back() const noexcept;

        void clear() noexcept;
        bool empty() const noexcept;

        std::vector<T>& getData() noexcept;
        const std::vector<T>& getData() const noexcept;

        T& operator[] (std::size_t index);
        const T& operator[] (std::size_t index) const;

    public:
        ring_buffer(const ring_buffer&) = default;
        ring_buffer& operator= (const ring_buffer&) = default;
    
        ring_buffer(ring_buffer&&) = default;
        ring_buffer& operator= (ring_buffer&&) = default;
    
        ~ring_buffer() = default;
    };

}

#include "ctl/ring_buffer.tpp"