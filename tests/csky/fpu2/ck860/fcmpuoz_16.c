/*
 * Copyright (c) 2021 T-Head Semiconductor Co., Ltd. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

#include "testsuite.h"
#include "fpu_structs.h"

struct op1_res1_f16_s16 data[] = {
    {.op1.f = -1.0,     .res = 0},
    {.op1.d = HpsNaN,   .res = 1},
    {.op1.d = HnqNaN,   .res = 1},
};

void test_fcmpuoz_16(float16 a, int expt)
{
    int res;
    asm ("fcmpuoz.16 %1;\
          movi %0, 1;\
          clrf %0;"
         : "=r"(res)
         : "v"(a.f)
    );
    TEST(res == expt);
}

int main(void)
{
    int i = 0;
    init_testsuite("Testing fpu fcmpuoz.16 instructions.\n");

    for (i = 0; i < sizeof(data) / sizeof(struct op1_res1_f16_s16); i++) {
        test_fcmpuoz_16(data[i].op1, data[i].res);
    }

    return done_testing();
}
