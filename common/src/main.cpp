#include "tests.h"

int main(int argc, const char **argv){
    bubblesort_test(argc, argv);
    mergesort_test(argc, argv);
    char permuteData[] = {
        6,0,0,0,
        3, 19, -5, 17, -4, 100
    };
    permute_test(permuteData);
    return 0;
}