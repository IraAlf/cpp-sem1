#include<stdlib.h>
#include <gtest/gtest.h>

extern "C" {
    #include "alignment.h"
}


TEST(Alignment, first) {
struct element **elements = (struct element**)malloc(2 * sizeof (struct element*));
elements[0] = (struct element*)malloc(2 * sizeof (struct element));
elements[1] = (struct element*)malloc(4 * sizeof (struct element));

struct element el1;
el1.value = 1;
el1.ptr = elements[0];
elements[0][0] = el1;

el1.value = 2;
el1.ptr = NULL;
elements[0][1] = el1;

el1.value = 1;
el1.ptr = elements[1];
elements[1][0] = el1;

el1.value = 2;
el1.ptr = elements[0] + 1;
elements[1][1] = el1;

el1.value = 3;
el1.ptr = elements[0] + 2;
elements[1][2] = el1;

el1.value = 4;
el1.ptr = NULL;
elements[1][3] = el1;


struct element **elements2 = (struct element**)malloc(2 * sizeof (struct element*));
elements2[0] = (struct element*)malloc(4 * sizeof ( struct element));
elements2[1] = (struct element*)malloc(4 * sizeof ( struct element));


el1.value = 1;
el1.ptr = elements[0];
elements[0][0] = el1;

el1.value = 2;
el1.ptr = elements[0] + 1;
elements[0][1] = el1;

el1.value = 0;
el1.ptr = elements[0] + 2;
elements[0][2] = el1;

el1.value = 0;
el1.ptr = elements[0] + 3;
elements[0][3] = el1;

el1.value = 1;
el1.ptr = elements[1];
elements[1][0] = el1;

el1.value = 2;
el1.ptr = elements[0] + 1;
elements[1][1] = el1;

el1.value = 3;
el1.ptr = elements[0] + 2;
elements[1][2] = el1;

el1.value = 4;
el1.ptr = elements[0] + 3;
elements[1][3] = el1;

struct element **element_res = alignment(elements, 2, 4);

for (int i = 0; i < 2; i++)
    for (int j = 0; j < 4; j++)
        ASSERT_EQ(elements2[i][j].value, element_res[i][j].value);
}

}

int main(int argc, char** argv) {
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
