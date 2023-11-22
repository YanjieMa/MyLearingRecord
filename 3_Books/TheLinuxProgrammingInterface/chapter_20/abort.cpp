#include <iostream>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>

using namespace std;

//信号不会中断自身的执行 只会pending
//信号A执行期间 信号B产生了 如果没有mask 则会打断信号A的执行 若A中正在sleep 返回时直接唤醒； 弱信号B有mask，则执行完A才收到信号B并执行

void (*old_handler)(int);

void sigHandler(int sig)
{
	printf("recv sig num is %d\n",sig);
	if(sig == SIGINT){
		cout << "recv SIGINT" << endl;
	}
	if(sig == SIGQUIT){
		cout << "recv SIGQUIT" << endl;
	}
	sleep(3);
	printf("sig handler end\n");
	return;
}

//2.信号的类型和默认行为
// SIGABRT  终止进程			core
// ulimit -a 查看设置
// ulimit -c 1024 设置核心转储文件大小为1024KByte
void test_abort()
{
	signal(SIGABRT,sigHandler);
	printf("sigabrt test before\n");
	abort();
	printf("sigabrt test after\n");
}
// SIGALRM  实时定时器过期		term
// SIGBUS	内存访问错误		core
// SIGCHID	终止或者停止子进程	ignore
// SIGCONT	若停止则继续		cont
// SIGFPE	算数异常			term
// SIGHUP	挂起				term
// SIGILL	非法指令			core
// SIGINFO	
// SIGINT	终端中断 Ctrl + c	term
// SIGIO	I/O时可能产生
// SIGKILL  必杀 kill -9		term
// SIGPIPE	管道断开			term
// SIGQUIT	终端退出 Ctrl + \	core
// SIGSTOP	确保停止			stop
// SIGTERM	终止进程			term
//



//3.改变信号处置 signal
//在信号处理函数执行期间
//再次收到信号 信号处于pending 储存一次接收
//信号处理函数执行完毕 再次生效
void test_signal()
{
	void (*oldHandler)(int);

	oldHandler = signal(SIGINT,sigHandler);	
	if(oldHandler == SIG_ERR){
		printf("sig err\n");
		return ;
	}
	sleep(5); //在sleep时 收到信号会被立刻唤醒 不再sleep
	printf("sleep over, begin sleep\n");
	sleep(5);
	printf("test_signal end\n");
}

//4.信号处理器简介
void test_resigint()
{
	if(signal(SIGINT,sigHandler) == SIG_ERR){
		return;
	}
	if(signal(SIGQUIT,sigHandler) == SIG_ERR){
		return;
	}
	for(int i=0; i< 10; i++){
		sleep(1);
		printf("now i is:%d\n",i);
	}	
}

//5.发送信号 kill
// pid > 0 发送给指定进程
// pid = 0 发送信号给同组进程 包括自己
// pid < -1 发送给指定组内的所有进程
// pid = -1 发送给有权发送的每个进程 除去自身和init进程(1)
void test_kill()
{
	signal(SIGINT,sigHandler);
	sleep(2);
	kill(getpid(),SIGINT);
	sleep(2);

}

//6.检测进程是否存在
void test_hasprocess(char *para)
{
	int pid = atoi(para);
	int ret = kill(pid,0);
	printf("ret is %d\n",ret);
	if(ret == 0){
		printf("发送成功 进程存在\n");
		return;
	}
	if(errno == ESRCH){
		printf("进程不存在 ESRCH \n");
	}
	if(errno == EPERM){
		printf("进程存在 无权发送 EPERM \n");
	}
}

//7.发送信号的其他方式 raise()
//单线程中 raise(sig) == kill(getpid(),sig)
//多线程中 raise(sig) == pthread_kill(pthread_self(),sig)
//raise 向自身发送信号
//killpg(pgrp, sig) == kill(-pgrp,sig)
void test_raise()
{
	signal(SIGINT, sigHandler);
	sleep(1);
	raise(SIGINT);
	sleep(1);	
	raise(SIGINT);
}

//8.显示信号描述

void test_strsignal()
{
	char *p;
	p = strsignal(20);
	printf("str signal is %s\n",p);

}

