#include <iostream>
#include <math.h>
#include "timer.h"

using namespace std;

long long max(long long a, long long b){
	return a > b ? a : b;
}

int main() {
  	cout << "Hello World!\n";
	long long n_size = 10;

	timer clock;
	clock.start();

	cout << "n_len  - " << 2 << endl;  
	cout << "n_max  - " << 9 << endl;
	cout << "n_min  - " << 4 << endl;
	cout << "81 -> 8 + 1 = 9" << endl;

	for (int n_len = 4; n_len <= 12; n_len += 2){
		n_size *= 10;
		long long n_max = n_size - 1; 
		long long n_min = (double)n_size/sqrt(10)+1;
		
		cout << "n_len  - " << n_len << endl;  
		//cout << "n_size - " << n_size << endl;
		cout << "n_max  - " << n_max << endl;
		cout << "n_min  - " << n_min << endl;
		long long tests = 0;
		for (long long n1 = n_size/10; n1 < n_size; n1+=2){
			for (int n2 = max(n_min - n1, 0); n2 < n_size; n2++){
				tests++;
				long long temp = n1 + n2;
				long long full_num = temp*temp;
				long long number = n1 * n_size + n2;

				if(full_num > number) break;
				else if(full_num == number){
					cout << full_num << " -> " << n1 << " + " << n2 << " = " << temp << "\n";
					n_min = temp;
					break;
				}
			}
		}
				
		cout << "Calculated " << tests << " tests\n";
	}
	clock.stop();
	clock.print();
}


