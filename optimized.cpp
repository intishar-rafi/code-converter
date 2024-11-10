#include <iostream>
#include <vector>
#include <chrono>
#include <cstdint>
#include <numeric>

class LCG {
public:
    LCG(uint32_t seed, uint32_t a = 1664525, uint32_t c = 1013904223, uint32_t m = 1 << 31)
        : value(seed), a(a), c(c), m(m) {}

    uint32_t next() {
        value = (a * value + c) % m;
        return value;
    }

private:
    uint32_t value;
    const uint32_t a, c, m;
};

int32_t max_subarray_sum(int32_t n, uint32_t seed, int32_t min_val, int32_t max_val) {
    LCG lcg(seed);
    std::vector<int32_t> random_numbers(n);
    for (int32_t &num : random_numbers)
        num = lcg.next() % (max_val - min_val + 1) + min_val;

    int64_t max_sum = std::numeric_limits<int64_t>::min(), current_sum = 0;
    for (int32_t i = 0; i < n; ++i) {
        for (int32_t j = i; j < n; ++j) {
            current_sum += random_numbers[j];
            if (current_sum > max_sum)
                max_sum = current_sum;
        }
        current_sum = 0;
    }
    return static_cast<int32_t>(max_sum);
}

int32_t total_max_subarray_sum(int32_t n, uint32_t initial_seed, int32_t min_val, int32_t max_val) {
    int64_t total_sum = 0;
    LCG lcg(initial_seed);
    for (int i = 0; i < 20; ++i) {
        uint32_t seed = lcg.next();
        total_sum += max_subarray_sum(n, seed, min_val, max_val);
    }
    return static_cast<int32_t>(total_sum);
}

int main() {
    int32_t n = 10000;
    uint32_t initial_seed = 42;
    int32_t min_val = -10;
    int32_t max_val = 10;

    auto start_time = std::chrono::high_resolution_clock::now();
    int32_t result = total_max_subarray_sum(n, initial_seed, min_val, max_val);
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end_time - start_time;

    std::cout << "Total Maximum Subarray Sum (20 runs): " << result << std::endl;
    std::cout << "Execution Time: " << elapsed.count() << " seconds" << std::endl;

    return 0;
}
