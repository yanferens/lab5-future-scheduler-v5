#include <iostream>
#include <syncstream>
#include <thread>
#include <chrono>
#include <string>
#include <future>

using namespace std;

void runTask(const string &name, chrono::seconds duration) {
    this_thread::sleep_for(duration);
    osyncstream(cout) << name << endl;
}

void chainA() {
    runTask("A1", 7s);
    runTask("A2", 1s);
}

void chainB() {
    runTask("B1", 1s);
    runTask("B2", 7s);
}

void chainC() {
    runTask("C", 1s);
    runTask("F", 1s);
}

pair<future<void>, future<void>> startThreads() {
    return {async(launch::async, chainB), async(launch::async, chainC)};
}

void printResult(chrono::steady_clock::time_point begin) {
    chrono::duration<double> elapsed = chrono::steady_clock::now() - begin;
    cout << "Execution time: " << elapsed.count() << " s" << endl;
    cout << "Work is done!" << endl;
}

void work() {
    auto begin = chrono::steady_clock::now();
    auto [threadB, threadC] = startThreads();
    chainA();
    threadB.get();
    runTask("D", 1s);
    threadC.get();
    printResult(begin);
}

int main() {
    work();
}