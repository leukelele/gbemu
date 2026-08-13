#include "unity.h"
#include "register_file.h"

void test_reg_init_sets_default_values(void) {
    reg_file regs;

    // set to non-default values to make sure init really changes them
    regs.af.reg = 0;
    regs.bc.reg = 0;
    regs.de.reg = 0;
    regs.hl.reg = 0;
    regs.sp = 0;
    regs.pc = 0;

    // call function under test
    reg_init(&regs);

    // verify values against spec
    TEST_ASSERT_EQUAL_UINT16(0x01b0, regs.af.reg);
    TEST_ASSERT_EQUAL_UINT16(0x0013, regs.bc.reg);
    TEST_ASSERT_EQUAL_UINT16(0x00d8, regs.de.reg);
    TEST_ASSERT_EQUAL_UINT16(0x014d, regs.hl.reg);
    TEST_ASSERT_EQUAL_UINT16(0xfffe, regs.sp);
    TEST_ASSERT_EQUAL_UINT16(0x0100, regs.pc);
}
