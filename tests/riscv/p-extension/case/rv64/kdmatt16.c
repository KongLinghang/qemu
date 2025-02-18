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
#include "rvp_insn.h"
#include "sample_array.h"
int main(void)
{
    int i = 0, length;
    init_testsuite("Testing insn kdmatt16\n");

    length = sizeof(samples_kdmatt16) / sizeof(struct ternary_calculation);

    for (i = 0; i < length; i++) {
        TEST(test_kdmatt16(samples_kdmatt16[i].op1,
                        samples_kdmatt16[i].op2,
                        samples_kdmatt16[i].op3)
                     == samples_kdmatt16[i].result);
    }
    return done_testing();
}
