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
 * Lesser General Public License  *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

#include "testsuite.h"
#include "rvv_insn.h"

struct rvv_reg src0[] = {
    {
        .fixu64 = {
            {0x3970b5993ab1f212, 0xc6a630b347e7377b, },
            {0x3970b5993ab1f212, 0xc6a630b347e7377b, },
            {0x3970b5993ab1f212, 0xc6a630b347e7377b, },
            {0x3970b5993ab1f212, 0xc6a630b347e7377b, },
        },
        .fixu32 = {
            {0xcfe06686, 0x8262f661, 0x15fc5221, 0xd6b9745a, },
            {0xcfe06686, 0x8262f661, 0x15fc5221, 0xd6b9745a, },
            {0xcfe06686, 0x8262f661, 0x15fc5221, 0xd6b9745a, },
            {0xcfe06686, 0x8262f661, 0x15fc5221, 0xd6b9745a, },
        },
        .fixu16 = {
            {0xd6d6, 0x51f2, 0x10ef, 0x0ea1, 0xa349, 0x4d3f, 0x475d, 0xa164, },
            {0xd6d6, 0x51f2, 0x10ef, 0x0ea1, 0xa349, 0x4d3f, 0x475d, 0xa164, },
            {0xd6d6, 0x51f2, 0x10ef, 0x0ea1, 0xa349, 0x4d3f, 0x475d, 0xa164, },
            {0xd6d6, 0x51f2, 0x10ef, 0x0ea1, 0xa349, 0x4d3f, 0x475d, 0xa164, },
        },
        .fixu8 = {
            {0xa5, 0x34, 0x8c, 0x74, 0xcd, 0x75, 0x92, 0x7a, 0x60, 0x19, 0x3c, 0x91, 0xfd, 0xab, 0x23, 0x21, },
            {0xa5, 0x34, 0x8c, 0x74, 0xcd, 0x75, 0x92, 0x7a, 0x60, 0x19, 0x3c, 0x91, 0xfd, 0xab, 0x23, 0x21, },
            {0xa5, 0x34, 0x8c, 0x74, 0xcd, 0x75, 0x92, 0x7a, 0x60, 0x19, 0x3c, 0x91, 0xfd, 0xab, 0x23, 0x21, },
            {0xa5, 0x34, 0x8c, 0x74, 0xcd, 0x75, 0x92, 0x7a, 0x60, 0x19, 0x3c, 0x91, 0xfd, 0xab, 0x23, 0x21, },
        },
    },
};

struct rvv_reg src1[] = {
    {
        .fixu64 = {
            {0x07d215928aa0d7b6, 0x07186161e5f9e80f, },
            {0x07d215928aa0d7b6, 0x07186161e5f9e80f, },
        },
        .fixu32 = {
            {0x7794d541, 0xf1bfac15, 0x67e3b37f, 0x12df3e7c, },
            {0x7794d541, 0xf1bfac15, 0x67e3b37f, 0x12df3e7c, },
        },
        .fixu16 = {
            {0x4fb8, 0x39b3, 0x6744, 0xfa98, 0xce81, 0x997d, 0x301c, 0xcfb5, },
            {0x4fb8, 0x39b3, 0x6744, 0xfa98, 0xce81, 0x997d, 0x301c, 0xcfb5, },
        },
        .fixu8 = {
            {0x21, 0xb6, 0x8d, 0x3a, 0xe2, 0x09, 0x90, 0x15, 0x2c, 0x13, 0xac, 0x86, 0x28, 0xce, 0x4f, 0xbb, },
            {0x21, 0xb6, 0x8d, 0x3a, 0xe2, 0x09, 0x90, 0x15, 0x2c, 0x13, 0xac, 0x86, 0x28, 0xce, 0x4f, 0xbb, },
        },
    },
};

struct rvv_reg dst_vl[] = {
    {
        .fixu8 = {
            {0x6b, 0x47, 0x00, 0x03, 0xd2, 0x26, 0x5d, 0x0b, 0x0d, 0x3e, 0x01, 0x3a, 0xa3, 0x01, 0x00, 0x14, },
            {0x6b, 0x47, 0x00, 0x03, 0xd2, 0x26, 0x5d, 0x0b, 0x0d, 0x3e, 0x01, 0x3a, 0xa3, 0x01, 0x00, 0x00, },
        },
        .fixu16 = {
            {0x00cf, 0x104c, 0xc522, 0x00d6, 0x3343, 0x0004, 0x0001, 0x06b5, },
            {0x00cf, 0x104c, 0xc522, 0x00d6, 0x3343, 0x0004, 0x0001, 0x0000, },
        },
        .fixu32 = {
            {0x9d58f909, 0x31859a3f, 0x00000000, 0x0000000c, },
            {0x9d58f909, 0x31859a3f, 0x00000000, 0x00000000, },
        },
    },
};

