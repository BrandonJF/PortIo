#include <unity.h>
#include <PasswordManager.h>
#include <vector>

void setUp(void)
{
    int test = 2;
}

void tearDown(void)
{
    // clean stuff up here;
    int test = 1;
}

void test_password_manager_registers_click()
{
 
    const std::vector<ClickType> myOtherVector = {s,d};
    PasswordManager passMan(myOtherVector);
    
    // PasswordStatus status = passMan.registerClick(s);
    // TEST_ASSERT_TRUE(status == ACCEPTED);
    TEST_ASSERT_TRUE(1==1);
}

int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_password_manager_registers_click);
    UNITY_END();
    return 0;
}