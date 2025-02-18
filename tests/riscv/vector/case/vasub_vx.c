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

int8_t   src1_s8 = 0x83;
int16_t src1_s16 = 0x507d;
int32_t src1_s32 = 0x7fffff7d;
int64_t src1_s64 = 0x80000ee29e8350c1;

struct rvv_reg dst_rnu[] = {
    {
        .fixs64 = {
            {0x5cb8535b4e1750a9, 0x235310e854b1f35d,},
            {0x5cb8535b4e1750a9, 0x0000000000000000,},
        },
        .fixs32 = {
            {0xa7f03385, 0x81317b72, 0xcafe2952, 0xab5cba6f,},
            {0xa7f03385, 0x81317b72, 0xcafe2952, 0x00000000,},
        },
        .fixs16 = {
            {0xc32d, 0x00bb, 0xe039, 0xdf12, 0xa966, 0xfe61, 0xfb70, 0xa874,},
            {0xc32d, 0x00bb, 0xe039, 0xdf12, 0xa966, 0xfe61, 0xfb70, 0x0000,},
        },
        .fixs8 = {
            {0x11, 0x59, 0x05, 0x79, 0x25, 0x79, 0x08, 0x7c, 0x6f, 0x4b, 0x5d, 0x07, 0x3d, 0x14, 0x50, 0x4f,},
            {0x11, 0x59, 0x05, 0x79, 0x25, 0x79, 0x08, 0x7c, 0x6f, 0x4b, 0x5d, 0x07, 0x3d, 0x14, 0x50, 0x00,},
        },
    },
};

/* vmo */
struct rvv_reg dst_rne[] = {
    {
        .fixs64 = {
            {0x1111111111111111, 0x235310e854b1f35d, },
            {0x1111111111111111, 0x235310e854b1f35d, },
        },
        .fixs32 = {
            {0x11111111, 0x81317b72, 0x11111111, 0xab5cba6e,},
            {0x11111111, 0x81317b72, 0x11111111, 0xab5cba6e,},
        },
        .fixs16 = {
            {0x1111, 0x00ba, 0x1111, 0xdf12, 0x1111, 0xfe61, 0x1111, 0xa874,},
            {0x1111, 0x00ba, 0x1111, 0xdf12, 0x1111, 0xfe61, 0x1111, 0xa874,},
        },
        .fixs8 = {
            {0x11, 0x58, 0x11, 0x78, 0x11, 0x79, 0x11, 0x7c, 0x11, 0x4b, 0x11, 0x07, 0x11, 0x14, 0x11, 0x4f,},
            {0x11, 0x58, 0x11, 0x78, 0x11, 0x79, 0x11, 0x7c, 0x11, 0x4b, 0x11, 0x07, 0x11, 0x14, 0x11, 0x4f,},
        },
    },
};

/* vme */
struct rvv_reg dst_rdn[] = {
    {
        .fixs64 = {
            {0x5cb8535b4e1750a8, 0x1111111111111111,},
            {0x5cb8535b4e1750a8, 0x1111111111111111,},
        },
        .fixs32 = {
            {0xa7f03384, 0x11111111, 0xcafe2952, 0x11111111,},
            {0xa7f03384, 0x11111111, 0xcafe2952, 0x11111111,},
        },
        .fixs16 = {
            {0xc32c, 0x1111, 0xe039, 0x1111, 0xa966, 0x1111, 0xfb70, 0x1111,},
            {0xc32c, 0x1111, 0xe039, 0x1111, 0xa966, 0x1111, 0xfb70, 0x1111,},
        },
        .fixs8 = {
            {0x11, 0x11, 0x04, 0x11, 0x25, 0x11, 0x07, 0x11, 0x6e, 0x11, 0x5c, 0x11, 0x3d, 0x11, 0x50, 0x11,},
            {0x11, 0x11, 0x04, 0x11, 0x25, 0x11, 0x07, 0x11, 0x6e, 0x11, 0x5c, 0x11, 0x3d, 0x11, 0x50, 0x11,},
        },
    },
};

