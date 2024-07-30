#ifndef __HOMECOMING_H
#define __HOMECOMING_H
#include <cstdio>
#include <cassert>

long long solve(int N, int K, int *A, int *B);

int main() {
  int T; assert(scanf("%d", &T) == 1);
  for(int t = 0; t < T; t++) {
    int N, K; assert(scanf("%d%d", &N, &K) == 2);
    int *A = new int[N];
    int *B = new int[N];
    for(int i = 0; i < N; i++) assert(scanf("%d", &A[i]) == 1);
    for(int i = 0; i < N; i++) assert(scanf("%d", &B[i]) == 1);
    printf("%lld\n", solve(N, K, A, B));
    delete[] A;
    delete[] B;
  }
  return 0;
}
#endif