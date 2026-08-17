#include "unity.h"
#include "register_file.h"

void test_reg_init_sets_default_values(void) {
    struct reg_file regs;

    // set to non-default values to make sure init really changes them
    regs.af.pair = 0;
    regs.bc.pair = 0;
    regs.de.pair = 0;
    regs.hl.pair = 0;
    regs.sp = 0;
    regs.pc = 0;

    // call function under test
    reg_init(&regs);

    // verify values against spec
    TEST_ASSERT_EQUAL_UINT16(0x01b0, regs.af.pair);
    TEST_ASSERT_EQUAL_UINT16(0x0013, regs.bc.pair);
    TEST_ASSERT_EQUAL_UINT16(0x00d8, regs.de.pair);
    TEST_ASSERT_EQUAL_UINT16(0x014d, regs.hl.pair);
    TEST_ASSERT_EQUAL_UINT16(0xfffe, regs.sp);
    TEST_ASSERT_EQUAL_UINT16(0x0100, regs.pc);
}
