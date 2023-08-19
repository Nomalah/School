#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <iostream>

class timer{
	public:
		bool stopped;
		double previous_time;

		timer(double previous_time = 0);
		void start();
		void stop();
		void reset(bool resume = 1);
		void print();
		double get();
		friend std::ostream& operator << (std::ostream& out, const timer& clock);
	private:
		std::chrono::steady_clock::time_point start_time;
};

#endif //TIMER_H