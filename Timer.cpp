#include "Timer.h"

void Timer::start() {
    start_time = std::chrono::high_resolution_clock::now();
}

void Timer::stop() {
    stop_time = std::chrono::high_resolution_clock::now();
}

void Timer::print(const std::string& label) const {
    std::cout << label << ": " << elapsed_ms() << " ms" << std::endl;
}

double Timer::elapsed_ms() const {
    return std::chrono::duration<double, std::milli>(stop_time - start_time).count();
}
