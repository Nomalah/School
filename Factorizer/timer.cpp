#include <iostream>
#include <chrono>
#include "timer.h"

timer::timer(double previous_time){
	this->previous_time = previous_time;
	stopped = 1;
}

void timer::start(){
	start_time = std::chrono::steady_clock::now();
	stopped = 0;
	return;
}

void timer::stop(){
	previous_time += std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - start_time).count();
	stopped = 1;
	return;
}

void timer::reset(bool resume){
	previous_time = 0;
	if (resume)
		start();
	else
		stopped = 1;
	return;
}

void timer::print(){
	if (stopped){
		std::cout << previous_time << '\n';
	}else{
    	std::cout << std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - start_time).count() + previous_time << '\n';
	}
	return;
}

double timer::get(){
	if (stopped){
		return previous_time;
	}else{
    	return std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - start_time).count() + previous_time;
	}
}
	
std::ostream& operator<< (std::ostream& out, const timer& clock)
{
	if (clock.stopped){
		out << clock.previous_time;
	}else{
    	out << std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::steady_clock::now() - clock.start_time).count() + clock.previous_time;
	}
    //out << "+i" << c.imag << endl;
    return out;
}

