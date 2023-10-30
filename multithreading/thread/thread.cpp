#include <iostream>
#include <thread>
#include <mutex>

// Глобальный мьютекс для синхронизации доступа к консоли
std::mutex consoleMutex;

// Функция, которую будет выполнять каждый поток
void threadFunction(int threadID) {
    for (int i = 0; i < 5; ++i) {
        // Захватываем мьютекс перед выводом в консоль
        std::lock_guard<std::mutex> lock(consoleMutex);
        std::cout << "Thread " << threadID << " is running iteration " << i << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}

int main() {
    while (1) {
        const int numThreads = 5;
        std::thread threads[numThreads];

        // Создаем и запускаем потоки
        for (int i = 0; i < numThreads; ++i) {
            threads[i] = std::thread(threadFunction, i + 1);
        }

        // Ждем, пока все потоки завершатся
        for (int i = 0; i < numThreads; ++i) {
            threads[i].join();
        }

        std::cout << "All threads finished " << std::endl;
    }

        return 0;
    
}