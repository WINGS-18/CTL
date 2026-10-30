/**
 * ring_buffer class provides various methods to use array like a queue.
 * Provides excellent cache locality and even the classis templated meaning can be used for any data type storage.
 */

#pragma once

#include <vector>

namespace ctl {

    template<typename T>
    class ring_buffer {
    private:
        std::vector<T> m_data;
        std::size_t m_head, m_tail;
        std::size_t m_size = 0;

    public:
        ring_buffer(std::size_t reserveSize);
        ring_buffer(std::size_t initSize, std::size_t reserveSize);

        std::size_t size() const noexcept;
        std::size_t capacity() const noexcept;
        
        std::size_t movePointers(std::size_t pointer, std::size_t size) noexcept;
        void reserveBack(std::size_t size) noexcept;
        void releaseFront(std::size_t size) noexcept;
        void releaseBack(std::size_t size) noexcept;
        void shrink(std::size_t size) noexcept;
        
        void pushPrimitive(T data) noexcept;
        void push(const T& data) noexcept;
        void push(T&& data) noexcept;
        void pop() noexcept;
        void clear() noexcept;
        bool empty() const noexcept;
        
        int head() const noexcept;
        int tail() const noexcept;

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