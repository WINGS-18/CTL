// // // #include "ctl/ring_buffer.hpp"
// // // #include <queue>
// // // #include <chrono>
// // // #include <iostream>

// // // constexpr int OPERATIONS = 10'000'000; // 10 Million pushes & pops
// // // constexpr std::size_t CAPACITY = 64;   // Typical buffer size for input/events

// // // // volatile prevents the -O3 compiler from deleting the loop!
// // // volatile int sink = 0;

// // // void benchmark_std_queue() {
// // //     std::queue<int> q;

// // //     auto start = std::chrono::high_resolution_clock::now();

// // //     for (int i = 0; i < OPERATIONS; ++i) {
// // //         q.push(i);
// // //         if (q.size() >= CAPACITY) {
// // //             sink = q.front();
// // //             q.pop();
// // //         }
// // //     }
// // //     while (!q.empty()) {
// // //         sink = q.front();
// // //         q.pop();
// // //     }

// // //     auto end = std::chrono::high_resolution_clock::now();
// // //     std::chrono::duration<double, std::milli> elapsed = end - start;
// // //     std::cout << "std::queue (std::deque): " << elapsed.count() << " ms\n";
// // // }

// // // void benchmark_ctl_ring_buffer() {
// // //     ctl::ring_buffer<int> rb(CAPACITY);

// // //     auto start = std::chrono::high_resolution_clock::now();

// // //     for (int i = 0; i < OPERATIONS; ++i) {
// // //         rb.push(i);
// // //         if (rb.size() >= CAPACITY) {
// // //             sink = rb[0];
// // //             rb.pop();
// // //         }
// // //     }
// // //     while (!rb.empty()) {
// // //         sink = rb[0];
// // //         rb.pop();
// // //     }

// // //     auto end = std::chrono::high_resolution_clock::now();
// // //     std::chrono::duration<double, std::milli> elapsed = end - start;
// // //     std::cout << "ctl::ring_buffer:        " << elapsed.count() << " ms\n";
// // // }

// // // int main() {
// // //     std::cout << "--- Benchmarking " << OPERATIONS << " Operations (Queue Capacity: " << CAPACITY << ") ---\n\n";

// // //     benchmark_std_queue();
// // //     benchmark_ctl_ring_buffer();

// // //     std::cout << "\nBenchmark complete!\n";
// // //     return 0;
// // // }

// // #include "ctl/flat_array.hpp"
// // #include <vector>
// // #include <chrono>
// // #include <iostream>

// // constexpr std::size_t ROWS = 1000;
// // constexpr std::size_t COLS = 1000;
// // constexpr int PASSES = 100; // 100 Passes = 100,000,000 Cell Accesses

// // volatile int sink = 0;

// // void benchmark_nested_vector() {
// //     // 1,001 separate allocations scattered across RAM!
// //     std::vector<std::vector<int>> grid(ROWS, std::vector<int>(COLS, 0));

// //     auto start = std::chrono::high_resolution_clock::now();

// //     for (int p = 0; p < PASSES; ++p) {
// //         for (std::size_t r = 0; r < ROWS; ++r) {
// //             for (std::size_t c = 0; c < COLS; ++c) {
// //                 grid[r][c] += 1;
// //                 sink = grid[r][c];
// //             }
// //         }
// //     }

// //     auto end = std::chrono::high_resolution_clock::now();
// //     std::chrono::duration<double, std::milli> elapsed = end - start;
// //     std::cout << "std::vector<std::vector<int>> (1,001 heap allocations): " << elapsed.count() << " ms\n";
// // }

// // void benchmark_ctl_flat_array() {
// //     // 1 single contiguous allocation!
// //     ctl::flat_array<int> grid(ROWS, COLS, 0);

// //     auto start = std::chrono::high_resolution_clock::now();

// //     for (int p = 0; p < PASSES; ++p) {
// //         for (std::size_t r = 0; r < ROWS; ++r) {
// //             for (std::size_t c = 0; c < COLS; ++c) {
// //                 grid(c, r) += 1; // (x = c, y = r)
// //                 sink = grid(c, r);
// //             }
// //         }
// //     }

// //     auto end = std::chrono::high_resolution_clock::now();
// //     std::chrono::duration<double, std::milli> elapsed = end - start;
// //     std::cout << "ctl::flat_array<int>          (1 single heap allocation):   " << elapsed.count() << " ms\n";
// // }

// // int main() {
// //     std::cout << "--- Benchmarking 2D Grid (" << ROWS << "x" << COLS << ") across " << PASSES << " Passes (100,000,000 ops) ---\n\n";

// //     benchmark_nested_vector();
// //     benchmark_ctl_flat_array();

// //     std::cout << "\nBenchmark complete!\n";
// //     return 0;
// // }

// #include "ctl/flat_array.hpp"
// #include <vector>
// #include <chrono>
// #include <iostream>

// constexpr std::size_t ROWS = 2000;
// constexpr std::size_t COLS = 2000;
// constexpr int PASSES = 10;

