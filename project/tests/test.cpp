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
#include "find_max.h"
#include "finding_max_paral.h"
#include "utils.h"
}



TEST(Find_max, test1) {
char *test_buf = "irina alferova";
EXPECT_STR_EQ(find_max_word(test_buf), "alferova");
}


TEST(Stress_tests, test_1) {
struct timespec start = {};
struct timespec finish = {};
char *res, *paral_res;
clock_gettime(CLOCK_MONOTONIC, &start);
paral_res = max_word_in_file_mp("project/tests/data/test1.txt");
clock_gettime(CLOCK_MONOTONIC, &finish);
double single_proc_time = (finish.tv_sec - start.tv_sec);
single_proc_time += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
clock_gettime(CLOCK_MONOTONIC, &start);
res = check_convo_mood_mp("/builds/naysudes/howeworks-technpark/project/tests/data/test1.txt");
clock_gettime(CLOCK_MONOTONIC, &finish);
EXPECT_STR_EQ(paral_res, res);
double multy_proc_time = (finish.tv_sec - start.tv_sec);
multy_proc_time += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
std::cout << '\n' << '\n' << "Multy proc time " << multy_proc_time;
std::cout << "\nSingle proc time: " << single_proc_time << '\n' << '\n';
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


