#include <iostream>
#include <chrono>
#include "prediction_old.h"

int main() {

    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    prediction_old test;
    test.reading_input("train.csv");
    test.finding_rank();
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;

    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";


    return 0;
}
