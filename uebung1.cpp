#include <chrono>
#include <iostream>
#include <vector>

int main() {
	int n = 100000;
	std::vector<double> a(n);
	std::vector<double> b(n);

	for (int i = 0; i < 10; i++) {

		auto time1 = std::chrono::high_resolution_clock::now();
		for (int i = 0; i<n; i++){
	    		a[i]=i;
		}
		auto time2 = std::chrono::high_resolution_clock::now();

		std::cout << "a: " <<std::chrono::duration<double, std::nano>(time2 - time1).count() << std::endl;

		time1 = std::chrono::high_resolution_clock::now();
		for (int i = 0; i<n; i++) {
	    		b[i]=a[i];
		}
		time2 = std::chrono::high_resolution_clock::now();

		std::cout << "b: " <<std::chrono::duration<double, std::nano>(time2 - time1).count() << std::endl;
	
		std::cout << "----------------------" << std::endl;
	}
}
