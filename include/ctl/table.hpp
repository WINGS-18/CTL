#pragma once

#include "ctl/flat_array.hpp"
#include "ctl/static_enum.hpp"

namespace ctl {

    template<typename DataType, typename RowKey, std::size_t RowSize, typename ColKey = RowKey, std::size_t ColSize = RowSize>
    class table {
    private:
        flat_array<DataType> m_data;
        static_enum<RowKey, RowSize, std::size_t> m_rowIndices;
        static_enum<ColKey, ColSize, std::size_t> m_columnIndices;

    public:
        table(static_enum<RowKey, RowSize, std::size_t> squareMap);
        table(static_enum<RowKey, RowSize, std::size_t> squareMap, flat_array<DataType> data);
        table(static_enum<RowKey, RowSize, std::size_t> rowIndices, static_enum<ColKey, ColSize, std::size_t> colIndices);
        table(static_enum<RowKey, RowSize, std::size_t> rowIndices, static_enum<ColKey, ColSize, std::size_t> colIndices, flat_array<DataType> data);

        DataType& operator() (const RowKey& row, const ColKey& col);
    };

}

#include "ctl/table.tpp"