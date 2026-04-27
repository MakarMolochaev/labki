#pragma once
#include <atomic>
#include <thread>
#include <iostream>
#include <iomanip>

class ProgressBar {
public:
    ProgressBar(int64_t maxProgress) {
        this->maxProgress = maxProgress;
        progress = 0;
        finished = false;
    }

    int64_t maxProgress;
    std::atomic<int64_t> progress;
    std::atomic<bool> finished;
    std::thread progressThread;

    void Start() {
        this->progressThread = std::thread([this]() {
            while (!this->finished) {
                float pct = 100.0f * this->progress / this->maxProgress;
                int pos = 40 * this->progress / this->maxProgress;
                std::cout << "\rRendering: [";
                for (int i = 0; i < 40; ++i)
                    std::cout << (i < pos ? "█" : "░");
                std::cout << "] " << std::fixed << std::setprecision(1) << pct << "%   " << std::flush;
                std::this_thread::sleep_for(std::chrono::milliseconds(16));
            }
            std::cout << "\rRendering: [████████████████████████████████████████] 100.0% - Done.\n";
        });
    }

    void Increment(int64_t value = 1) {
        this->progress.fetch_add(1, std::memory_order_relaxed); 
    }

    void Stop() {
        this->finished = true;
        this->progressThread.join();
    }
};