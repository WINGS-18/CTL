#include "ctl/ring_buffer.hpp"
#include "ctl/flat_array.hpp"
#include "ctl/flat_string.hpp"
#include "ctl/static_flat_map.hpp"
#include "ctl/table.hpp"
#include "ctl/static_enum.hpp"
#include <cstddef>
#include <ostream>
#include <string>
#include <string_view>
#include <iostream>
#include <cstdint>

int main() {
    // 1. Test ring_buffer
    // ctl::ring_buffer<int> rb(5);
    // rb.push(10);
    // rb.push(20);
    // std::cout << "RingBuffer Front: " << rb[0] << std::endl;

    // // 2. Test flat_array
    // ctl::flat_array<char> grid(10, 10);
    // grid.fill('.');
    // grid(2, 3) = '#';
    // std::cout << "FlatArray (2, 3): " << grid(2, 3) << std::endl;

    // // 3. Test flat_string
    // ctl::flat_string str(5, 5, 'x');
    // std::cout << "FlatString rendered:\n" << str.getData() << std::endl;

    // std::cout << "All CTL structures compiled and tested successfully!" << std::endl;

    // ctl::flat_array<int> nums = {{1, 2, 3}, {3, 4, 5}};
    // for(int i = 0; i < nums.rows(); i++) {
    //     for(int j = 0; j < nums.columns(); j++) {
    //         std::cout << nums(i, j) << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // ctl::static_flat_map<std::string, int, 8> map = {{"A", 1}, {"C", 4}, {"D", 3}, {"B", 68}, {"AA", 33}};
    // std::cout << map["A"] << "\n";
    // map["H"] = 6;
    // //map["J"] = 6;
    // std::cout << map["H"] << "\n";
    // std::cout << map["J"] << "\n";
    
    // map.insert("F", 15);
    // std::cout << map["F"];

    // auto at = map.at("H");
    // std::cout << "H" << ", " << at << std::endl;

    // std::cout << "cap: " << map.capacity() << std::endl;
    // std::cout << "empty: " << map.empty() << std::endl;
    // std::cout << "size: " << map.size() << std::endl;
    
    // ctl::static_enum<std::string_view, 2, std::size_t> rowMap = {"Zero", "One"};
    // ctl::static_enum<std::string_view, 3, std::size_t> colMap = {"Zero", "One", "Two"};
    // ctl::flat_array<int> data = {
    //     {1, 2, 3}, {2, 4, 6}
    // };

    // ctl::table<int, std::string_view, 2, std::string_view, 3> t1(rowMap, colMap, std::move(data));
    // // Row: "One"
    // std::cout
    //           << t1("Zero", "Zero")    << " "
    //           << t1("Zero", "One")    << " "
    //           << t1("Zero", "Two")  << "\n";

    // // Row: "Two"
    // std::cout
    //           << t1("One", "Zero")    << " "
    //           << t1("One", "One")    << " "
    //           << t1("One", "Two")  << "\n";

    // ctl::static_enum<std::string_view, 5> en = {"Zero", "One", "Two", "Three", "Four"};
    // ctl::static_enum<std::string_view, 5> en2({"Zero", "One", "Two", "Three", "Four"}, 5);

    // std::cout << en["Four"];
    // std::cout << en2["Four"];

    // t1("five", "One");
    // nums(5, 6); //error

    ctl::ring_buffer<int> nums(5);

    nums.push(1);
    nums.push(2);
    nums.push(3);
    // nums.push(4);
    // nums.push(5);

    for(std::size_t i = 0; i < nums.size(); i++) {
        std::cout << nums[i] << ", ";
    }
    std::cout << std::endl;
    
    nums.pop();
    nums.pop();
    nums.push(7);
    nums.push(8);
    // nums.pop();
    // nums.pop();
    // for(std::size_t i = 0; i < nums.size(); i++) {
    //     std::cout << nums[i] << ", ";
    // }
    // std::cout << std::endl;

    std::cout << nums.front() << "\n";
    
    int& val = nums.emplace_back();
    val = 10;
    std::cout << nums.back() << "\n";

    const int& va = nums.back();

    std::cout << va;

    return 0;
}