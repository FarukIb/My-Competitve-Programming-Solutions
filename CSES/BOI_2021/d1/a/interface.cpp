#include<vector>
#include<cstdio>
#include<cassert>
#include<cstdlib>
#include"books.h"
#include "books_sample.cpp"

using namespace std;
namespace {
    constexpr int QUERY = 946149565,
                ANSWER = 345685428,
            IMPOSSIBLE = 547293220;
    int K;
}
int safely_read_int()
{
    int i;
    if(scanf("%d", &i)) {}
    return i;
}

long long safely_read_ll()
{
    long long l;
    if(scanf("%lld", &l)) {}
    return l;
}

void answer(std::vector<int> a)
{
    if(a.size() != (size_t) K)
    {
        printf("%d -1\n", ANSWER);
        fflush(stdout);
    }

    else
    {
        printf("%d %d", ANSWER, (int) a.size());
        for(int x : a) printf(" %d", x);
        printf("\n"); fflush(stdout);
    }

    exit(0);
}

void impossible()
{
    printf("%d\n", IMPOSSIBLE); fflush(stdout);
    exit(0);
}

long long skim(int pos)
{
    printf("%d %d\n", QUERY, pos); fflush(stdout);
    long long answer = safely_read_ll();
    if(answer == -1) exit(0);
    return answer;
}

int main()
{
    int N = safely_read_int();
    K = safely_read_int();
    long long A = safely_read_ll();
    int S = safely_read_int();
    solve(N, K, A, S);
    return 0;
}
