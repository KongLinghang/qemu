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
            {0xffffffffffffffff, 0x0000000000000000,},
            {0x0000000000000005, 0x0000000000102000,},
        },
        .float32 = {
            {0x0002d1c8, 0x00007970, 0x00001000, 0x00015ad4,},
            {0xffffffff, 0x00007970, 0x00000000, 0x00030000,}, 
        },
        .float16 = {
            {0x000e, 0x0002, 0x0020, 0x0007, 0x000d, 0x0002, 0x0200, 0x0006,},
            {0x000e, 0xffff, 0x0010, 0x0000, 0x000d, 0x0002, 0x0300, 0x0e00,}, 
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
        .float64 = {
            {0x43f0000000000000, 0x0000000000000000,},
            {0x4014000000000000, 0x0000000000000000,},
        },
        .float32 = {
            {0x48347200, 0x46f2e000, 0x45800000, 0x47ad6a00,},
            {0x4f800000, 0x46f2e000, 0x00000000, 0x00000000,},
        },
        .float16 = {
            {0x4b00, 0x4000, 0x5000, 0x4700, 0x4a80, 0x4000, 0x6000, 0x4600,},
            {0x4b00, 0x7c00, 0x4c00, 0x0000, 0x4a80, 0x4000, 0x6200, 0x0000,},
        },
    },
};

struct rvv_reg dst_even[] = {
    {
        .float64 = {
            {0x43f0000000000000, 0x1111111111111111,},
            {0x4014000000000000, 0x1111111111111111,},
        },
        .float32 = {
            {0x48347200, 0x11111111, 0x45800000, 0x11111111,},
            {0x4f800000, 0x11111111, 0x00000000, 0x11111111,},
        },
        .float16 = {
            {0x4b00, 0x1111, 0x5000, 0x1111, 0x4a80, 0x1111, 0x6000, 0x1111,},
            {0x4b00, 0x1111, 0x4c00, 0x1111, 0x4a80, 0x1111, 0x6200, 0x1111,},
        },
    },
};

struct rvv_reg dst_odd[] = {
    {
        .float64 = {
            {0x1111111111111111, 0x0000000000000000,},
            {0x1111111111111111, 0x4130200000000000,},
        },
        .float32 = {
            {0x11111111, 0x46f2e000, 0x11111111, 0x47ad6a00,},
            {0x11111111, 0x46f2e000, 0x11111111, 0x48400000,},
        },
        .float16 = {
            {0x1111, 0x4000, 0x1111, 0x4700, 0x1111, 0x4000, 0x1111, 0x4600,},
            {0x1111, 0x7c00, 0x1111, 0x0000, 0x1111, 0x4000, 0x1111, 0x6b00,},
        },
    },
};

struct rvv_reg res;

int main(void)
{
    int i = 0;
    init_testsuite("Testing insn vfcvt.f.xu.v\n");


    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vfcvt_f_xu_v_16(vlmax_16 - 1, src0[i].float16[0],
                src1[i].float16[0], res.float16[0], pad.fixu16[0]);
        result_compare_s16_lmul(res.float16[0], dst_vl[i].float16[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vfcvt_f_xu_v_16_vm(src0[i].float16[0], src1[i].float16[0],
                res.float16[0], vmo.fixu16, pad.fixu16[0]);
        result_compare_s16_lmul(res.float16[0], dst_odd[i].float16[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vfcvt_f_xu_v_16_vm(src0[i].float16[0], src1[i].float16[0],
                res.float16[0], vme.fixu16, pad.fixu16[0]);
        result_compare_s16_lmul(res.float16[0], dst_even[i].float16[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vfcvt_f_xu_v_32(vlmax_32 - 1, src0[i].float32[0],
                src1[i].float32[0], res.float32[0], pad.fixu32[0]);
        result_compare_s32_lmul(res.float32[0], dst_vl[i].float32[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vfcvt_f_xu_v_32_vm(src0[i].float32[0], src1[i].float32[0],
                res.float32[0], vme.fixu32, pad.fixu32[0]);
        result_compare_s32_lmul(res.float32[0], dst_even[i].float32[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vfcvt_f_xu_v_32_vm(src0[i].float32[0], src1[i].float32[0],
                res.float32[0], vmo.fixu32, pad.fixu32[0]);
        result_compare_s32_lmul(res.float32[0], dst_odd[i].float32[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vfcvt_f_xu_v_64(vlmax_64 - 1, src0[i].float64[0],
                src1[i].float64[0], res.float64[0], pad.fixu64);
        result_compare_s64_lmul(res.float64[0], dst_vl[i].float64[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vfcvt_f_xu_v_64_vm(src0[i].float64[0], src1[i].float64[0],
                res.float64[0], vmo.fixu64, pad.fixu64[0]);
        result_compare_s64_lmul(res.float64[0], dst_odd[i].float64[0]);
    }

    for (i = 0; i < sizeof(src0) / sizeof(struct rvv_reg); i++) {
        test_vfcvt_f_xu_v_64_vm(src0[i].float64[0], src1[i].float64[0],
                res.float64[0], vme.fixu64, pad.fixu64[0]);
        result_compare_s64_lmul(res.float64[0], dst_even[i].float64[0]);
    }

    return done_testing();
}
