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
        .fixs16 = {
            {0xffa5, 0xff8c, 0xffcd, 0xff92, 0x0060, 0x003c, 0xfffd, 0x0023, },
            {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, },
        },
    },
    {
        .fixs16 = {
            {0x0034, 0x0074, 0x0075, 0x007a, 0x0019, 0xff91, 0xffab, 0x0021, },
            {0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, },
        },
    },
};

struct rvv_reg dst0[] = {
    {
        .fixs16 = {
            {0xffa5, 0x0034, 0x1111, 0x1111, 0xff8c, 0x0074, 0x1111, 0x1111, },
            {0xffcd, 0x0075, 0x1111, 0x1111, 0xff92, 0x007a, 0x1111, 0x1111, },
        },
    },
};


struct rvv_reg res0, res1;

int main(void)
{
    init_testsuite("Testing insn vssseg2e\n");

    /* sew 16 */
    test_vssseg2e_16(&pad.fixs16[0], src0[0].fixs16[0], src0[1].fixs16[0], res0.fixs16[0]);
    result_compare_s16_lmul(res0.fixs16[0], dst0[0].fixs16[0]);

    return done_testing();
}
