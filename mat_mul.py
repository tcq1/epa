import random
from timeit import default_timer as timer

def create_matrix(n):
    matrix = [None] * n * n
    for i in range(n*n):
        matrix[i] = random.random()

    return matrix

def mat_mul(a, b, n):
    matrix = [0] * n * n
    for i in range(n):
        for j in range(n):
            for k in range(n):
               matrix[i*n+j] = a[i*n+k] * b[k*n+j]

    return matrix

def benchmark(n):
    mat_a = create_matrix(n)
    mat_b = create_matrix(n)

    start = timer()

    mat_c = mat_mul(mat_a, mat_b, n)
    
    end = timer()
    duration = (end-start)
    print('n = {}: {}s'.format(n, duration))

def main():
    for i in range(1, 10):
        benchmark(i*100)

if __name__ == '__main__':
    main()
