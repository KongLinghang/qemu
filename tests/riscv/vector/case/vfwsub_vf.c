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
        .float64 = {
            {0x7fefffffffffffff, 0xffefffffffffffff,},
            {0x40154afd6a012e31, 0xc0417456836cfe7b,},
        },
        .float32 = {
            {0x483471f7, 0x46f2e02b, 0xc785dc35, 0x47ad69d9, },
            {0x483471f7, 0x46f2e02b, 0xff7fffff, 0x47ad69d9, },
        },
        .float16 = {
            {0x4aee, 0x40aa, 0xc524, 0x46a9, 0x4a65, 0x404e, 0xc4bf, 0x4626, },
            {0x4aee, 0x40aa, 0xc524, 0x46a9, 0x4a65, 0x404e, 0xc4bf, 0x4626, },
        },
    },
};

struct rvv_reg src1[] = {
    {
        .float64 = {
            {0x402b982fa8cba1c2, 0xc0371fb2129cb102},
            {0x402b982fa8cba1c2, 0xc0371fb2129cb102},
        },
        .float32 = {
            {0xc843ca22, 0x483c7bbf, 0xc73b64a7, 0x7f7fffff, },
            {0xc843ca22, 0x483c7bbf, 0xc73b64a7, 0x481eefee, },
        },
        .float16 = {
            {0xcb85, 0x4b3d, 0xc332, 0x4a1a, 0xcaf1, 0x4aae, 0xc2a4, 0x49a2, },
            {0x7bff, 0x4b3d, 0xfbff, 0x4a1a, 0xcaf1, 0x4aae, 0xc2a4, 0x49a2, },
        },
    },
};

struct rvv_reg dst_vl[] = {
    {
        .wfloat64 = {
            {0x411783c190000000, 0x410c44c4ec000000, 0x41001b80f0000000, 0x4111a7f0e8000000,},
            {0x411783c190000000, 0x410c44c4ec000000, 0xc7efffffe0000000, 0x0000000000000000,},
        },
        .wfloat32 = {
            {0x41e73000, 0x418af800, 0x411e6000, 0x41ad9800, 0x41dea000, 0x41898800, 0x4124b000, 0x41a98000,},
            {0x41e73000, 0x418af800, 0x411e6000, 0x41ad9800, 0x41dea000, 0x41898800, 0x4124b000, 0x00000000,},
        },
    },
};

struct rvv_reg dst_even[] = {
    {
        .wfloat64 = {
            {0x411783c190000000, 0x1111111111111111, 0x41001b80f0000000, 0x1111111111111111,},
            {0x411783c190000000, 0x1111111111111111, 0xc7efffffe0000000, 0x1111111111111111,},
        },
        .wfloat32 = {
            {0x41e73000, 0x11111111, 0x411e6000, 0x11111111, 0x41dea000, 0x11111111, 0x4124b000, 0x11111111,},
            {0x41e73000, 0x11111111, 0x411e6000, 0x11111111, 0x41dea000, 0x11111111, 0x4124b000, 0x11111111,},
        },
    },
};

struct rvv_reg dst_odd[] = {
    {
        .wfloat64 = {
            {0x1111111111111111, 0x410c44c4ec000000, 0x1111111111111111, 0x4111a7f0e8000000,},
            {0x1111111111111111, 0x410c44c4ec000000, 0x1111111111111111, 0x4111a7f0e8000000,},
        },
        .wfloat32 = {
            {0x11111111, 0x418af800, 0x11111111, 0x41ad9800, 0x11111111, 0x41898800, 0x11111111, 0x41a98000,},
            {0x11111111, 0x418af800, 0x11111111, 0x41ad9800, 0x11111111, 0x41898800, 0x11111111, 0x41a98000,},
        },
    },
};

struct rvv_reg res;

int main(void)
{
    int i = 0;
    init_testsuite("Testing insn vfwsub.vf\n");


    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vfwsub_vf_16(vlmax_16 - 1, src0[i].float16[0],
                src1[i].float16[0][0], res.wfloat32[0], pad.fixu32[0]);
        result_compare_s32_lmulw(res.wfloat32[0], dst_vl[i].wfloat32[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vfwsub_vf_16_vm(src0[i].float16[0], src1[i].float16[0][0],
                res.wfloat32[0], vmo.fixu16, pad.fixu32[0]);
        result_compare_s32_lmulw(res.wfloat32[0], dst_odd[i].wfloat32[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vfwsub_vf_16_vm(src0[i].float16[0], src1[i].float16[0][0],
                res.wfloat32[0], vme.fixu16, pad.fixu32[0]);
        result_compare_s32_lmulw(res.wfloat32[0], dst_even[i].wfloat32[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vfwsub_vf_32(vlmax_32 - 1, src0[i].float32[0],
                src1[i].float32[0][0], res.wfloat64[0], pad.fixu64[0]);
        result_compare_s64_lmulw(res.wfloat64[0], dst_vl[i].wfloat64[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vfwsub_vf_32_vm(src0[i].float32[0], src1[i].float32[0][0],
                res.wfloat64[0], vme.fixu32, pad.fixu64[0]);
        result_compare_s64_lmulw(res.wfloat64[0], dst_even[i].wfloat64[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vfwsub_vf_32_vm(src0[i].float32[0], src1[i].float32[0][0],
                res.wfloat64[0], vmo.fixu32, pad.fixu64[0]);
        result_compare_s64_lmulw(res.wfloat64[0], dst_odd[i].wfloat64[0]);
    }

    return done_testing();
}
