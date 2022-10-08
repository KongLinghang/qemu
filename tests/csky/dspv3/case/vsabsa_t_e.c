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
#include "dspv3_insn.h"

/* src reg 0 */
struct vdsp_reg src0[] = {
    {
        .fixs32 = {0xcfe06686, 0x8262f661, 0x15fc5221, 0xd6b9745a, },
        .fixs16 = {0xd6d6, 0x51f2, 0x10ef, 0x0ea1, 0xa349, 0x4d3f, 0x475d, 0xa164, },
        .fixs8 = {0xa5, 0x34, 0x8c, 0x74, 0xcd, 0x75, 0x92, 0x7a, 0x60, 0x19, 0x3c, 0x91, 0xfd, 0xab, 0x23, 0x21, },
        .fixu32 = {0xc5cf5eb9, 0x75bc7c30, 0xf0bec11d, 0x683e0475, },
        .fixu16 = {0xfe56, 0x4b63, 0xf166, 0x08bc, 0x6f16, 0x0ddb, 0xdeb9, 0xafbe, },
        .fixu8 = {0xc2, 0x29, 0x99, 0x3e, 0xe3, 0x82, 0x47, 0x89, 0xcd, 0xfb, 0xad, 0x9e, 0xe6, 0x27, 0x14, 0xc9, },
    },
};
/* src reg 1 */
struct vdsp_reg src1[] = {
    {
        .fixs32 = {0x7794d541, 0xf1bfac15, 0x67e3b37f, 0x12df3e7c, },
        .fixs16 = {0x4fb8, 0x39b3, 0x6744, 0xfa98, 0xce81, 0x997d, 0x301c, 0xcfb5, },
        .fixs8 = {0x21, 0xb6, 0x8d, 0x3a, 0xe2, 0x09, 0x90, 0x15, 0x2c, 0x13, 0xac, 0x86, 0x28, 0xce, 0x4f, 0xbb, },
        .fixu32 = {0xe391e1de, 0xb2c0dd9f, 0x888fed5e, 0x1c3b70fe, },
        .fixu16 = {0x6371, 0x3b45, 0x49ed, 0x7e26, 0x9ea1, 0xd612, 0x5c92, 0xfc48, },
        .fixu8 = {0x1c, 0x42, 0xd3, 0x53, 0x94, 0x57, 0x7b, 0xa3, 0xae, 0x96, 0x41, 0x28, 0x3a, 0x59, 0x9b, 0x70, },
    },
};
/* src reg 2 */
struct vdsp_reg src2[] = {
    {
        .fixs32 = {0x2ef3c1ca, 0xd167753f, 0xd345a93c, 0xcb8a4543, },
        .fixs16 = {0xf0f6, 0x8940, 0xf0cf, 0x70e1, 0x43dc, 0xd684, 0xd39d, 0x86d3, },
        .fixs8 = {0x5a, 0xeb, 0x19, 0x10, 0x5b, 0xcd, 0xa0, 0xda, 0x8f, 0x29, 0xb3, 0x35, 0x3d, 0xda, 0x0d, 0x99, },
        .fixu32 = {0xd6bc23ef, 0xd20235bb, 0xdb7e4b2f, 0x588d9bbf, },
        .fixu16 = {0x5d85, 0xab10, 0xc750, 0xab2a, 0xa9ae, 0xf97c, 0x415e, 0x882d, },
        .fixu8 = {0xd3, 0xd9, 0x4a, 0xd1, 0x8c, 0x5a, 0xef, 0x56, 0x6c, 0xc2, 0x44, 0xc2, 0x96, 0x9c, 0x23, 0x67, },
    },
};
/* src reg 3 */
struct vdsp_reg src3[] = {
    {
        .fixs32 = {0xb62db774, 0x0709f7b4, 0x6c9c7bcc, 0xa8c6d274, },
        .fixs16 = {0xbb9b, 0xb82a, 0x94a5, 0x70b4, 0x29b7, 0x8c06, 0x7c45, 0xaca1, },
        .fixs8 = {0xb5, 0x33, 0x70, 0x25, 0xd1, 0xaf, 0x8c, 0x2b, 0x97, 0xcd, 0x2d, 0x8a, 0xf5, 0x3a, 0x83, 0x10, },
        .fixu32 = {0x84619587, 0x16cdc3f9, 0x242a69b4, 0x35f2f02e, },
        .fixu16 = {0xbb43, 0x9b0c, 0xce4f, 0x4276, 0x2d64, 0x3b43, 0xb531, 0x33dc, },
        .fixu8 = {0xbd, 0xf2, 0x62, 0xa8, 0x68, 0x90, 0xe1, 0x5e, 0x42, 0xab, 0x6a, 0x13, 0xe7, 0xa5, 0xde, 0x38, },
    },
};
/* dst reg 0 */
struct vdsp_reg dst0[] = {
    {
        .fixs32 = {0xd6a83085, 0xd167753f, 0x42a25ef0, 0xcb8a4544, },
        .fixs16 = {0x69d8, 0x8941, 0x090e, 0x70e2, 0x9a31, 0xd684, 0xe7a6, 0x86d3, },
        .fixs8 = {0xd6, 0xeb, 0x97, 0x10, 0x5c, 0xcd, 0xda, 0xda, 0xa4, 0x29, 0x1f, 0x36, 0x3f, 0xda, 0x72, 0x99, },
        .fixu32 = {0xf47ea714, 0xd20235bb, 0x1882ac9e, 0x588d9bc0, },
        .fixu16 = {0xf86a, 0xab10, 0xd76e, 0xab2a, 0x5127, 0xf97d, 0xb6c8, 0x882d, },
        .fixu8 = {0x79, 0xda, 0x63, 0xd1, 0xc6, 0x5a, 0x04, 0x57, 0xbb, 0xc2, 0x6f, 0xc2, 0xca, 0x9c, 0x3d, 0x67, },
    },
};
/* dst reg 1 */
struct vdsp_reg dst1[] = {
    {
        .fixs32 = {0x081518d2, 0x0709f7b5, 0xa8c245ee, 0xa8c6d274, },
        .fixs16 = {0xe6d3, 0xb82a, 0x4867, 0x70b5, 0x40f8, 0x8c06, 0xaa96, 0xaca1, },
        .fixs8 = {0xe9, 0x33, 0x76, 0x25, 0x61, 0xb0, 0x97, 0x2b, 0xc2, 0xcd, 0x50, 0x8a, 0x21, 0x3b, 0xe9, 0x10, },
        .fixu32 = {0xec906946, 0x16cdc3f9, 0x702cfd2b, 0x35f2f02e, },
        .fixu16 = {0xeace, 0x9b0c, 0x9686, 0x4277, 0xaf8b, 0x3b43, 0x01bb, 0x33dd, },
        .fixu8 = {0xdc, 0xf2, 0xc7, 0xa8, 0xd4, 0x90, 0x57, 0x5f, 0xee, 0xab, 0x9c, 0x13, 0x6e, 0xa6, 0x37, 0x39, },
    },
};

