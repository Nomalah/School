// Written by Dallas Hart
// Copyright @2022

#include <stdio.h>

#include "manip.h"

int main(void) {
    printf("Hello World\n");
    int64_t res = multiplyByFive(20);
    printf("Result: %lld\n", res);
    return 0;
}