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

void test_fldmus()
{
    float f[4] = {1.0, 2.0, 3.0, 4.0};
    float fldmus_res[4];
    int bias;
    asm volatile ("mov r0, %2;\
                  mov r1, %1;\
                  fldmu.32 vr0-vr3, (r0);\
                  fstmu.32 vr0-vr3, (r1);\
                  sub %0, r0, %2"
                  : "=&r"(bias)
                  : "r"(&fldmus_res), "r"(&f)
                  : "vr0", "vr1", "vr2", "vr3", "r0", "r1"
    );
    TEST(f[0] == fldmus_res[0]
        && f[1] == fldmus_res[1]
        && f[2] == fldmus_res[2]
        && f[3] == fldmus_res[3]
        && bias == 16);
}

int main(void)
{
    int i = 0;
    init_testsuite("Testing fpu fldmus instructions.\n");
    test_fldmus();

    return done_testing();
}
