#include <iostream>
#include <random>
#include <chrono>
#include <vector>

using namespace std;
using namespace chrono;

/**
void print_matrix(float mat[][n]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << mat[i][j] << " ";
		}
		cout << "\n";
	}
}
*/

std::vector<float> create_matrix(int n) {
	std::vector<float> matrix(n*n);
	for (int i = 0; i < matrix.size(); i++) {
		matrix[i] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	}

	return matrix;
}

std::vector<float> mat_mul(std::vector<float> a, std::vector<float> b, int n) {
	std::vector<float> mat(n*n);
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				mat[i*n + j] += a[i*n + k] * b[k*n + j];		
			}
		}
	}

	return mat;
}

void benchmark(int n) {
	std::vector<float> mat_a = create_matrix(n);
	std::vector<float> mat_b = create_matrix(n);

    	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	
	std::vector<float> mat_c = mat_mul(mat_a, mat_b, n);

    	high_resolution_clock::time_point t2 = high_resolution_clock::now();
    	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);

    	cout << "n = " << n << ": " << time_span.count() << " seconds.\n";

}

int main() {
	for (int i = 1; i <= 10; i++) {
		benchmark(i*100);
	}

	//benchmark(2000);
}