//9.信号集
void test_sigset()
{
	//初始化信号集
	sigset_t sigset_empty;
	sigset_t sigset_fill;
	
	sigemptyset(&sigset_empty);
	sigfillset(&sigset_fill);

	//增删信号
	sigaddset(&sigset_empty,SIGQUIT);
	sigaddset(&sigset_empty,SIGINT);
	int ismember = sigismember(&sigset_empty,SIGQUIT);
	if(ismember != 0){
		printf("SIGQUIT is member\n");
	}
	sigdelset(&sigset_empty,SIGQUIT);
	ismember = sigismember(&sigset_empty,SIGQUIT);
	if(ismember == 0){
		printf("SIGQUIT is not member\n");
	}
	
	//信号集操作 集合操作
	//sigandset(sigset_t *dest,sigset_t *left, sigset_t *right)
	//sigorset(sigset_t *dest,sigset_t *left, sigset_t *right)
	
}

void printSigset(const sigset_t *sigset)
{
	for(int sig=0;sig < 64; sig++){
		if(sigismember(sigset,sig)){
			printf("%d(%s) in member\n",sig,strsignal(sig));
		}
	}
}

//10.信号掩码
// sigprocmask(int how,sigset_t *set,sigset_t *oldset);
// how: SIG_BLOCK SIG_UNBLOCK SIG_SETMASK
// 设置了信号 pending 后, 收到信号不会立刻执行，先暂存一个，unblock之后执行一次
// not pending后 信号有效
void test_sigprocmask()
{
	//注册信号处理函数
	signal(SIGINT,sigHandler);
	//设置信号阻塞
	sigset_t block_set;
	sigemptyset(&block_set);
	sigaddset(&block_set,SIGINT);
	sigprocmask(SIG_BLOCK,&block_set,NULL);
	printf("设置了SIGINT pending\n");
	sleep(3);
	sigprocmask(SIG_UNBLOCK,&block_set,NULL);
	printf("设置了SIGINT not pending\n");
	
	sleep(3);
}

//11.处于等待状态的信号
// 可以检测收到那些信号 处于pending状态的信号 不会再次调用handler处理函数
void test_sigpending()
{
	//注册信号处理函数
	signal(SIGINT,sigHandler);
	//设置信号阻塞
	sigset_t block_set;
	sigemptyset(&block_set);
	sigaddset(&block_set,SIGINT);
	sigprocmask(SIG_BLOCK,&block_set,NULL);
	printf("设置了SIGINT pending\n");
	sleep(3);
	sigset_t sigp;
	sigpending(&sigp);
	int ret = sigismember(&sigp,SIGINT); //可以检测某个信号是否处于pending状态
	printf("ret is %d\n",ret);
	sleep(3);
}	

//13.处理信号的另一种方式 sigaction
void test_sigaction()
{
	struct sigaction act;
	sigemptyset(&act.sa_mask);//此掩码的作用是调用信号处理函数时，屏蔽设置了掩码的信号 等到信号处理函数执行完毕 再解除屏蔽 接收到信号
	sigaddset(&act.sa_mask,SIGINT);
	sigaddset(&act.sa_mask,SIGQUIT);
	act.sa_handler = sigHandler;
	act.sa_flags = SA_SIGINFO;
	sigaction(SIGINT,&act,NULL);
	sleep(3); 
}


//14.pause
// pause()将暂停进程的执行
// 直至信号处理器函数中断该调用为止
void test_pause()
{
	signal(SIGINT,sigHandler);
	pause();
	printf("中断了\n");
	sleep(1);
}

void sigActionHandler(int sig,siginfo_t *info, void *myact)
{
	printf("recv sig %d, para %s\n",sig,(char *)(info->si_ptr));	
}

void test_sigqueue()
{
	struct sigaction sa;
	sa.sa_sigaction = sigActionHandler;
	sa.sa_flags = SA_SIGINFO;
	sigfillset(&sa.sa_mask);
	sigaction(40,&sa,NULL);
	
	sigset_t block_mask;
	sigemptyset(&block_mask);
	sigaddset(&block_mask,SIGINT);
	sigprocmask(SIG_SETMASK,&block_mask,NULL);

	sleep(3);
	union sigval sv;
	char buf[1024] = "123";
	sv.sival_ptr = buf;
	sigqueue(getpid(),40,sv);
	sleep(1);
	printf("end\n");
}

int main(int argc,char **argv)
{
	test_pause();
}

