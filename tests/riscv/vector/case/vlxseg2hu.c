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
#include "rvv_insn.h"

struct rvv_reg src0[] = {
    {
        .fixu16 = {
            {0xffa5, 0x0034, 0xff8c, 0x0074, 0xffcd, 0x0075, 0xff92, 0x007a, },
            {0x0060, 0x0019, 0x003c, 0xff91, 0xfffd, 0xffab, 0x0023, 0x0021, },
        },
    },
};

struct rvv_reg src1[] = {
    {
        .fixu32 = {
            {0x00000000, 0x00000004, 0x00000008, 0x0000000c, },
            {0x00000010, 0x00000014, 0x00000018, 0x0000001c, },
        },
    },
};
struct rvv_reg dst0[] = {
    {
        .fixu32 = {
            {0x0000ffa5, 0x0000ff8c, 0x0000ffcd, 0x0000ff92, },
            {0x00000060, 0x0000003c, 0x0000fffd, 0x00000023, },
        },
    },
    {
        .fixu32 = {
            {0x00000034, 0x00000074, 0x00000075, 0x0000007a, },
            {0x00000019, 0x0000ff91, 0x0000ffab, 0x00000021, },
        },
    },
    };


struct rvv_reg res0, res1;

int main(void)
{
    init_testsuite("Testing insn vlxseg2hu\n");

    /* sew 32 */
    test_vlxseg2hu_32(vlmax_32, &pad.fixu32[0], src0[0].fixu16[0], src1[0].fixu32[0], res0.fixu32[0], res1.fixu32[0]);
    result_compare_s32_lmul(res0.fixu32[0], dst0[0].fixu32[0]);
    result_compare_s32_lmul(res1.fixu32[0], dst0[1].fixu32[0]);

    return done_testing();
}
