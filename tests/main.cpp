#include "ctl/ring_buffer.hpp"
#include "ctl/flat_array.hpp"
#include "ctl/flat_string.hpp"
#include "ctl/static_flat_map.hpp"
#include "ctl/table.hpp"
#include <string>
#include <string_view>
#include <iostream>

int main() {
//     // 1. Test ring_buffer
//     ctl::ring_buffer<int> rb(5);
//     rb.push(10);
//     rb.push(20);
//     std::cout << "RingBuffer Front: " << rb[0] << std::endl;

//     // 2. Test flat_array
//     ctl::flat_array<char> grid(10, 10);
//     grid.fill('.');
//     grid(2, 3) = '#';
//     std::cout << "FlatArray (2, 3): " << grid(2, 3) << std::endl;

//     // 3. Test flat_string
//     ctl::flat_string str(5, 5, 'x');
//     std::cout << "FlatString rendered:\n" << str.getData() << std::endl;

//     std::cout << "All CTL structures compiled and tested successfully!" << std::endl;

//     ctl::flat_array<int> nums = {{1, 2, 3}, {3, 4, 5}};
//     for(int i = 0; i < nums.rows(); i++) {
//         for(int j = 0; j < nums.columns(); j++) {
//             std::cout << nums(i, j) << " ";
//         }
//         std::cout << std::endl;
//     }

    // ctl::static_flat_map<std::string, int, 5> map = {{"A", 1}, {"C", 4}, {"D", 3}, {"B", 68}, {"AA", 33}};
    // std::cout << map["A"];

    // auto at = map.at(3);
    // std::cout << at.m_key << ", " << at.m_value;

    ctl::static_flat_map<std::string_view, std::size_t, 6> rowMap = {{"Zero", 0}, {"One", 1}, {"Two", 2}};
    ctl::static_flat_map<std::string_view, std::size_t, 6> colMap = {{"Zero", 0}, {"One", 1}, {"Two", 2}, {"Three", 3}};
    ctl::flat_array<int> data = {
        {0, 0, 0, 0}, {0, 1, 2, 3}, {0, 2, 4, 6}
    };

    ctl::table<int, std::string_view, 6> t1(rowMap, colMap, std::move(data));
    t1("Zero", "Zero") = 6;

    // Row: "Zero"
    std::cout << t1("Zero", "Zero")  << " "
              << t1("Zero", "One")   << " "
              << t1("Zero", "Two")   << " "
              << t1("Zero", "Three") << "\n";

    // Row: "One"
    std::cout << t1("One", "Zero")   << " "
              << t1("One", "One")    << " "
              << t1("One", "Two")    << " "
              << t1("One", "Three")  << "\n";

    // Row: "Two"
    std::cout << t1("Two", "Zero")   << " "
              << t1("Two", "One")    << " "
              << t1("Two", "Two")    << " "
              << t1("Two", "Three")  << "\n";


    return 0;
}