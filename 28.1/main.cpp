#include <iostream>
#include <thread>
#include <mutex>
#include <string>
#include <vector>

std::vector<int> times;
std::mutex writeLock;
std::string names[6];
double speed[6];


void swim(double speed, int num){
    int seconds = 0;
    double distance = 100;
    while(distance > 0){
        std::this_thread::sleep_for(std::chrono::seconds(1));
        distance -= speed;
        seconds++;
        if(distance < 0) {
            distance = 0;
            writeLock.lock();
            std::cout << "\nNumber " << num << " finished!";
            writeLock.unlock();
        }
        writeLock.lock();
        std::cout << std::endl << names[num] << " - " << distance;
        writeLock.unlock();
    }
    writeLock.lock();
    times.push_back(seconds);
    writeLock.unlock();
}
int main() {
    for(int i = 0; i < 6; i++){
        std::cout << "\nEnter number " << i << " name: ";
        std::cin >> names[i];
        std::cout << "\nEnter speed: ";
        std::cin >> speed[i];
    }
    std::thread swimming0(swim, speed[0], 0);
    std::thread swimming1(swim, speed[1], 1);
    std::thread swimming2(swim, speed[2], 2);
    std::thread swimming3(swim, speed[3], 3);
    std::thread swimming4(swim, speed[4], 4);
    std::thread swimming5(swim, speed[5], 5);
    swimming0.join();
    swimming1.join();
    swimming2.join();
    swimming3.join();
    swimming4.join();
    swimming5.join();
    for(int i = 0; i < 6; i++){
        std::cout << std::endl << names[i] << " time: " << times[i];
    }
}