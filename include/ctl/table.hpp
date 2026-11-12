#pragma once

#include "ctl/flat_array.hpp"
#include "ctl/static_flat_map.hpp"

namespace ctl {

    template<typename DataType, typename RowKey, std::size_t RowSize, typename ColKey = RowKey, std::size_t ColSize = RowSize>
    class table {
    private:
        flat_array<DataType> m_data;
        static_flat_map<RowKey, std::size_t, RowSize> m_rowIndices;
        static_flat_map<ColKey, std::size_t, ColSize> m_columnIndices;

    public:
        table(static_flat_map<RowKey, std::size_t, RowSize> squareMap);
        table(static_flat_map<RowKey, std::size_t, RowSize> squareMap, flat_array<DataType> data);
        table(static_flat_map<RowKey, std::size_t, RowSize> rowIndices, static_flat_map<ColKey, std::size_t, ColSize> colIndices);
        table(static_flat_map<RowKey, std::size_t, RowSize> rowIndices, static_flat_map<ColKey, std::size_t, ColSize> colIndices, flat_array<DataType> data);

        DataType& operator() (const RowKey& row, const ColKey& col);
    };

}

#include "ctl/table.tpp"