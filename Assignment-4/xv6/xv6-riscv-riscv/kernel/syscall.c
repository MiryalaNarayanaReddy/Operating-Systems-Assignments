#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "spinlock.h"
#include "proc.h"
#include "syscall.h"
#include "defs.h"

// Fetch the uint64 at addr from the current process.
int
fetchaddr(uint64 addr, uint64 *ip)
{
  struct proc *p = myproc();
  if(addr >= p->sz || addr+sizeof(uint64) > p->sz)
    return -1;
  if(copyin(p->pagetable, (char *)ip, addr, sizeof(*ip)) != 0)
    return -1;
  return 0;
}

// Fetch the nul-terminated string at addr from the current process.
// Returns length of string, not including nul, or -1 for error.
int
fetchstr(uint64 addr, char *buf, int max)
{
  struct proc *p = myproc();
  int err = copyinstr(p->pagetable, buf, addr, max);
  if(err < 0)
    return err;
  return strlen(buf);
}

static uint64
argraw(int n)
{
  struct proc *p = myproc();
  switch (n) {
  case 0:
    return p->trapframe->a0;
  case 1:
    return p->trapframe->a1;
  case 2:
    return p->trapframe->a2;
  case 3:
    return p->trapframe->a3;
  case 4:
    return p->trapframe->a4;
  case 5:
    return p->trapframe->a5;
  }
  panic("argraw");
  return -1;
}

// Fetch the nth 32-bit system call argument.
int
argint(int n, int *ip)
{
  *ip = argraw(n);
  return 0;
}

// Retrieve an argument as a pointer.
// Doesn't check for legality, since
// copyin/copyout will do that.
int
argaddr(int n, uint64 *ip)
{
  *ip = argraw(n);
  return 0;
}

// Fetch the nth word-sized system call argument as a null-terminated string.
// Copies into buf, at most max.
// Returns string length if OK (including nul), -1 if error.
int
argstr(int n, char *buf, int max)
{
  uint64 addr;
  if(argaddr(n, &addr) < 0)
    return -1;
  return fetchstr(addr, buf, max);
}

extern uint64 sys_chdir(void);
extern uint64 sys_close(void);
extern uint64 sys_dup(void);
extern uint64 sys_exec(void);
extern uint64 sys_exit(void);
extern uint64 sys_fork(void);
extern uint64 sys_fstat(void);
extern uint64 sys_getpid(void);
extern uint64 sys_kill(void);
extern uint64 sys_link(void);
extern uint64 sys_mkdir(void);
extern uint64 sys_mknod(void);
extern uint64 sys_open(void);
extern uint64 sys_pipe(void);
extern uint64 sys_read(void);
extern uint64 sys_sbrk(void);
extern uint64 sys_sleep(void);
extern uint64 sys_unlink(void);
extern uint64 sys_wait(void);
extern uint64 sys_write(void);
extern uint64 sys_uptime(void);
extern uint64 sys_trace(void);
extern uint64 sys_waitx(void);
extern uint64 sys_set_priority(void);

static uint64 (*syscalls[])(void) = {
[SYS_fork]    sys_fork,
[SYS_exit]    sys_exit,
[SYS_wait]    sys_wait,
[SYS_pipe]    sys_pipe,
[SYS_read]    sys_read,
[SYS_kill]    sys_kill,
[SYS_exec]    sys_exec,
[SYS_fstat]   sys_fstat,
[SYS_chdir]   sys_chdir,
[SYS_dup]     sys_dup,
[SYS_getpid]  sys_getpid,
[SYS_sbrk]    sys_sbrk,
[SYS_sleep]   sys_sleep,
[SYS_uptime]  sys_uptime,
[SYS_open]    sys_open,
[SYS_write]   sys_write,
[SYS_mknod]   sys_mknod,
[SYS_unlink]  sys_unlink,
[SYS_link]    sys_link,
[SYS_mkdir]   sys_mkdir,
[SYS_close]   sys_close,
[SYS_trace]   sys_trace,
[SYS_waitx]   sys_waitx,
[SYS_set_priority] sys_set_priority,
};

void name_of_syscall(int num, struct proc *p)
{
	switch (num)
	{
	case 1:
		printf("fork ( ) ");
		break;
	case 2:
		printf("exit ( %d ) ", p->trapframe->a0);
		break;
	case 3:
		printf("wait ( %d ) ", p->trapframe->a0);
		break;
	case 4:
		printf("pipe ( %d ) ", p->trapframe->a0);
		break;
	case 5:
		printf("read ( %d %d %d ) ", p->trapframe->a0, p->trapframe->a1, p->trapframe->a2);
		break;
	case 6:
		printf("kill ( %d ) ", p->trapframe->a0);
		break;
	case 7:
		printf("exec ( %d %d ) ", p->trapframe->a0, p->trapframe->a1);
		break;
	case 8:
		printf("fstat ( %d %d ) ", p->trapframe->a0, p->trapframe->a1);
		break;
	case 9:
		printf("chdir ( %d ) ", p->trapframe->a0);
		break;
	case 10:
		printf("dup ( %d ) ", p->trapframe->a0);
		break;
	case 11:
		printf("getpid ( ) ");
		break;
	case 12:
		printf("sbrk ( %d ) ", p->trapframe->a0);
		break;
	case 13:
		printf("sleep ( %d ) ", p->trapframe->a0);
		break;
	case 14:
		printf("uptime ( ) ");
		break;
	case 15:
		printf("open ( %d %d ) ", p->trapframe->a0, p->trapframe->a1);
		break;
	case 16:
		printf("write ( %d %d %d ) ", p->trapframe->a0, p->trapframe->a1, p->trapframe->a2);
		break;
	case 17:
		printf("mknod ( %d %d %d ) ", p->trapframe->a0, p->trapframe->a1, p->trapframe->a2);
		break;
	case 18:
		printf("unlink ( %d ) ", p->trapframe->a0);
		break;
	case 19:
		printf("link ( %d %d ) ", p->trapframe->a0, p->trapframe->a1);
		break;
	case 20:
		printf("mkdir ( %d ) ", p->trapframe->a0);
		break;
	case 21:
		printf("close ( %d ) ", p->trapframe->a0);
		break;
	case 22:
		printf("waitx ( %d %d %d ) ", p->trapframe->a0, p->trapframe->a1, p->trapframe->a2);
		break;
	default:
		printf("Unknown syscall :( ");
	}
}

void syscall(void)
{
	int num;
	struct proc *p = myproc();

	num = p->trapframe->a7;
	if (num > 0 && num < NELEM(syscalls) && syscalls[num])
	{
		if (p->trace_mask & (1 << num))
		{
			printf("%d: syscall ", p->pid);
			// print args of system call
			name_of_syscall(num, p);

			//	printf("pending in syscall.c"); // pending

			printf(" -> ");
		}

		p->trapframe->a0 = syscalls[num]();
		if (p->trace_mask & (1 << num))
		{
			printf("%d\n", p->trapframe->a0); // return work
		}
	}
	else
	{
		printf("%d %s: unknown sys call %d\n",
			   p->pid, p->name, num);
		p->trapframe->a0 = -1;
	}
}
