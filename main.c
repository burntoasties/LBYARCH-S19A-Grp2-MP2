/*
=======================================================
LBYARCH S19-A
Authors:
- Sophia Kylie Avelino
- Anton Miguel Borromeo

[MCO2] x86-to-C Interface Programming
=======================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <malloc.h>
#include <string.h>
#include <time.h>

extern float sdot_asm(float *A, float *B, int n);

float sdot_c(float *A, float *B, int n) {
    float sum = 0.0f;
    for (int i = 0; i < n; ++i)
        sum += A[i] * B[i];
    return sum;
}

double now_ms(void) {
    static LARGE_INTEGER freq = {0};
    LARGE_INTEGER t;
    if (!freq.QuadPart)
        QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&t);
    return (double)t.QuadPart * 1000.0 / (double)freq.QuadPart;
}

// for debug
void print_vector(float *v, int n, const char *name) {
    printf("%s = [ ", name);
    for (int i = 0; i < n; ++i)
        printf("%.1f ", v[i]);
    printf("]\n");
}

void run_debug_mode(void) {
    printf("=== DEBUG MODE ===\n");

    int n = 5;
    printf("Vector length: %d\n\n", n);

    float *A = (float*)_aligned_malloc(n * sizeof(float), 32);
    float *B = (float*)_aligned_malloc(n * sizeof(float), 32);

    srand((unsigned)time(NULL));
    for (int i = 0; i < n; ++i) {
        A[i] = (float)(rand() % 1000) / 10.0f;
        B[i] = (float)(rand() % 1000) / 10.0f;
    }

    print_vector(A, n, "A");
    print_vector(B, n, "B");

    double t0 = now_ms();
    float c_res = sdot_c(A, B, n);
    double t1 = now_ms();

    double t2 = now_ms();
    float asm_res = sdot_asm(A, B, n);
    double t3 = now_ms();

    printf("\nC result:   %.9f\n", c_res);
    printf("ASM result: %.9f\n", asm_res);

    printf("\nC time:   %.6f ms\n", t1 - t0);
    printf("ASM time: %.6f ms\n\n", t3 - t2);

    _aligned_free(A);
    _aligned_free(B);
}

void run_benchmark_mode(void) {
    printf("=== BENCHMARK MODE ===\n");

    size_t sizes[] = {1<<20, 1<<24, 1<<30};
    int num_sizes = sizeof(sizes)/sizeof(sizes[0]);
    int runs = 20;

    for (int s = 0; s < num_sizes; s++) {
        size_t n = sizes[s];
        printf("\nVector length: %zu\n", n);

        float *A = (float*)_aligned_malloc(n * sizeof(float), 32);
        float *B = (float*)_aligned_malloc(n * sizeof(float), 32);

        if (!A || !B) {
            printf("ERROR: Not enough RAM for n = %zu\n", n);
            if (A) _aligned_free(A);
            if (B) _aligned_free(B);
            continue;
        }

        for (size_t i = 0; i < n; ++i) {
            A[i] = (float)(rand() % 1000) / 10.0f;
            B[i] = (float)(rand() % 1000) / 10.0f;
        }

        double c_total = 0.0;
        double asm_total = 0.0;

        for (int r = 0; r < runs; r++) {
            // C
            double t0 = now_ms();
            volatile float rc = sdot_c(A, B, (int)n);
            double t1 = now_ms();
            c_total += (t1 - t0);

            // ASM
            double t2 = now_ms();
            volatile float ra = sdot_asm(A, B, (int)n);
            double t3 = now_ms();
            asm_total += (t3 - t2);
        }

        printf("C total time  (20 runs): %.6f ms\n", c_total);
        printf("C average time:         %.6f ms\n", c_total / runs);

        printf("ASM total time  (20 runs): %.6f ms\n", asm_total);
        printf("ASM average time:         %.6f ms\n", asm_total / runs);

        _aligned_free(A);
        _aligned_free(B);
    }
}

int main(int argc, char *argv[]) {
    int debug_mode = 0;

    if (argc > 1) {
        if (strcmp(argv[1], "debug") == 0) {
            debug_mode = 1;
        } else if (strcmp(argv[1], "bench") == 0) {
            debug_mode = 0;
        } else {
            printf("Unknown mode '%s'. Use:\n", argv[1]);
            printf("  program.exe debug\n");
            printf("  program.exe bench\n");
            return 1;
        }
    } else {
        // Default to debug
        debug_mode = 1;
    }

    if (debug_mode)
        run_debug_mode();
    else
        run_benchmark_mode();

    return 0;
}



