#include "types.h"
#include "stat.h"
#include "user.h"

#define PASS 1
#define FAIL 0

int
test_info_1(void)
{
  int system_process_count = info(1);
  if(system_process_count < 0)
  {
    printf(1, "error calling info(1)\n");
    return FAIL;
  }
  else
  {
    //printf(1, "system_process_count == %d\n", system_process_count);
    return PASS;
  }
}

int test_info_2(void)
{
  int system_call_count = info(2);
  if(system_call_count < 0)
  {
    printf(1, "error calling info(2)\n");
    return FAIL;
  }
  else
  {
    //printf(1, "system_call_count == %d\n", system_call_count);
    return PASS;
  }
}

int test_info_3(void)
{
  int process_page_count = info(3);
  if(process_page_count < 0)
  {
    printf(1, "error calling info(3)\n");
    return FAIL;
  }
  else
  {
    printf(1, "process_page_count == %d\n", process_page_count);
    return PASS;
  }
return PASS;
}


int main(int argc, char * argv[])
{
  int rc = test_info_1();
  rc &= test_info_2();
  rc &= test_info_3();
  if(!rc)
  {
    printf(1, "info(...) tests fail\n");
  }
  else
  {
    printf(1, "info(...) tests pass\n");
  }
  exit();
}
