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
            {0x7ffffffffffffffa, 0x8000000000000001, },
            {0x7ffffffffffffffa, 0x8000000000000001, },
        },
        .fixs32 = {
            {0xcfe06686, 0x80000001, 0x15fc5221, 0x7ffffffa, },
            {0xcfe06686, 0x80000001, 0x15fc5221, 0x7ffffffa, },
        },
        .fixs16 = {
            {0x8001, 0x51f2, 0x7ff1, 0x0ea1, 0xa349, 0x4d3f, 0x475d, 0xa164, },
            {0x8001, 0x51f2, 0x7ff1, 0x0ea1, 0xa349, 0x4d3f, 0x475d, 0xa164, },
        },
        .fixs8 = {
            {0xa5, 0x34, 0x8c, 0x74, 0xcd, 0x75, 0x92, 0x7a, 0x60, 0x19, 0x3c, 0x91, 0xfd, 0xab, 0x23, 0x21, },
            {0xa5, 0x34, 0x8c, 0x74, 0xcd, 0x75, 0x92, 0x7a, 0x60, 0x19, 0x3c, 0x91, 0xfd, 0xab, 0x23, 0x21, },
        },
        .fixu64 = {
            {0xfffffffffffffffa, 0x1c626bcd2715a031, },
            {0xfffffffffffffffa, 0x1c626bcd2715a031, },
        },
        .fixu32 = {
            {0xc5cf5eb9, 0xfffffff3, 0xf0bec11d, 0x683e0475, },
            {0xc5cf5eb9, 0xfffffff3, 0xf0bec11d, 0x683e0475, },
        },
        .fixu16 = {
            {0xfe56, 0x4b63, 0xfff6, 0x08bc, 0x6f16, 0x0ddb, 0xdeb9, 0xafbe, },
            {0xfe56, 0x4b63, 0xfff6, 0x08bc, 0x6f16, 0x0ddb, 0xdeb9, 0xafbe, },
        },
        .fixu8 = {
            {0xc2, 0x29, 0x99, 0x3e, 0xe3, 0x82, 0x47, 0x89, 0xcd, 0xfb, 0xad, 0x9e, 0xe6, 0x27, 0x14, 0xc9, },
            {0xc2, 0x29, 0x99, 0x3e, 0xe3, 0x82, 0x47, 0x89, 0xcd, 0xfb, 0xad, 0x9e, 0xe6, 0x27, 0x14, 0xc9, },
        },
    },
};

struct rvv_reg dst_even[] = {
    {
        .fixs64 = {
            {0x7fffffffffffffff, 0x1111111111111111},
            {0x7fffffffffffffff, 0x1111111111111111},
        },
        .fixs32 = {
            {0xcfe06694, 0x11111111, 0x15fc522f, 0x11111111,},
            {0xcfe06694, 0x11111111, 0x15fc522f, 0x11111111,},
        },
        .fixs16 = {
            {0x8000, 0x1111, 0x7fe1, 0x1111, 0xa339, 0x1111, 0x474d, 0x1111,},
            {0x8000, 0x1111, 0x7fe1, 0x1111, 0xa339, 0x1111, 0x474d, 0x1111,},
        },
        .fixs8 = {
            {0x95, 0x11, 0x80, 0x11, 0xbd, 0x11, 0x82, 0x11, 0x50, 0x11, 0x2c, 0x11, 0xed, 0x11, 0x13, 0x11,},
            {0x95, 0x11, 0x80, 0x11, 0xbd, 0x11, 0x82, 0x11, 0x50, 0x11, 0x2c, 0x11, 0xed, 0x11, 0x13, 0x11,},
        },
        .fixu64 = {
            {0xffffffffffffffff, 0x1111111111111111, },
            {0xffffffffffffffff, 0x1111111111111111, },
        },
        .fixu32 = {
            {0xc5cf5ec8, 0x11111111, 0xf0bec12c, 0x11111111,},
            {0xc5cf5ec8, 0x11111111, 0xf0bec12c, 0x11111111,},
        },
        .fixu16 = {
            {0xfe65, 0x1111, 0xffff, 0x1111, 0x6f25, 0x1111, 0xdec8, 0x1111,},
            {0xfe65, 0x1111, 0xffff, 0x1111, 0x6f25, 0x1111, 0xdec8, 0x1111,},
        },
        .fixu8 = {
            {0xd1, 0x11, 0xa8, 0x11, 0xf2, 0x11, 0x56, 0x11, 0xdc, 0x11, 0xbc, 0x11, 0xf5, 0x11, 0x23, 0x11,},
            {0xd1, 0x11, 0xa8, 0x11, 0xf2, 0x11, 0x56, 0x11, 0xdc, 0x11, 0xbc, 0x11, 0xf5, 0x11, 0x23, 0x11,},
        },
    },
};

