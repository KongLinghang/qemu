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
int64_t src1 = 0x1122334455667788;


struct rvv_reg dst_vl[] = {
    {
        .fixs8 = {
            {0x2a, 0xe7, 0x36, 0xc9, 0x17, 0xc9, 0x33, 0xc6, 0xd3, 0xf4, 0xe3, 0x34, 0x01, 0x27, 0xef, 0xf0, },
            {0x2a, 0xe7, 0x36, 0xc9, 0x17, 0xc9, 0x33, 0xc6, 0xd3, 0xf4, 0xe3, 0x34, 0x01, 0x27, 0xef, 0x00, },
        },
        .fixs16 = {
            {0xecc7, 0x2643, 0x07e8, 0x06d4, 0xd4b5, 0x2411, 0x2152, 0xd3d3, },
            {0xecc7, 0x2643, 0x07e8, 0x06d4, 0xd4b5, 0x2411, 0x2152, 0x0000, },
        },
        .fixs32 = {
            {0xeff23efb, 0xd6189495, 0x07559411, 0xf23b0e40, },
            {0xeff23efb, 0xd6189495, 0x07559411, 0x00000000, },
        },
        .fixs64 = {
            {0x03d828881486ca20, 0xfc295fd22c4cc7f2, },
            {0x03d828881486ca20, 0x0000000000000000, },
        },
    },
};

struct rvv_reg dst_even[] = {
    {
        .fixs8 = {
            {0x2a, 0x11, 0x36, 0x11, 0x17, 0x11, 0x33, 0x11, 0xd3, 0x11, 0xe3, 0x11, 0x01, 0x11, 0xef, 0x11, },
            {0x2a, 0x11, 0x36, 0x11, 0x17, 0x11, 0x33, 0x11, 0xd3, 0x11, 0xe3, 0x11, 0x01, 0x11, 0xef, 0x11, },
        },
        .fixs16 = {
            {0xecc7, 0x1111, 0x07e8, 0x1111, 0xd4b5, 0x1111, 0x2152, 0x1111, },
            {0xecc7, 0x1111, 0x07e8, 0x1111, 0xd4b5, 0x1111, 0x2152, 0x1111, },
        },
        .fixs32 = {
            {0xeff23efb, 0x11111111, 0x07559411, 0x11111111, },
            {0xeff23efb, 0x11111111, 0x07559411, 0x11111111, },
        },
        .fixs64 = {
            {0x03d828881486ca20, 0x1111111111111111, },
            {0x03d828881486ca20, 0x1111111111111111, },
        },
    },
};

struct rvv_reg dst_odd[] = {
    {
        .fixs8 = {
            {0x11, 0xe7, 0x11, 0xc9, 0x11, 0xc9, 0x11, 0xc6, 0x11, 0xf4, 0x11, 0x34, 0x11, 0x27, 0x11, 0xf0, },
            {0x11, 0xe7, 0x11, 0xc9, 0x11, 0xc9, 0x11, 0xc6, 0x11, 0xf4, 0x11, 0x34, 0x11, 0x27, 0x11, 0xf0, },
        },
        .fixs16 = {
            {0x1111, 0x2643, 0x1111, 0x06d4, 0x1111, 0x2411, 0x1111, 0xd3d3, },
            {0x1111, 0x2643, 0x1111, 0x06d4, 0x1111, 0x2411, 0x1111, 0xd3d3, },
        },
        .fixs32 = {
            {0x11111111, 0xd6189495, 0x11111111, 0xf23b0e40, },
            {0x11111111, 0xd6189495, 0x11111111, 0xf23b0e40, },
        },
        .fixs64 = {
            {0x1111111111111111, 0xfc295fd22c4cc7f2, },
            {0x1111111111111111, 0xfc295fd22c4cc7f2, },
        },
    },
};

struct rvv_reg res;
int main(void)
{
    int i = 0;
    init_testsuite("Testing insn vmulh.vx\n");

    /* int8_t vmulh */
    test_vmulh_vx_8(vlmax_8 - 1, src0[i].fixs8[0], src1, res.fixs8[0], vma.fixs8, pad.fixs8[0]);
    result_compare_s8_lmul(res.fixs8[0], dst_vl[i].fixs8[0]);

    test_vmulh_vx_8_vm(src0[i].fixs8[0], src1, res.fixs8[0], vme.fixs8, pad.fixs8[0]);
    result_compare_s8_lmul(res.fixs8[0], dst_even[i].fixs8[0]);

    test_vmulh_vx_8_vm(src0[i].fixs8[0], src1, res.fixs8[0], vmo.fixs8, pad.fixs8[0]);
    result_compare_s8_lmul(res.fixs8[0], dst_odd[i].fixs8[0]);

    /* int16_t vmulh */
    test_vmulh_vx_16(vlmax_16 - 1, src0[i].fixs16[0], src1, res.fixs16[0], vma.fixs16, pad.fixs16[0]);
    result_compare_s16_lmul(res.fixs16[0], dst_vl[i].fixs16[0]);

    test_vmulh_vx_16_vm(src0[i].fixs16[0], src1, res.fixs16[0], vme.fixs16, pad.fixs16[0]);
    result_compare_s16_lmul(res.fixs16[0], dst_even[i].fixs16[0]);

    test_vmulh_vx_16_vm(src0[i].fixs16[0], src1, res.fixs16[0], vmo.fixs16, pad.fixs16[0]);
    result_compare_s16_lmul(res.fixs16[0], dst_odd[i].fixs16[0]);

    /* int32_t vmulh */
    test_vmulh_vx_32(vlmax_32 - 1, src0[i].fixs32[0], src1, res.fixs32[0], vma.fixs32, pad.fixs32[0]);
    result_compare_s32_lmul(res.fixs32[0], dst_vl[i].fixs32[0]);

    test_vmulh_vx_32_vm(src0[i].fixs32[0], src1, res.fixs32[0], vme.fixs32, pad.fixs32[0]);
    result_compare_s32_lmul(res.fixs32[0], dst_even[i].fixs32[0]);

    test_vmulh_vx_32_vm(src0[i].fixs32[0], src1, res.fixs32[0], vmo.fixs32, pad.fixs32[0]);
    result_compare_s32_lmul(res.fixs32[0], dst_odd[i].fixs32[0]);

    /* int64_t vmulh */
    test_vmulh_vx_64(vlmax_64 - 1, src0[i].fixs64[0], src1, res.fixs64[0], vma.fixs64, pad.fixs64[0]);
    result_compare_s64_lmul(res.fixs64[0], dst_vl[i].fixs64[0]);

    test_vmulh_vx_64_vm(src0[i].fixs64[0], src1, res.fixs64[0], vme.fixs64, pad.fixs64[0]);
    result_compare_s64_lmul(res.fixs64[0], dst_even[i].fixs64[0]);

    test_vmulh_vx_64_vm(src0[i].fixs64[0], src1, res.fixs64[0], vmo.fixs64, pad.fixs64[0]);
    result_compare_s64_lmul(res.fixs64[0], dst_odd[i].fixs64[0]);

    return done_testing();
}
