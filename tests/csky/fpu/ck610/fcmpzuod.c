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
#include "fpu_structs.h"

binary_calculation_64_t samples_fcmpzuod[] = {
    {.op1.a.d = 1.5, .result.a.ull = 0}, /* 1.5, -1.5 */
    {.op1.a.d = -1.5, .result.a.ull = 0}, /* -1.5, 1.5 */
    {.op1.a.d = 1.5, .result.a.ull = 0}, /* 1.5, 1.5 */
};

/* fmtvrl, mfcr32, fcmpzuod */
void test_fcmpzuod()
{
    unsigned int fcmpzuod_psr;
    int i = 0;
    for (i = 0;
        i < sizeof(samples_fcmpzuod) / sizeof(samples_fcmpzuod[0]);
        i++)
    {
        asm ("ldw r2, (%1, 0);\n\t"\
            "ldw r3, (%1, 4);\n\t"\
            "fmtd r2, fr0;\n\t"
            "ldw r4, (%2, 0);\n\t"\
            "ldw r5, (%2, 4);\n\t"\
            "fmtd r4, fr2;\n\t"\
            "fcmpzuod fr0, r2;\n\t"\
            "bt set_true;\n\t"\
            "movi %0, 0\n\t"\
            "br done;\n\t" \
            "set_true:\n\t" \
            "movi %0, 1\n\t" \
            "done:\n\t"
            : "=r"(fcmpzuod_psr)
            : "r"(&samples_fcmpzuod[i].op1.a.i[0]),
            "r"(&samples_fcmpzuod[i].op2.a.i[0])
            : "fr0", "fr1", "r2"
        );
        TEST((fcmpzuod_psr & 0x1)
            == samples_fcmpzuod[i].result.a.ull);
    }
}

int main(void)
{
    int i = 0;
    init_testsuite("Testing fpu fcmpzuod instructions.\n");
    test_fcmpzuod();

    return done_testing();
}