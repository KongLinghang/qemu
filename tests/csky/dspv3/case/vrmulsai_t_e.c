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

struct vdsp_reg src[] = {
    {
        .fixs32 = {0xcfe06686, 0x8262f661, 0x15fc5221, 0xd6b9745a, },
        .fixs16 = {0xd6d6, 0x51f2, 0x10ef, 0x0ea1, 0xa349, 0x4d3f, 0x475d, 0xa164, },
        .fixs8 = {0xa5, 0x34, 0x8c, 0x74, 0xcd, 0x75, 0x92, 0x7a, 0x60, 0x19, 0x3c, 0x91, 0xfd, 0xab, 0x23, 0x21, },
    },
    {
        .fixs32 = {0x7794d541, 0xf1bfac15, 0x67e3b37f, 0x12df3e7c, },
        .fixs16 = {0x4fb8, 0x39b3, 0x6744, 0xfa98, 0xce81, 0x997d, 0x301c, 0xcfb5, },
        .fixs8 = {0x21, 0xb6, 0x8d, 0x3a, 0xe2, 0x09, 0x90, 0x15, 0x2c, 0x13, 0xac, 0x86, 0x28, 0xce, 0x4f, 0xbb, },
    },
    {
        .fixs64 = {0x2ef3c1cad167753f, 0xd345a93ccb8a4543, },
        .fixs32 = {0xf0f68940, 0xf0cf70e1, 0x43dcd684, 0xd39d86d3, },
        .fixs16 = {0x5aeb, 0x1910, 0x5bcd, 0xa0da, 0x8f29, 0xb335, 0x3dda, 0x0d99, },
    },
    {
        .fixs64 = {0x2ef3c1cad167753f, 0xd345a93ccb8a4543, },
        .fixs32 = {0xf0f68940, 0xf0cf70e1, 0x43dcd684, 0xd39d86d3, },
        .fixs16 = {0x5aeb, 0x1910, 0x5bcd, 0xa0da, 0x8f29, 0xb335, 0x3dda, 0x0d99, },
    },
};

struct vdsp_reg dst[] = {
    {
        .fixs64 = {0x23b66c7157c73842, 0xb5ef25c9c823e713, },
        .fixs32 = {0xea8dc328, 0xfd91bad9, 0x467fcce8, 0xd5e4a02f, },
        .fixs16 = {0x550d, 0x1c6a, 0x5453, 0xa854, 0x8bdf, 0xbabf, 0x36c3, 0x1576, },
    },
    {
        .fixs64 = {0x34164af97d249cef, 0xc9a1c4324200fbb0, },
        .fixs32 = {0xe286fafc, 0xfcd66c05, 0x4ef95570, 0xc4e274c3, },
        .fixs16 = {0x611b, 0x1aac, 0x5fab, 0x99b2, 0x8ef7, 0xadba, 0x401b, 0x0fb9, },
    },
};


struct vdsp_reg res[2];

int main(void)
{
    int i = 0;
    init_testsuite("Testing insn vrmulsai.t.e\n");

    test_vrmulsai_s8_e(src[0].fixs8, res[0].fixs16);
    result_compare_s16(res[0].fixs16, dst[0].fixs16);
    result_compare_s16(res[1].fixs16, dst[1].fixs16);

    test_vrmulsai_s16_e(src[0].fixs16, res[0].fixs32);
    result_compare_s32(res[0].fixs32, dst[0].fixs32);
    result_compare_s32(res[1].fixs32, dst[1].fixs32);

    test_vrmulsai_s32_e(src[0].fixs32, res[0].fixs64);
    result_compare_s64(res[0].fixs64, dst[0].fixs64);
    result_compare_s64(res[1].fixs64, dst[1].fixs64);

    return done_testing();
}
