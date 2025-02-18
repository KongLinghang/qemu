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
#include "test_device.h"
#include "dsp_insn.h"
#define TEST_TIMES      17
int main(void)
{
    int i = 0;

    init_testsuite("Testing insn MULA.U32 \n");

    /*
     * MULA.U32
     * {rn,rz} = (rx * ry) + {rn,rz}, unsigned
     */
    struct ternary64_calculation ter64_sample[TEST_TIMES] = {
        {0x00000001, 0x00000001, 0x0000000000000001, 0x0000000000000002},
        {0x00000001, 0x00000001, 0xffffffffffffffff, 0x0000000000000000},
        {0x00000001, 0x00000001, 0x8000000000000000, 0x8000000000000001},
        {0x00000001, 0x00000001, 0x7fffffffffffffff, 0x8000000000000000},
        {0x00000001, 0xffffffff, 0xffffffffffffffff, 0x00000000fffffffe},
        {0x00000001, 0xffffffff, 0x8000000000000000, 0x80000000ffffffff},
        {0x00000001, 0xffffffff, 0x7fffffffffffffff, 0x80000000fffffffe},
        {0x80000000, 0x80000000, 0xffffffffffffffff, 0x3fffffffffffffff},
        {0x80000000, 0x80000000, 0x8000000000000000, 0xc000000000000000},
        {0x80000000, 0x80000000, 0x7fffffffffffffff, 0xbfffffffffffffff},
        {0x7fffffff, 0xffffffff, 0xffffffffffffffff, 0x7ffffffe80000000},
        {0x7fffffff, 0xffffffff, 0x8000000000000000, 0xfffffffe80000001},
        {0x7fffffff, 0xffffffff, 0x7fffffffffffffff, 0xfffffffe80000000},
        {0x00000000, 0x00000001, 0x0000000000000000, 0x0000000000000000},
        {0x00000001, 0x00000000, 0x0000000000000000, 0x0000000000000000},
    };

    for (i = 0; i < TEST_TIMES; i++) {
        TEST(test_mula_u32(ter64_sample[i].op1, ter64_sample[i].op2,
                           ter64_sample[i].op3) == ter64_sample[i].result);
    }

    return done_testing();
}

