#include "unity.h"
#include "cpu.h"

// setUp and tearDown are required, even if empty
void setUp(void) {}
void tearDown(void) {}

void check_hello_world(void) {
	int result = cpu();
	TEST_ASSERT_EQUAL_INT(13, result);	// "Hello world!\n" is 13 characters
}

int main(void) {
	UNITY_BEGIN();
	RUN_TEST(check_hello_world);
	return UNITY_END();
}