struct rvv_reg dst_rod[] = {
    {
        .fixs64 = {
            {0x5cb8535b4e1750a9, 0x235310e854b1f35d, },
            {0x5cb8535b4e1750a9, 0x235310e854b1f35d, },
        },
        .fixs32 = {
            {0xa7f03385, 0x81317b72, 0xcafe2952, 0xab5cba6f, },
            {0xa7f03385, 0x81317b72, 0xcafe2952, 0xab5cba6f, },
        },
        .fixs16 = {
            {0xc32d, 0x00bb, 0xe039, 0xdf12, 0xa966, 0xfe61, 0xfb70, 0xa873, },
            {0xc32d, 0x00bb, 0xe039, 0xdf12, 0xa966, 0xfe61, 0xfb70, 0xa873, },
        },
        .fixs8 = {
            {0x11, 0x59, 0x05, 0x79, 0x25, 0x79, 0x07, 0x7b, 0x6f, 0x4b, 0x5d, 0x07, 0x3d, 0x14, 0x50, 0x4f, },
            {0x11, 0x59, 0x05, 0x79, 0x25, 0x79, 0x07, 0x7b, 0x6f, 0x4b, 0x5d, 0x07, 0x3d, 0x14, 0x50, 0x4f, },
        },
    },
};

struct rvv_reg res;

int main(void)
{
    int i = 0;
    init_testsuite("Testing insn vasub.vx\n");

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vasub_vx_8_rnu(vlmax_8 - 1, src0[i].fixs8, src1_s8,
                res.fixs8, pad.fixs8);
        result_compare_s8_lmul(res.fixs8[0], dst_rnu[i].fixs8[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vasub_vx_8_rne(src0[i].fixs8, src1_s8, res.fixs8,
                vmo.fixs8, pad.fixs8);
        result_compare_s8_lmul(res.fixs8[0], dst_rne[i].fixs8[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vasub_vx_8_rdn(src0[i].fixs8, src1_s8, res.fixs8,
                vme.fixs8, pad.fixs8);
        result_compare_s8_lmul(res.fixs8[0], dst_rdn[i].fixs8[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vasub_vx_8_rod(src0[i].fixs8, src1_s8, res.fixs8, pad.fixs8);
        result_compare_s8_lmul(res.fixs8[0], dst_rod[i].fixs8[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vasub_vx_16_rnu(vlmax_16 - 1, src0[i].fixs16, src1_s16,
                res.fixs16, pad.fixs16);
        result_compare_s16_lmul(res.fixs16[0], dst_rnu[i].fixs16[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vasub_vx_16_rne(src0[i].fixs16, src1_s16, res.fixs16,
                vmo.fixs16, pad.fixs16);
        result_compare_s16_lmul(res.fixs16[0], dst_rne[i].fixs16[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vasub_vx_16_rdn(src0[i].fixs16, src1_s16,
                res.fixs16, vme.fixs16, pad.fixs16);
        result_compare_s16_lmul(res.fixs16[0], dst_rdn[i].fixs16[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vasub_vx_16_rod(src0[i].fixs16, src1_s16, res.fixs16,
                pad.fixs16);
        result_compare_s16_lmul(res.fixs16[0], dst_rod[i].fixs16[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vasub_vx_32_rnu(vlmax_32 - 1, src0[i].fixs32, src1_s32,
                res.fixs32, pad.fixs32);
        result_compare_s32_lmul(res.fixs32[0], dst_rnu[i].fixs32[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vasub_vx_32_rne(src0[i].fixs32, src1_s32, res.fixs32,
                vmo.fixs32, pad.fixs32);
        result_compare_s32_lmul(res.fixs32[0], dst_rne[i].fixs32[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vasub_vx_32_rdn(src0[i].fixs32, src1_s32,
                res.fixs32, vme.fixs32, pad.fixs32);
        result_compare_s32_lmul(res.fixs32[0], dst_rdn[i].fixs32[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vasub_vx_32_rod(src0[i].fixs32, src1_s32, res.fixs32,
                pad.fixs32);
        result_compare_s32_lmul(res.fixs32[0], dst_rod[i].fixs32[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vasub_vx_64_rnu(vlmax_64 - 1, src0[i].fixs64, src1_s64,
                res.fixs64, pad.fixs64);
        result_compare_s64_lmul(res.fixs64[0], dst_rnu[i].fixs64[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vasub_vx_64_rne(src0[i].fixs64, src1_s64,
                res.fixs64, vmo.fixs64, pad.fixs64);
        result_compare_s64_lmul(res.fixs64[0], dst_rne[i].fixs64[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vasub_vx_64_rdn(src0[i].fixs64, src1_s64,
                res.fixs64, vme.fixs64, pad.fixs64);
        result_compare_s64_lmul(res.fixs64[0], dst_rdn[i].fixs64[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vasub_vx_64_rod(src0[i].fixs64, src1_s64, res.fixs64,
                pad.fixs64);
        result_compare_s64_lmul(res.fixs64[0], dst_rod[i].fixs64[0]);
    }

    return done_testing();
}

