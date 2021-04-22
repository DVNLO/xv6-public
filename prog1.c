#include "types.h"
#include "stat.h"
#include "user.h"
//prog1
int main(int argc, char *argv[])
{
  int const tickets = set_tickets(30);
  int i,k;
  const int loop=43000;
  for(i=0;i<loop;i++) {
    asm(nop);
    //in order to prevent the compiler from optimizing the for loop
    for(k=0;k<loop;k++) {
      asm(nop);
    }
  }
  exit();
}