struct rvv_reg dst_odd[] = {
    {
        .fixs64 = {
            {0x1111111111111111, 0x800000000000000f},
            {0x1111111111111111, 0x800000000000000f},
        },
        .fixs32 = {
            {0x11111111, 0x8000000f, 0x11111111, 0x7fffffff,},
            {0x11111111, 0x8000000f, 0x11111111, 0x7fffffff,},
        },
        .fixs16 = {
            {0x1111, 0x51e2, 0x1111, 0x0e91, 0x1111, 0x4d2f, 0x1111, 0xa154,},
            {0x1111, 0x51e2, 0x1111, 0x0e91, 0x1111, 0x4d2f, 0x1111, 0xa154,},
        },
        .fixs8 = {
            {0x11, 0x24, 0x11, 0x64, 0x11, 0x65, 0x11, 0x6a, 0x11, 0x09, 0x11, 0x81, 0x11, 0x9b, 0x11, 0x11,},
            {0x11, 0x24, 0x11, 0x64, 0x11, 0x65, 0x11, 0x6a, 0x11, 0x09, 0x11, 0x81, 0x11, 0x9b, 0x11, 0x11,},
        },
        .fixu64 = {
            {0x1111111111111111, 0x1c626bcd2715a040, },
            {0x1111111111111111, 0x1c626bcd2715a040, },
        },
        .fixu32 = {
            {0x11111111, 0xffffffff, 0x11111111, 0x683e0484,},
            {0x11111111, 0xffffffff, 0x11111111, 0x683e0484,},
        },
        .fixu16 = {
            {0x1111, 0x4b72, 0x1111, 0x08cb, 0x1111, 0x0dea, 0x1111, 0xafcd,},
            {0x1111, 0x4b72, 0x1111, 0x08cb, 0x1111, 0x0dea, 0x1111, 0xafcd,},
        },
        .fixu8 = {
            {0x11, 0x38, 0x11, 0x4d, 0x11, 0x91, 0x11, 0x98, 0x11, 0xff, 0x11, 0xad, 0x11, 0x36, 0x11, 0xd8,},
            {0x11, 0x38, 0x11, 0x4d, 0x11, 0x91, 0x11, 0x98, 0x11, 0xff, 0x11, 0xad, 0x11, 0x36, 0x11, 0xd8,},
        },
    },
};

struct rvv_reg dst_vl[] = {
    {
        .fixs64 = {
            {0x7fffffffffffffff, 0x800000000000000f},
            {0x7fffffffffffffff, 0x0000000000000000},
        },
        .fixs32 = {
            {0xcfe06676, 0x80000000, 0x15fc5211, 0x7fffffea,},
            {0xcfe06676, 0x80000000, 0x15fc5211, 0x00000000,},
        },
        .fixs16 = {
            {0x8000, 0x51e2, 0x7fe1, 0x0e91, 0xa339, 0x4d2f, 0x474d, 0xa154,},
            {0x8000, 0x51e2, 0x7fe1, 0x0e91, 0xa339, 0x4d2f, 0x474d, 0x0000,},
        },
        .fixs8 = {
            {0x95, 0x24, 0x80, 0x64, 0xbd, 0x65, 0x82, 0x6a, 0x50, 0x09, 0x2c, 0x81, 0xed, 0x9b, 0x13, 0x11,},
            {0x95, 0x24, 0x80, 0x64, 0xbd, 0x65, 0x82, 0x6a, 0x50, 0x09, 0x2c, 0x81, 0xed, 0x9b, 0x13, 0x00,},
        },
        .fixu64 = {
            {0xffffffffffffffff, 0x1c626bcd2715a040, },
            {0xffffffffffffffff, 0x0000000000000000, },
        },
        .fixu32 = {
            {0xc5cf5ec8, 0xffffffff, 0xf0bec12c, 0x683e0484,},
            {0xc5cf5ec8, 0xffffffff, 0xf0bec12c, 0x00000000,},
        },
        .fixu16 = {
            {0xfe65, 0x4b72, 0xffff, 0x08cb, 0x6f25, 0x0dea, 0xdec8, 0xafcd,},
            {0xfe65, 0x4b72, 0xffff, 0x08cb, 0x6f25, 0x0dea, 0xdec8, 0x0000,},
        },
        .fixu8 = {
            {0xd1, 0x38, 0xa8, 0x4d, 0xf2, 0x91, 0x56, 0x98, 0xdc, 0xff, 0xbc, 0xad, 0xf5, 0x36, 0x23, 0xd8,},
            {0xd1, 0x38, 0xa8, 0x4d, 0xf2, 0x91, 0x56, 0x98, 0xdc, 0xff, 0xbc, 0xad, 0xf5, 0x36, 0x23, 0x00,},
        },
    },
    {
        .fixs64 = {
            {0x7fffffffffffffea, 0x8000000000000000},
            {0x7fffffffffffffea, 0x0000000000000000},
        },
        .fixs32 = {
            {0xcfe06694, 0x8000000f, 0x15fc522f, 0x7fffffff,},
            {0xcfe06694, 0x8000000f, 0x15fc522f, 0x00000000,},
        },
        .fixs16 = {
            {0x800f, 0x5200, 0x7fff, 0x0eaf, 0xa357, 0x4d4d, 0x476b, 0xa172,},
            {0x800f, 0x5200, 0x7fff, 0x0eaf, 0xa357, 0x4d4d, 0x476b, 0x0000,},
        },
        .fixs8 = {
            {0xb3, 0x42, 0x9a, 0x7f, 0xdb, 0x7f, 0xa0, 0x7f, 0x6e, 0x27, 0x4a, 0x9f, 0x0b, 0xb9, 0x31, 0x2f,},
            {0xb3, 0x42, 0x9a, 0x7f, 0xdb, 0x7f, 0xa0, 0x7f, 0x6e, 0x27, 0x4a, 0x9f, 0x0b, 0xb9, 0x31, 0x00,},
        },
    },

};

