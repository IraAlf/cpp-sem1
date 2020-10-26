//
// Created by irinina on 25.10.2020.
//

#include "gtest/gtest.h"
#include <istream>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <unistd.h>

extern "C" {
#include "../headers/find_max.h"
#include "../headers/finding_max_paral.h"
#include "../headers/utils.h"
}



TEST(Find_max, test1) {
char test_buf[50] = "irina alferova";
EXPECT_STREQ(find_max_word(test_buf, 14), "alferova");
}


TEST(Stress_tests, test_1) {
struct timespec start = {};
struct timespec finish = {};
char *res, *paral_res;
clock_gettime(CLOCK_MONOTONIC, &start);
char name[50] = "project/tests/data/1.txt";
paral_res = max_word_in_file_mp(name);
clock_gettime(CLOCK_MONOTONIC, &finish);
double single_proc_time = (finish.tv_sec - start.tv_sec);
single_proc_time += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
clock_gettime(CLOCK_MONOTONIC, &start);
res = max_word_in_file(name);
clock_gettime(CLOCK_MONOTONIC, &finish);
EXPECT_STREQ(paral_res, res);
double multy_proc_time = (finish.tv_sec - start.tv_sec);
multy_proc_time += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
std::cout << '\n' << '\n' << "Multy proc time " << multy_proc_time;
std::cout << "\nSingle proc time: " << single_proc_time << '\n' << '\n';
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


