#include<iostream>
#include<thread>
#include <mutex>
#include <vector>

class Swimmers
{
public:
    std::string name;
    float speed;
    int time;
};

std::vector<Swimmers> result;
Swimmers swimmers[6];
std::mutex print;

void swimmer(Swimmers swimmer)
{
    int i = 1;
    float distance = 0;

    while (distance < 100)
    {
        print.lock();
        std::cout << i << " sec. ";
        distance += swimmer.speed;
        if (distance >= 100)
        {
            swimmer.time = i;
            result.push_back(swimmer);
            distance = 100;
        }
        std::cout << swimmer.name << " " << distance << std::endl;
        i++;
        print.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main()
{
    for (int i = 0; i < 6; i++)
    {
        std::cout << "Enter swimmer's name #" << i + 1 << " ";
        std::cin >> swimmers[i].name;
        std::cout << "Enter speed " << swimmers[i].name << ": ";
        std::cin >> swimmers[i].speed;
    }

    std::thread swimmer1(swimmer,swimmers[0]);
    std::thread swimmer2(swimmer,swimmers[1]);
    std::thread swimmer3(swimmer,swimmers[2]);
    std::thread swimmer4(swimmer,swimmers[3]);
    std::thread swimmer5(swimmer,swimmers[4]);
    std::thread swimmer6(swimmer,swimmers[5]);

    swimmer1.join();
    swimmer2.join();
    swimmer3.join();
    swimmer4.join();
    swimmer5.join();
    swimmer6.join();

    for (int i = 0; i < 6; ++i)
    {
        std::cout << i+1 << " place. " << result[i].name << " " << result[i].time << " sec." << std::endl;
    }


}