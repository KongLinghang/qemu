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
        .fixs64 = {
            {0x3970b5993ab1f212, 0xc6a630b347e7377b, },
            {0x3970b5993ab1f212, 0xc6a630b347e7377b, },
        },
        .fixs32 = {
            {0xcfe06686, 0x8262f661, 0x15fc5221, 0xd6b9745a, },
            {0xcfe06686, 0x8262f661, 0x15fc5221, 0xd6b9745a, },
        },
        .fixs16 = {
            {0xd6d6, 0x51f2, 0x10ef, 0x0ea1, 0xa349, 0x4d3f, 0x475d, 0xa164, },
            {0xd6d6, 0x51f2, 0x10ef, 0x0ea1, 0xa349, 0x4d3f, 0x475d, 0xa164, },
        },
        .fixs8 = {
            {0xa5, 0x34, 0x8c, 0x74, 0xcd, 0x75, 0x92, 0x7a, 0x60, 0x19, 0x3c, 0x91, 0xfd, 0xab, 0x23, 0x21, },
            {0xa5, 0x34, 0x8c, 0x74, 0xcd, 0x75, 0x92, 0x7a, 0x60, 0x19, 0x3c, 0x91, 0xfd, 0xab, 0x23, 0x21, },
        },
    },
};

struct rvv_reg src1[] = {
    {
        .fixs64 = {
            {0x07d215928aa0d7b6, 0x07186161e5f9e80f, },
            {0x07d215928aa0d7b6, 0x07186161e5f9e80f, },
        },
        .fixs32 = {
            {0x7794d541, 0xf1bfac15, 0x67e3b37f, 0x12df3e7c, },
            {0x7794d541, 0xf1bfac15, 0x67e3b37f, 0x12df3e7c, },
        },
        .fixs16 = {
            {0x4fb8, 0x39b3, 0x6744, 0xfa98, 0xce81, 0x997d, 0x301c, 0xcfb5, },
            {0x4fb8, 0x39b3, 0x6744, 0xfa98, 0xce81, 0x997d, 0x301c, 0xcfb5, },
        },
        .fixs8 = {
            {0x21, 0xb6, 0x8d, 0x3a, 0xe2, 0x09, 0x90, 0x15, 0x2c, 0x13, 0xac, 0x86, 0x28, 0xce, 0x4f, 0xbb, },
            {0x21, 0xb6, 0x8d, 0x3a, 0xe2, 0x09, 0x90, 0x15, 0x2c, 0x13, 0xac, 0x86, 0x28, 0xce, 0x4f, 0xbb, },
        },
    },
};
struct rvv_reg dst_vl[] = {
    {
        .fixs8 = {
            {0x56, 0x09, 0x2d, 0x59, 0x0b, 0x2e, 0x31, 0x13, 0x91, 0xec, 0x61, 0xf7, 0x99, 0xab, 0xde, 0x2c, },
            {0x56, 0x09, 0x2d, 0x59, 0x0b, 0x2e, 0x31, 0x13, 0x91, 0xec, 0x61, 0xf7, 0x99, 0xab, 0xde, 0x00, },
        },
        .fixs16 = {
            {0x84e1, 0x3f47, 0xb98d, 0xfaa9, 0x16da, 0x6fd4, 0x4f3d, 0x08c5, },
            {0x84e1, 0x3f47, 0xb98d, 0xfaa9, 0x16da, 0x6fd4, 0x4f3d, 0x0000, },
        },
        .fixs32 = {
            {0x1dd09717, 0x64177306, 0x80ede270, 0xab7938a9, },
            {0x1dd09717, 0x64177306, 0x80ede270, 0x00000000, },
        },
        .fixs64 = {
            {0xcc3a00453d2047dd, 0x79ccc9dccf87c946, },
            {0xcc3a00453d2047dd, 0x0000000000000000, },
        },
    },
};

struct rvv_reg dst_even[] = {
    {
        .fixs8 = {
            {0x56, 0x11, 0x2d, 0x11, 0x0b, 0x11, 0x31, 0x11, 0x91, 0x11, 0x61, 0x11, 0x99, 0x11, 0xde, 0x11, },
            {0x56, 0x11, 0x2d, 0x11, 0x0b, 0x11, 0x31, 0x11, 0x91, 0x11, 0x61, 0x11, 0x99, 0x11, 0xde, 0x11, },
        },
        .fixs16 = {
            {0x84e1, 0x1111, 0xb98d, 0x1111, 0x16da, 0x1111, 0x4f3d, 0x1111, },
            {0x84e1, 0x1111, 0xb98d, 0x1111, 0x16da, 0x1111, 0x4f3d, 0x1111, },
        },
        .fixs32 = {
            {0x1dd09717, 0x11111111, 0x80ede270, 0x11111111, },
            {0x1dd09717, 0x11111111, 0x80ede270, 0x11111111, },
        },
        .fixs64 = {
            {0xcc3a00453d2047dd, 0x1111111111111111, },
            {0xcc3a00453d2047dd, 0x1111111111111111, },
        },
    },
};