struct rvv_reg res;

int main(void)
{
    int i = 0;
    init_testsuite("Testing insn vsaddu.vi\n");

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vsaddu_vi_8(vlmax_8 - 1, src0[i].fixu8,
                res.fixu8, pad.fixs8);
        result_compare_u8_lmul(res.fixu8[0], dst_vl[i].fixu8[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vsaddu_vi_8_vm(src0[i].fixu8, res.fixu8, vmo.fixs8, pad.fixu8);
        result_compare_u8_lmul(res.fixu8[0], dst_odd[i].fixu8[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vsaddu_vi_8_vm(src0[i].fixu8, res.fixu8, vme.fixs8, pad.fixu8);
        result_compare_u8_lmul(res.fixu8[0], dst_even[i].fixu8[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vsaddu_vi_16(vlmax_16 - 1, src0[i].fixu16,
                res.fixu16, pad.fixs16);
        result_compare_u16_lmul(res.fixu16[0], dst_vl[i].fixu16[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vsaddu_vi_16_vm(src0[i].fixu16, res.fixu16, vmo.fixs16,
                pad.fixu16);
        result_compare_u16_lmul(res.fixu16[0], dst_odd[i].fixu16[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vsaddu_vi_16_vm(src0[i].fixu16, res.fixu16, vme.fixs16,
                pad.fixu16);
        result_compare_u16_lmul(res.fixu16[0], dst_even[i].fixu16[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vsaddu_vi_32(vlmax_32 - 1, src0[i].fixu32,
                res.fixu32, pad.fixs32);
        result_compare_u32_lmul(res.fixu32[0], dst_vl[i].fixu32[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vsaddu_vi_32_vm(src0[i].fixu32, res.fixu32, vmo.fixs32,
                pad.fixu32);
        result_compare_u32_lmul(res.fixu32[0], dst_odd[i].fixu32[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vsaddu_vi_32_vm(src0[i].fixu32, res.fixu32, vme.fixs32,
                pad.fixu32);
        result_compare_u32_lmul(res.fixu32[0], dst_even[i].fixu32[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vsaddu_vi_64(vlmax_64 - 1, src0[i].fixu64,
                res.fixu64, pad.fixs64);
        result_compare_u64_lmul(res.fixu64[0], dst_vl[i].fixu64[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vsaddu_vi_64_vm(src0[i].fixu64, res.fixu64, vmo.fixs64,
                pad.fixu64);
        result_compare_u64_lmul(res.fixu64[0], dst_odd[i].fixu64[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vsaddu_vi_64_vm(src0[i].fixu64, res.fixu64, vme.fixs64,
                pad.fixu64);
        result_compare_u64_lmul(res.fixu64[0], dst_even[i].fixu64[0]);
    }

    return done_testing();
}
