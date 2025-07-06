#include "tests.h"

int main(int argc, const char **argv){
    bubblesort_test(argc, argv);
    mergesort_test(argc, argv);
    int permuteData[] = {
        6,
        3, 19, -5, 17, -4, 100
    };
    permute_test(permuteData);
    return 0;
}