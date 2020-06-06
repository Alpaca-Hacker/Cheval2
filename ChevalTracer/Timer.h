#pragma once
#include <chrono>
#include <iomanip>
#include <string>

class Timer
{
public:
    void start()
    {
        startTime_ = std::chrono::system_clock::now();
        bRunning_ = true;
    }

    void stop()
    {
        endTime_ = std::chrono::system_clock::now();
        bRunning_ = false;
    }

    double elapsedMilliseconds() const
    {
        std::chrono::time_point<std::chrono::system_clock> endTime;

        if (bRunning_)
        {
            endTime = std::chrono::system_clock::now();
        }
        else
        {
            endTime = endTime_;
        }

        return std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime_).count();
    }

    double elapsedSeconds() const
    {
        return elapsedMilliseconds() / 1000.0;
    }

	void displayElapsedTime() const
    {
        int hours;
        const int milli = elapsedMilliseconds();
        const int seconds = milli / 1000;
        const int minutes = seconds / 60;
        //hours = minutes / 60;
    	
        std::cout << std::setw(2) << std::setfill('0') << static_cast<int>(minutes) << ":"
    	<< std::setw(2) << std::setfill('0') << static_cast<int>(seconds % 60) << ":"
    	<< std::setw(3) << std::setfill('0') << static_cast<int>(milli % 1000);
    	
    	//<< seconds << " seconds is equivalent to " << int(hours) << " hours " << int(minutes % 60)
     //       << " minutes " << int(seconds % 60) << " seconds.";
    }

private:
    std::chrono::time_point<std::chrono::system_clock> startTime_;
    std::chrono::time_point<std::chrono::system_clock> endTime_;
    bool                                               bRunning_ = false;
};

