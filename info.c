#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char * argv[])
{
  int rc;
  int i;
  info(2);
  for(i = 1; i <= 3; ++i)
  {
    rc = info(i);
    if(rc < 0)
    {
      printf(1, "error calling info(%d)\n", i);
    }
  }
  for(i = 0; i < 10; ++i)
  {
    rc = info(2);
  }
  exit();
}
