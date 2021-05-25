#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int
sys_thread_create(void)
{
  int const ptr_sz = 4; // bytes
  void * (*start_routine)(void*);
  void * arg;
  int rc;
  rc = argptr(0, (char **)(&start_routine), ptr_sz);
  if(rc < 0)
  {
    return -1;
  }
  rc = argptr(1, (char **)(&arg), ptr_sz);
  if(rc < 0)
  {
    return -1;
  }
  rc = thread_create(start_routine, arg);
  return rc;
}

int
sys_lock_init(void)
{
  cprintf("sys_lock_init : begin\n");
  int const ptr_sz = 4; // bytes
  lock_t * lk;
  int rc;
  rc = argptr(0, (char **)(&lk), ptr_sz);
  if(rc < 0)
  {
    return -1;
  }
  initlock(lk, "lock_t");
  cprintf("sys_lock_init : end\n");
  return 0;
}

int
sys_lock_acquire(void)
{
  cprintf("sys_lock_acquire : begin\n");
  int const ptr_sz = 4; // bytes
  lock_t * lk;
  int rc;
  rc = argptr(0, (char **)(&lk), ptr_sz);
  if(rc < 0)
  {
    return -1;
  }
  acquire(lk);
  cprintf("sys_lock_acquire : end\n");
  return 0;
}

int
sys_lock_release(void)
{
  cprintf("sys_lock_release : begin\n");
  int const ptr_sz = 4; // bytes
  lock_t * lk;
  int rc;
  rc = argptr(0, (char **)(&lk), ptr_sz);
  if(rc < 0)
  {
    return -1;
  }
  release(lk);
  cprintf("sys_lock_release : end\n");
  return 0;
}