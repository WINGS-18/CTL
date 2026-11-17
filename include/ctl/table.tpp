#include "ctl/table.hpp"
#include <iostream>

namespace ctl {

    template<typename DataType, typename RowKey, std::size_t RowSize, typename ColKey, std::size_t ColSize>
    table<DataType, RowKey, RowSize, ColKey, ColSize>::table(static_enum<RowKey, RowSize, std::size_t> squareMap) 
        : m_data(RowSize, ColSize) , m_rowIndices(squareMap), m_columnIndices(squareMap) {}

    template<typename DataType, typename RowKey, std::size_t RowSize, typename ColKey, std::size_t ColSize>
    table<DataType, RowKey, RowSize, ColKey, ColSize>::table(static_enum<RowKey, RowSize, std::size_t> squareMap, flat_array<DataType> data)
        : m_data(data) , m_rowIndices(squareMap), m_columnIndices(squareMap) {}
    
    template<typename DataType, typename RowKey, std::size_t RowSize, typename ColKey, std::size_t ColSize>
    table<DataType, RowKey, RowSize, ColKey, ColSize>::table(static_enum<RowKey, RowSize, std::size_t> rowIndices, static_enum<ColKey, ColSize, std::size_t> colIndices)
        : m_data(RowSize, ColSize), m_rowIndices(rowIndices), m_columnIndices(colIndices) {}

    template<typename DataType, typename RowKey, std::size_t RowSize, typename ColKey, std::size_t ColSize>
    table<DataType, RowKey, RowSize, ColKey, ColSize>::table(static_enum<RowKey, RowSize, std::size_t> rowIndices, static_enum<ColKey, ColSize, std::size_t> colIndices, flat_array<DataType> data)
    : m_data(data), m_rowIndices(rowIndices), m_columnIndices(colIndices) {}
    
    template<typename DataType, typename RowKey, std::size_t RowSize, typename ColKey, std::size_t ColSize>
    DataType& table<DataType, RowKey, RowSize, ColKey, ColSize>::operator() (const RowKey& row, const ColKey& col) noexcept {
        return m_data(m_rowIndices[row], m_columnIndices[col]);
    }

    template<typename DataType, typename RowKey, std::size_t RowSize, typename ColKey, std::size_t ColSize>
    const DataType& table<DataType, RowKey, RowSize, ColKey, ColSize>::operator() (const RowKey& row, const ColKey& col) const noexcept {
        return m_data(m_rowIndices[row], m_columnIndices[col]);
    }

    template<typename DataType, typename RowKey, std::size_t RowSize, typename ColKey, std::size_t ColSize>
    DataType& table<DataType, RowKey, RowSize, ColKey, ColSize>::operator() (std::size_t row, std::size_t col) noexcept {
        return m_data(row, col);
    }

    template<typename DataType, typename RowKey, std::size_t RowSize, typename ColKey, std::size_t ColSize>
    const DataType& table<DataType, RowKey, RowSize, ColKey, ColSize>::operator() (std::size_t row, std::size_t col) const noexcept {
        return m_data(row, col);
    }

    template<typename DataType, typename RowKey, std::size_t RowSize, typename ColKey, std::size_t ColSize>
    std::size_t table<DataType, RowKey, RowSize, ColKey, ColSize>::rows() const noexcept {
        return m_data.rows();
    }

    template<typename DataType, typename RowKey, std::size_t RowSize, typename ColKey, std::size_t ColSize>
    std::size_t table<DataType, RowKey, RowSize, ColKey, ColSize>::columns() const noexcept {
        return m_data.columns();
    }

    template<typename DataType, typename RowKey, std::size_t RowSize, typename ColKey, std::size_t ColSize>
    std::size_t table<DataType, RowKey, RowSize, ColKey, ColSize>::size() const noexcept {
        return RowSize * ColSize;
    }

    template<typename DataType, typename RowKey, std::size_t RowSize, typename ColKey, std::size_t ColSize>
    void table<DataType, RowKey, RowSize, ColKey, ColSize>::fill(const DataType& data) noexcept {
        m_data.fill(data);
    }


}