#include<stubmanagerframework.h>
#include<vector>
#include<string>
#include<cassert>
#include<set>

using namespace std;

constexpr int QUERY = 946149565,
             ANSWER = 345685428,
         IMPOSSIBLE = 547293220;

#ifdef DEBUG
    #define TOO_MANY_QUERIES "Too many queries"
    #define INVALID_QUERY "Invalid call to query"
    #define WRONG_ANSWER "Wrong answer"
    #define WRONG_IMPOSSIBLE "Claimed impossible, but isn't"
    #define INVALID_ANSWER "Invalid arguments to answer"
    #define NO_ANSWER "No answer"
    #define CORRECT "Correct"
    #define WRONG_ANSWER_ADAPTIVE "Wrong answer (adaptive)"
    #define CORRECT_ADAPTIVE "Correct (adaptive)"
    #define WRONG_IMPOSSIBLE_ADAPTIVE "Claimed impossible, but isn't (adaptive)"
    #define SECURITY_VIOLATION "Security violation!"
#else
    #define TOO_MANY_QUERIES "Not correct"
    #define INVALID_QUERY "Not correct"
    #define WRONG_ANSWER "Not correct"
    #define WRONG_IMPOSSIBLE "Not correct"
    #define INVALID_ANSWER "Not correct"
    #define NO_ANSWER "Not correct"
    #define CORRECT "Correct"
    #define WRONG_ANSWER_ADAPTIVE "Not correct"
    #define CORRECT_ADAPTIVE "Correct"
    #define WRONG_IMPOSSIBLE_ADAPTIVE "Not correct"
    #define SECURITY_VIOLATION "Security violation!"
#endif

int N, K, S;
long long A;
vector<long long> seq, min_seq, max_seq;

set<int> queried;
int adaptive_mode;

int read_int_or_fail()
{
    int i;

    if(fscanf(fcommin, "%d", &i) != 1)
        result(0.0, SECURITY_VIOLATION);

    return i;
}

void handle_query()
{
    --S;
    if(S < 0) result(0.0, TOO_MANY_QUERIES);

    int pos = read_int_or_fail() - 1;
    if(pos < 0 or pos >= N) result(0.0, INVALID_QUERY);

    queried.insert(pos);

    fprintf(fcommout, "%lld\n", seq[pos]); fflush(fcommout);
}

long long get_min_value(int i) {
    if(min_seq.empty()) {
        long long minVal = (long long)1;
        min_seq.resize(N);
        for(int j = 0; j < N; ++j) {
            if(queried.count(j))
                min_seq[j] = seq[j];
            else
                min_seq[j] = minVal;
            minVal = min_seq[j]+1;
        }
    }

    return min_seq[i];
}

long long get_max_value(int i) {
    if(max_seq.empty()) {
        long long maxVal = (long long)1e18;
        max_seq.resize(N);
        for(int j = N-1; j >= 0; --j) {
            if(queried.count(j))
                max_seq[j] = seq[j];
            else
                max_seq[j] = maxVal;
            maxVal = max_seq[j]-1;
        }
    }

    return max_seq[i];
}

void handle_answer()
{
    int length = read_int_or_fail();
    if(length == -1) result(0.0, INVALID_ANSWER);
    if(length != K) result(0.0, SECURITY_VIOLATION);

    __int128 sum = 0, minSum = 0, maxSum = 0;
    set<int> indices;

    for(int _ = 0; _ < K; ++_)
    {
        int i = read_int_or_fail() - 1;

        if(i < 0 or i >= N or indices.find(i) != indices.end())
            result(0.0, INVALID_ANSWER);

        indices.insert(i);
        if(adaptive_mode)
        {
            maxSum += get_max_value(i);
            minSum += get_min_value(i);
        }
        else
            sum += seq[i];
    }

    if(adaptive_mode)
    {
        if((__int128) A <= minSum and maxSum <= 2 * (__int128) A)
            result(1.0, CORRECT_ADAPTIVE);
        else
            result(0.0, WRONG_ANSWER_ADAPTIVE);
    }
    else
    {
        if((__int128) A <= sum and sum <= 2 * (__int128) A)
            result(1.0, CORRECT);
        else
            result(0.0, WRONG_ANSWER);
    }
}

void handle_impossible()
{
    if(adaptive_mode)
    {
        // check if the smallest k-1 numbers + the smallest number > A could be a solution
        __int128 minVal = 0;
        for(int i = 0; i < K-1; ++i)
            minVal += get_min_value(i);

        long long biggerThanACandidate = min(max(get_min_value(N-1), A+1), get_max_value(N-1));
        for(int i = K-1; i < N; ++i) {
            long long lowest = min(max(get_min_value(i), A+1), get_max_value(i));
            if(lowest > A)
                biggerThanACandidate = min(biggerThanACandidate, lowest);
        }
        minVal += biggerThanACandidate;
        if((__int128) A <= minVal and minVal <= 2 * (__int128) A)
            result(0.0, WRONG_IMPOSSIBLE_ADAPTIVE);

        // check if the smallest k numbers and the largest k numbers <= A can possibly contain a solution

        int biggestLeqA = 0;
        for(int i = 0; i < N; ++i)
            if(get_min_value(i) <= A)
                biggestLeqA = i;

        if(biggestLeqA >= K - 1) { // we actually have enough elements <= A to form any solutions
            minVal = 0;
            __int128 maxVal = 0;
            for(int i = 0; i < K; ++i)
                minVal += get_min_value(i);

            for(int i = biggestLeqA - K + 1; i <= biggestLeqA; ++i)
                maxVal += get_max_value(i);

            if((__int128) A <= maxVal and minVal <= 2 * (__int128) A)
                result(0.0, WRONG_IMPOSSIBLE_ADAPTIVE);
        }

        result(1.0, CORRECT_ADAPTIVE);
    }
    else
    {
        int sol; assert(fscanf(fok, "%d", &sol) == 1);
        if(sol == 0) result(1.0, CORRECT);
        else         result(0.0, WRONG_IMPOSSIBLE);
    }
}

void check()
{
    message_on_shutdown = true;

    assert(fscanf(fin, "%d %d %d %lld %d", &adaptive_mode, &N, &K, &A, &S) == 5);
    fprintf(fcommout, "%d %d %lld %d\n", N, K, A, S);
    fflush(fcommout);

    for(int i = 0; i < N; ++i)
    {
        long long x;
        assert(fscanf(fin, "%lld", &x) == 1);
        assert(seq.empty() or x > seq.back());
        seq.push_back(x);
    }

    for(;;)
    {
        int type;
        auto fscanf_return = fscanf(fcommin, "%d", &type);

        if(fscanf_return == EOF)    break;
        else if(fscanf_return != 1) result(0.0, SECURITY_VIOLATION);

        switch(type)
        {
            case QUERY:
                handle_query();
                break;

            case ANSWER:
                handle_answer();
                break;

            case IMPOSSIBLE:
                handle_impossible();
                break;

            default:
                result(0.0, SECURITY_VIOLATION);
                break;
        }
    }

    result(0.0, NO_ANSWER);
}