struct rvv_reg dst_odd[] = {
    {
        .fixs8 = {
            {0x11, 0x09, 0x11, 0x59, 0x11, 0x2e, 0x11, 0x13, 0x11, 0xec, 0x11, 0xf7, 0x11, 0xab, 0x11, 0x2c, },
            {0x11, 0x09, 0x11, 0x59, 0x11, 0x2e, 0x11, 0x13, 0x11, 0xec, 0x11, 0xf7, 0x11, 0xab, 0x11, 0x2c, },
        },
        .fixs16 = {
            {0x1111, 0x3f47, 0x1111, 0xfaa9, 0x1111, 0x6fd4, 0x1111, 0x08c5, },
            {0x1111, 0x3f47, 0x1111, 0xfaa9, 0x1111, 0x6fd4, 0x1111, 0x08c5, },
        },
        .fixs32 = {
            {0x11111111, 0x64177306, 0x11111111, 0xab7938a9, },
            {0x11111111, 0x64177306, 0x11111111, 0xab7938a9, },
        },
        .fixs64 = {
            {0x1111111111111111, 0x79ccc9dccf87c946, },
            {0x1111111111111111, 0x79ccc9dccf87c946, },
        },
    },
};

struct rvv_reg res;

int main(void)
{
    int i = 0;
    init_testsuite("Testing insn vmacc.vv\n");

    /* int8_t vmacc */
    test_vmacc_vv_8(vlmax_8 - 1, src0[i].fixs8[0], src1[i].fixs8[0], res.fixs8[0], vma.fixs8, pad.fixs8[0]);
    result_compare_s8_lmul(res.fixs8[0], dst_vl[i].fixs8[0]);

    test_vmacc_vv_8_vm(src0[i].fixs8[0], src1[i].fixs8[0], res.fixs8[0], vme.fixs8, pad.fixs8[0]);
    result_compare_s8_lmul(res.fixs8[0], dst_even[i].fixs8[0]);

    test_vmacc_vv_8_vm(src0[i].fixs8[0], src1[i].fixs8[0], res.fixs8[0], vmo.fixs8, pad.fixs8[0]);
    result_compare_s8_lmul(res.fixs8[0], dst_odd[i].fixs8[0]);

    /* int16_t vmacc */
    test_vmacc_vv_16(vlmax_16 - 1, src0[i].fixs16[0], src1[i].fixs16[0], res.fixs16[0], vma.fixs16, pad.fixs16[0]);
    result_compare_s16_lmul(res.fixs16[0], dst_vl[i].fixs16[0]);

    test_vmacc_vv_16_vm(src0[i].fixs16[0], src1[i].fixs16[0], res.fixs16[0], vme.fixs16, pad.fixs16[0]);
    result_compare_s16_lmul(res.fixs16[0], dst_even[i].fixs16[0]);

    test_vmacc_vv_16_vm(src0[i].fixs16[0], src1[i].fixs16[0], res.fixs16[0], vmo.fixs16, pad.fixs16[0]);
    result_compare_s16_lmul(res.fixs16[0], dst_odd[i].fixs16[0]);

    /* int32_t vmacc */
    test_vmacc_vv_32(vlmax_32 - 1, src0[i].fixs32[0], src1[i].fixs32[0], res.fixs32[0], vma.fixs32, pad.fixs32[0]);
    result_compare_s32_lmul(res.fixs32[0], dst_vl[i].fixs32[0]);

    test_vmacc_vv_32_vm(src0[i].fixs32[0], src1[i].fixs32[0], res.fixs32[0], vme.fixs32, pad.fixs32[0]);
    result_compare_s32_lmul(res.fixs32[0], dst_even[i].fixs32[0]);

    test_vmacc_vv_32_vm(src0[i].fixs32[0], src1[i].fixs32[0], res.fixs32[0], vmo.fixs32, pad.fixs32[0]);
    result_compare_s32_lmul(res.fixs32[0], dst_odd[i].fixs32[0]);

    /* int64_t vmacc */
    test_vmacc_vv_64(vlmax_64 - 1, src0[i].fixs64[0], src1[i].fixs64[0], res.fixs64[0], vma.fixs64, pad.fixs64[0]);
    result_compare_s64_lmul(res.fixs64[0], dst_vl[i].fixs64[0]);

    test_vmacc_vv_64_vm(src0[i].fixs64[0], src1[i].fixs64[0], res.fixs64[0], vme.fixs64, pad.fixs64[0]);
    result_compare_s64_lmul(res.fixs64[0], dst_even[i].fixs64[0]);

    test_vmacc_vv_64_vm(src0[i].fixs64[0], src1[i].fixs64[0], res.fixs64[0], vmo.fixs64, pad.fixs64[0]);
    result_compare_s64_lmul(res.fixs64[0], dst_odd[i].fixs64[0]);

    return done_testing();
}
