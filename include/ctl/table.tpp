#include "ctl/table.hpp"
#include <iostream>

namespace ctl {

    template<typename DataType, typename RowKey, std::size_t RowSize, typename ColKey, std::size_t ColSize>
    table<DataType, RowKey, RowSize, ColKey, ColSize>::table(static_flat_map<RowKey, std::size_t, RowSize> sqaureMap) 
        : m_data(RowSize, ColSize) , m_rowIndices(sqaureMap), m_columnIndices(sqaureMap) {}

    template<typename DataType, typename RowKey, std::size_t RowSize, typename ColKey, std::size_t ColSize>
    table<DataType, RowKey, RowSize, ColKey, ColSize>::table(static_flat_map<RowKey, std::size_t, RowSize> sqaureMap, flat_array<DataType> data)
        : m_data(data) , m_rowIndices(sqaureMap), m_columnIndices(sqaureMap) {}
    
    template<typename DataType, typename RowKey, std::size_t RowSize, typename ColKey, std::size_t ColSize>
    table<DataType, RowKey, RowSize, ColKey, ColSize>::table(static_flat_map<RowKey, std::size_t, RowSize> rowIndices, static_flat_map<ColKey, std::size_t, ColSize> colIndices)
        : m_data(RowSize, ColSize), m_rowIndices(rowIndices), m_columnIndices(colIndices) {}

    template<typename DataType, typename RowKey, std::size_t RowSize, typename ColKey, std::size_t ColSize>
    table<DataType, RowKey, RowSize, ColKey, ColSize>::table(static_flat_map<RowKey, std::size_t, RowSize> rowIndices, static_flat_map<ColKey, std::size_t, ColSize> colIndices, flat_array<DataType> data)
    : m_data(data), m_rowIndices(rowIndices), m_columnIndices(colIndices) {}
    
    template<typename DataType, typename RowKey, std::size_t RowSize, typename ColKey, std::size_t ColSize>
    DataType& table<DataType, RowKey, RowSize, ColKey, ColSize>::operator() (const RowKey& row, const ColKey& col) {
        return m_data(m_rowIndices[row], m_columnIndices[col]);
    }

}