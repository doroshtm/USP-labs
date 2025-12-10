#include <stdio.h>
#include <time.h>
#include <stdint.h>

int main() {
    const uint64_t N = 1000000000ULL;
    // volatile evita otimização de remoção
    volatile uint64_t acc = 0;
    struct timespec t0, t1;

    clock_gettime(CLOCK_MONOTONIC, &t0);
    for (uint64_t i = 0; i < N; ++i) {
        acc += i;
    }
    clock_gettime(CLOCK_MONOTONIC, &t1);

    double secs = (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / 1e9;
    double ops_per_sec = (double)N / secs;

    printf("Resultado: %llu (ignorar)\n", (unsigned long long)acc);
    printf("Tempo: %.6f s\n", secs);
    printf("Ops/s (somas): %.3f\n", ops_per_sec);
}
