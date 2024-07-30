#ifndef GRA_GRALIB_HPP
#define GRA_GRALIB_HPP

#include <iostream>
#include <vector>
#include <random>

int __n, __k, __M;
int __x = 0;
int __calls = 0;
int __gamesRemaining = 100;
int __prev = 0;
bool __initialized = false;
std::mt19937 rng;

void __read() {
    int seed;
    std::cin >> __n >> __k >> __M >> seed;

    rng.seed(seed);
}

void __init() {
    if (!__initialized) {
        __read();
        __initialized = true;
    }
}

int dajN() {
    __init();
    return __n;
}

int dajK() {
    __init();
    return __k;
}

int dajM() {
    __init();
    return __M;
}

int nastepna() {
    __init();

    ++__calls;

    if (__calls > __M) {
        std::cout << "Przekroczono limit zapytan." << std::endl;
        std::exit(0);
    }

    __prev = 1 + rng() % __k;

    return __prev;
}

void zwieksz() {
    __init();

    if (__prev == 0) {
        std::cout << "Program wywoluje zwieksz() bez wczesniejszego wywolania nastepna()." << std::endl;
        std::exit(0);
    }
    if (__x % __prev != 0) {
        std::cout << "Proba zwiekszenia licznika o liczbe niebedaca jego dzielnikiem." << std::endl;
        std::exit(0);
    }

    __x += __prev;
    __prev = 0;

    if (__x > __n) {
        std::cout << "Licznik przekroczyl n." << std::endl;
        std::exit(0);
    }
}

void koniec() {
    __init();

    if (__x != __n) {
        std::cout << "Zla odpowiedz " << __x << std::endl;
        std::exit(0);
    }

    if (__gamesRemaining == 1) {
        std::cout << "OK" << std::endl;
    }
    else if (__gamesRemaining <= 0) {
        std::cout << "Program wywoluje koniec() zbyt wiele razy." << std::endl;
        std::exit(0);
    }

    --__gamesRemaining;
    __x = 0;
    __calls = 0;
    __prev = 0;
}

#endif //GRA_GRALIB_HPP