// volatile int sink = 0;

// void test_allocation_speed() {
//     std::cout << "--- 1. Allocation Speed (Creating 2000x2000 Grids) ---\n";

//     // Benchmark vector<vector> (2,001 heap allocations!)
//     auto start1 = std::chrono::high_resolution_clock::now();
//     std::vector<std::vector<int>> nested(ROWS, std::vector<int>(COLS, 0));
//     auto end1 = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<double, std::milli> ms1 = end1 - start1;
//     std::cout << "vector<vector> allocation (2,001 calls): " << ms1.count() << " ms\n";

//     // Benchmark flat_array (1 single heap allocation!)
//     auto start2 = std::chrono::high_resolution_clock::now();
//     ctl::flat_array<int> flat(ROWS, COLS, 0);
//     auto end2 = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<double, std::milli> ms2 = end2 - start2;
//     std::cout << "ctl::flat_array allocation (1 call):      " << ms2.count() << " ms\n\n";
// }

// void test_column_traversal_cache_misses() {
//     std::cout << "--- 2. Vertical Column Traversal (The Cache-Miss Test) ---\n";
//     std::vector<std::vector<int>> nested(ROWS, std::vector<int>(COLS, 0));
//     ctl::flat_array<int> flat(ROWS, COLS, 0);

//     // Benchmark vector<vector> column-major
//     auto start1 = std::chrono::high_resolution_clock::now();
//     for (int p = 0; p < PASSES; ++p) {
//         for (std::size_t c = 0; c < COLS; ++c) {
//             for (std::size_t r = 0; r < ROWS; ++r) {
//                 nested[r][c] += 1;
//                 sink = nested[r][c];
//             }
//         }
//     }
//     auto end1 = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<double, std::milli> ms1 = end1 - start1;
//     std::cout << "vector<vector> Column-Traversal: " << ms1.count() << " ms\n";

//     // Benchmark flat_array column-major
//     auto start2 = std::chrono::high_resolution_clock::now();
//     for (int p = 0; p < PASSES; ++p) {
//         for (std::size_t c = 0; c < COLS; ++c) {
//             for (std::size_t r = 0; r < ROWS; ++r) {
//                 flat(c, r) += 1;
//                 sink = flat(c, r);
//             }
//         }
//     }
//     auto end2 = std::chrono::high_resolution_clock::now();
//     std::chrono::duration<double, std::milli> ms2 = end2 - start2;
//     std::cout << "ctl::flat_array Column-Traversal: " << ms2.count() << " ms\n";
// }

// int main() {
//     test_allocation_speed();
//     test_column_traversal_cache_misses();
//     return 0;
// }

#include "ctl/flat_string.hpp"
#include <vector>
#include <string>
#include <chrono>
#include <iostream>

constexpr std::size_t ROWS = 30;
constexpr std::size_t COLS = 80;
constexpr int FRAMES = 100'000; // 100,000 Frames of gameplay rendering!

volatile std::size_t sink = 0;

void benchmark_vector_of_strings() {
    std::vector<std::string> frame(ROWS, std::string(COLS, ' '));

    auto start = std::chrono::high_resolution_clock::now();

    for (int f = 0; f < FRAMES; ++f) {
        // 1. Draw entities (walls on borders, player at center)
        for (std::size_t r = 0; r < ROWS; ++r) {
            frame[r][0] = '#';
            frame[r][COLS - 1] = '#';
        }
        frame[15][40] = '@';

        // 2. To avoid cursor flickering, assemble a single frame buffer
        std::string displayBuffer;
        displayBuffer.reserve((ROWS * COLS) + ROWS);
        for (const auto& row : frame) {
            displayBuffer += row;
            displayBuffer += '\n';
        }

        sink += displayBuffer.size();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms = end - start;
    std::cout << "std::vector<std::string> (Row Assembly + Concatenation): " << ms.count() << " ms\n";
}

void benchmark_ctl_flat_string() {
    ctl::flat_string frame(ROWS, COLS, ' ');

    auto start = std::chrono::high_resolution_clock::now();

    for (int f = 0; f < FRAMES; ++f) {
        // 1. Draw entities directly via 2D coordinates (x, y)
        for (std::size_t r = 0; r < ROWS; ++r) {
            frame(0, r) = '#';
            frame(COLS - 1, r) = '#';
        }
        frame(40, 15) = '@';

        // 2. Display buffer: 0 ms! Already pre-baked with '\n' in place!
        sink += frame.getData().size();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms = end - start;
    std::cout << "ctl::flat_string         (Pre-baked '\\n', Zero Concatenation): " << ms.count() << " ms\n";
}

int main() {
    std::cout << "--- Benchmarking Terminal Frame Blitting (30x80 Screen) across " << FRAMES << " Frames ---\n\n";

    benchmark_vector_of_strings();
    benchmark_ctl_flat_string();

    std::cout << "\nBenchmark complete!\n";
    return 0;
}