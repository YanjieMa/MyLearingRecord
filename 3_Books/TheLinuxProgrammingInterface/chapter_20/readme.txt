

1.信号安装
signal()：不支持信号传递信息，主要用于非实时信号安装；
	信号处理函数 void sigHandler(int signum);
sigaction():支持信号传递信息，可用于所有信号安装；
	int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
	signum：要操作的signal信号。
	act：设置对signal信号的新处理方式。
	oldact：原来对信号的处理方式。
	返回值：0 表示成功，-1 表示有错误发生。
           struct sigaction {
               void     (*sa_handler)(int);
               void     (*sa_sigaction)(int, siginfo_t *, void *);
               sigset_t   sa_mask;
               int        sa_flags;
               void     (*sa_restorer)(void);
           };
	其中 sigaction结构体
		sa_handler:信号处理函数
		sa_mask：指定信号处理程序执行过程中需要阻塞的信号；
		sa_flags：标示位
			SA_RESTART：使被信号打断的syscall重新发起。
			SA_NOCLDSTOP：使父进程在它的子进程暂停或继续运行时不会收到 SIGCHLD 信号。
			SA_NOCLDWAIT：使父进程在它的子进程退出时不会收到SIGCHLD信号，这时子进程如果退出也不会成为僵 尸进程。
			SA_NODEFER：使对信号的屏蔽无效，即在信号处理函数执行期间仍能发出这个信号。
			SA_RESETHAND：信号处理之后重新设置为默认的处理方式。
			SA_SIGINFO：使用sa_sigaction成员而不是sa_handler作为信号处理函数。
	信号处理函数:void sigactionHandler(int signum,siginfo_t *info, void *myact);
	 siginfo_t {
               int      si_signo;     /* Signal number 信号编号 */
               int      si_errno;     /* An errno value 如果为非零值则错误代码与之关联 */
               int      si_code;      /* Signal code 说明进程如何接收信号以及从何处收到*/
               int      si_trapno;    /* Trap number that caused
                                         hardware-generated signal
                                         (unused on most architectures) */
               pid_t    si_pid;       /* Sending process ID适用于SIGCHLD，代表被终止进程的PID  */
               uid_t    si_uid;       /* Real user ID of sending process适用于SIGCHLD,代表被终止进程所拥有进程的UID  */
               int      si_status;    /* Exit value or signal 适用于SIGCHLD，代表被终止进程的状态 */
               clock_t  si_utime;     /* User time consumed 适用于SIGCHLD，代表被终止进程所消耗的用户时间 */
               clock_t  si_stime;     /* System time consumed 适用于SIGCHLD，代表被终止进程所消耗系统的时间 */
               ==================
               sigval_t si_value;     /* Signal value */
               ==================
               int      si_int;       /* POSIX.1b signal */
               void    *si_ptr;       /* POSIX.1b signal */
               int      si_overrun;   /* Timer overrun count;
                                         POSIX.1b timers */
               int      si_timerid;   /* Timer ID; POSIX.1b timers */
               void    *si_addr;      /* Memory location which caused fault */
               long     si_band;      /* Band event (was int in
                                         glibc 2.3.2 and earlier) */
               int      si_fd;        /* File descriptor */
               short    si_addr_lsb;  /* Least significant bit of address
                                         (since Linux 2.6.32) */
               void    *si_call_addr; /* Address of system call instruction
                                         (since Linux 3.5) */
               int      si_syscall;   /* Number of attempted system call
                                         (since Linux 3.5) */
               unsigned int si_arch;  /* Architecture of attempted system call
                                         (since Linux 3.5) */
           }
2.信号发送
kill()：用于向进程或进程组发送信号；
sigqueue()：
	int sigqueue(pid_t pid, int sig,const union sigval value);
	union sigval{
		 int sigval_int;
		 void * sigval_ptr;
	};
	siginfo_t 结构体中(sigval_t) si_value就是sigqueue函数中传入的第三个参数sigval
	siginfo_t 结构体中(int) si_int就是从sigqueue函数中传入的第三个参数sigval.sival_int中获得
	siginfo_t 结构体中si_ptr就是从sigqueue函数中传入的第三个参数sigval.sival_ptr中获得
	只能向一个进程发送信号，不能像进程组发送信号；主要针对实时信号提出，与sigaction()组合使用，当然也支持非实时信号的发送；
alarm()：用于调用进程指定时间后发出SIGALARM信号；
setitimer()：设置定时器，计时达到后给进程发送SIGALRM信号，功能比alarm更强大；
abort()：向进程发送SIGABORT信号，默认进程会异常退出。
raise()：用于向进程自身发送信号；

3.信号相关函数
信号集操作函数
sigemptyset(sigset_t *set)：信号集全部清0；
sigfillset(sigset_t *set)： 信号集全部置1，则信号集包含linux支持的64种信号；
sigaddset(sigset_t *set, int signum)：向信号集中加入signum信号；
sigdelset(sigset_t *set, int signum)：向信号集中删除signum信号；
sigismember(const sigset_t *set, int signum)：判定信号signum是否存在信号集中。

信号阻塞函数
sigprocmask(int how, const sigset_t *set, sigset_t *oldset))； 不同how参数，实现不同功能
	SIG_BLOCK：将set指向信号集中的信号，添加到进程阻塞信号集；
	SIG_UNBLOCK：将set指向信号集中的信号，从进程阻塞信号集删除；
	SIG_SETMASK：将set指向信号集中的信号，设置成进程阻塞信号集；
sigpending(sigset_t *set))：获取已发送到进程，却被阻塞的所有信号；
sigsuspend(const sigset_t *mask))：用mask代替进程的原有掩码，并暂停进程执行，直到收到信号再恢复原有掩码并继续执行进程。(上述三步是原子操作)。
int sigwaitinfo(const sigset_t *set,siginfo_t *info);阻塞等待set中的信号达到
int sigtimedwait(const sigset_t *set, siginfo_t *info,const struct timespec* timeout); 在指定时间内阻塞的等待set中的信号抵达
	struct timespec{
		time_t tv_sec;
		long tv_nsec;
	};


如果linux执行一个信号处理函数的时候如果又收到又收到一个同种信号，则不会打断，是排队顺序执行的.
如果linux执行一个信号处理函数的时候如果又收到一个不同种信号，会去执行新的信号处理函数，执行完之后再回来执行。
如果发送了信号但是没有安装对应接收信号，这是子进程会结束掉，即变成僵尸进程.
