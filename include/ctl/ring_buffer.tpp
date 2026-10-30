#include "ctl/ring_buffer.hpp"

namespace ctl {

    template<typename T>
    ring_buffer<T>::ring_buffer(std::size_t reserveSize)
        : m_data(reserveSize), m_head(0), m_tail(0), m_size(0) {}

    template<typename T>
    ring_buffer<T>::ring_buffer(std::size_t initSize, std::size_t reserveSize)
        : m_data(reserveSize), m_head(0), m_tail(static_cast<int> (initSize)), m_size(initSize) {}

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
        return m_data.capacity();
    }

    template<typename T>
    std::size_t ring_buffer<T>::movePointers(std::size_t pointer, std::size_t size) noexcept {
        pointer = (pointer + size) % (m_data.size());   //increases the volume of the valid range (tail -> head).

        return pointer;
    }
    
    template<typename T>
    void ring_buffer<T>::releaseFront(std::size_t size) noexcept {
        m_head = movePointers(m_head, size);
        m_size -= size;
    }

    template<typename T>
    void ring_buffer<T>::releaseBack(std::size_t size) noexcept {
        if(m_tail != 0) {
            m_tail -= size;
            m_size -= size;
        }
    }

    template<typename T>
    void ring_buffer<T>::shrink(std::size_t size) noexcept {
        if(size >= m_tail) {
            return;
        }

        if(size <= 0) {
            m_head = 0;
            m_tail = 0;
            m_size = 0;
        }
        m_head = 0;
        m_tail = size;
        m_size = size;
    }

    template<typename T>
    void ring_buffer<T>::reserveBack(std::size_t size) noexcept {
        m_tail = movePointers(m_tail, size);
        m_size += size;
    }

    template<typename T>
    void ring_buffer<T>::pushPrimitive(T data) noexcept {
        m_data[m_tail] = data;
        reserveBack(1);
    }

    template<typename T>
    void ring_buffer<T>::push(const T& data) noexcept {
        m_data[m_tail] = data;
        reserveBack(1);
    }

    template<typename T>
    void ring_buffer<T>::push(T&& data) noexcept {
        m_data[m_tail] = std::move(data);
        reserveBack(1);
    }

    template<typename T>
    void ring_buffer<T>::pop() noexcept {
        releaseFront(1);
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
    inline int ring_buffer<T>::head() const noexcept {
        return m_head;
    }

    template<typename T>
    inline int ring_buffer<T>::tail() const noexcept {
        return m_tail - m_head - 1;
    }

    template<typename T>
    T& ring_buffer<T>::operator[] (std::size_t index) {
        auto usableIndex = (m_head + index) % m_data.size();

        return m_data[usableIndex];
    }

    template<typename T>
    const T& ring_buffer<T>::operator[] (std::size_t index) const {
        auto usableIndex = (m_head + index) % m_data.size();
        
        return m_data[usableIndex];
    }

}