int main(void)
{
    int i = 0;
    init_testsuite("Testing insn vsabsa.t.e\n");

    for (i = 0; i < sizeof(src0) / sizeof(struct vdsp_reg); i++) {
        test_vsabsa_s8_e(src0[i].fixs8, src1[i].fixs8, src2[i].fixs8, src3[i].fixs8);
        result_compare_s8(src2[i].fixs8, dst0[i].fixs8);
        result_compare_s8(src3[i].fixs8, dst1[i].fixs8);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct vdsp_reg); i++) {
        test_vsabsa_s16_e(src0[i].fixs16, src1[i].fixs16, src2[i].fixs16, src3[i].fixs16);
        result_compare_s16(src2[i].fixs16, dst0[i].fixs16);
        result_compare_s16(src3[i].fixs16, dst1[i].fixs16);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct vdsp_reg); i++) {
        test_vsabsa_s32_e(src0[i].fixs32, src1[i].fixs32, src2[i].fixs32, src3[i].fixs32);
        result_compare_s32(src2[i].fixs32, dst0[i].fixs32);
        result_compare_s32(src3[i].fixs32, dst1[i].fixs32);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct vdsp_reg); i++) {
        test_vsabsa_u8_e(src0[i].fixu8, src1[i].fixu8, src2[i].fixu8, src3[i].fixu8);
        result_compare_u8(src2[i].fixu8, dst0[i].fixu8);
        result_compare_u8(src3[i].fixu8, dst1[i].fixu8);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct vdsp_reg); i++) {
        test_vsabsa_u16_e(src0[i].fixu16, src1[i].fixu16, src2[i].fixu16, src3[i].fixu16);
        result_compare_u16(src2[i].fixu16, dst0[i].fixu16);
        result_compare_u16(src3[i].fixu16, dst1[i].fixu16);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct vdsp_reg); i++) {
        test_vsabsa_u32_e(src0[i].fixu32, src1[i].fixu32, src2[i].fixu32, src3[i].fixu32);
        result_compare_u32(src2[i].fixu32, dst0[i].fixu32);
        result_compare_u32(src3[i].fixu32, dst1[i].fixu32);
    }

    return done_testing();
}