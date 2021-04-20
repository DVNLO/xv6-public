#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char * argv[])
{
  int rc;
  int i;
  for(i = 1; i <= 3; ++i)
  {
    printf(1, "calling info(%d)\n", i);
    rc = info(i);
    if(rc < 0)
    {
      printf(1, "error calling info(%d)\n", i);
    }
    else
    {
      printf(1, "success calling info(%d)\n", i);
    }
  }
  exit();
}