struct rvv_reg dst_even[] = {
    {
        .fixu8 = {
            {0x6b, 0x11, 0x00, 0x11, 0xd2, 0x11, 0x5d, 0x11, 0x0d, 0x11, 0x01, 0x11, 0xa3, 0x11, 0x00, 0x11, },
            {0x6b, 0x11, 0x00, 0x11, 0xd2, 0x11, 0x5d, 0x11, 0x0d, 0x11, 0x01, 0x11, 0xa3, 0x11, 0x00, 0x11, },
        },
        .fixu16 = {
            {0x00cf, 0x1111, 0xc522, 0x1111, 0x3343, 0x1111, 0x0001, 0x1111, },
            {0x00cf, 0x1111, 0xc522, 0x1111, 0x3343, 0x1111, 0x0001, 0x1111, },
        },
        .fixu32 = {
            {0x9d58f909, 0x11111111, 0x00000000, 0x11111111, },
            {0x9d58f909, 0x11111111, 0x00000000, 0x11111111, },
        },
    },
};

struct rvv_reg dst_odd[] = {
    {
        .fixu8 = {
            {0x11, 0x47, 0x11, 0x03, 0x11, 0x26, 0x11, 0x0b, 0x11, 0x3e, 0x11, 0x3a, 0x11, 0x01, 0x11, 0x14, },
            {0x11, 0x47, 0x11, 0x03, 0x11, 0x26, 0x11, 0x0b, 0x11, 0x3e, 0x11, 0x3a, 0x11, 0x01, 0x11, 0x14, },
        },
        .fixu16 = {
            {0x1111, 0x104c, 0x1111, 0x00d6, 0x1111, 0x0004, 0x1111, 0x06b5, },
            {0x1111, 0x104c, 0x1111, 0x00d6, 0x1111, 0x0004, 0x1111, 0x06b5, },
        },
        .fixu32 = {
            {0x11111111, 0x31859a3f, 0x11111111, 0x0000000c, },
            {0x11111111, 0x31859a3f, 0x11111111, 0x0000000c, },
        },
    },
};


struct rvv_reg res;

int main(void)
{
    int i = 0;
    init_testsuite("Testing insn vnsrl.vv\n");

    /* int8_t vnsrl */
    test_vnsrl_vv_8(vlmax_8 - 1, src0[i].fixu16[0], src1[i].fixu8[0], res.fixu8[0], pad.fixu8[0]);
    result_compare_u8_lmul(res.fixu8[0], dst_vl[i].fixu8[0]);

    test_vnsrl_vv_8_vm(src0[i].fixu16[0], src1[i].fixu8[0], res.fixu8[0], vme.fixu8, pad.fixu8[0]);
    result_compare_u8_lmul(res.fixu8[0], dst_even[i].fixu8[0]);

    test_vnsrl_vv_8_vm(src0[i].fixu16[0], src1[i].fixu8[0], res.fixu8[0], vmo.fixu8, pad.fixu8[0]);
    result_compare_u8_lmul(res.fixu8[0], dst_odd[i].fixu8[0]);

    /* int16_t vnsrl */
    test_vnsrl_vv_16(vlmax_16 - 1, src0[i].fixu32[0], src1[i].fixu16[0], res.fixu16[0], pad.fixu8[0]);
    result_compare_u16_lmul(res.fixu16[0], dst_vl[i].fixu16[0]);

    test_vnsrl_vv_16_vm(src0[i].fixu32[0], src1[i].fixu16[0], res.fixu16[0], vme.fixu16, pad.fixu8[0]);
    result_compare_u16_lmul(res.fixu16[0], dst_even[i].fixu16[0]);

    test_vnsrl_vv_16_vm(src0[i].fixu32[0], src1[i].fixu16[0], res.fixu16[0], vmo.fixu16, pad.fixu8[0]);
    result_compare_u16_lmul(res.fixu16[0], dst_odd[i].fixu16[0]);

    /* int32_t vnsrl */
    test_vnsrl_vv_32(vlmax_32 - 1, src0[i].fixu64[0], src1[i].fixu32[0], res.fixu32[0], pad.fixu8[0]);
    result_compare_u32_lmul(res.fixu32[0], dst_vl[i].fixu32[0]);

    test_vnsrl_vv_32_vm(src0[i].fixu64[0], src1[i].fixu32[0], res.fixu32[0], vme.fixu32, pad.fixu8[0]);
    result_compare_u32_lmul(res.fixu32[0], dst_even[i].fixu32[0]);

    test_vnsrl_vv_32_vm(src0[i].fixu64[0], src1[i].fixu32[0], res.fixu32[0], vmo.fixu32, pad.fixu8[0]);
    result_compare_u32_lmul(res.fixu32[0], dst_odd[i].fixu32[0]);

    return done_testing();
}
