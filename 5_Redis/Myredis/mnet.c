

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>

#include "mnet.h"

    /*
    inet_aton()函数
    功能：inet_aton()函数用于将点分十进制IP地址转换成网络字节序IP地址;
    原型：int inet_aton(const char *string, struct in_addr *addr);
    返回值：如果这个函数成功，函数的返回值非零，如果输入地址不正确则会返回零;
    头文件：sys/socket.h (Linux)
    */
    /*
    inet_ntoa()函数
    功能inet_ntoa()函数用于网络字节序IP转化点分十进制IP;
    原型：char *inet_ntoa (struct in_addr);
    返回值：若无错误发生，inet_ntoa()返回一个字符指针。否则的话，返回NULL。其中的数据应在下一个WINDOWS套接口调用前复制出来;
    头文件：arpa/inet.h (Linux)
    */
    /*
    inet_ntop()函数
    功能：inet_ntop()函数用于将网络字节序的二进制地址转换成文本字符串;
    原型：const char *inet_pton(int domain, const void *restrict addr, char *restrict str, socklen_t size);
    返回值：若成功，返回地址字符串指针；若出错，返回NULL;
    头文件：arpa/inet.h (Linux)
    */
    /*
    inet_pton()函数
    功能：inet_pton()函数用于将文本字符串格式转换成网络字节序二进制地址;
    原型：int inet_pton(int domain, const char *restrict str, void *restrict addr);
    返回值：若成功，返回1；若格式无效，返回0；若出错，返回-1;
    头文件：arpa/inet.h (Linux)
    */


static void anetSetError(char *err, const char *fmt, ...)
{
    va_list ap;

    if (!err) return;
    va_start(ap, fmt);
    vsnprintf(err, ANET_ERR_LEN, fmt, ap);
    va_end(ap);
}   

//将 "127.0.0.1" 转化为形如点分十进制IP地址 确认此IP可以使用
int anetResolve(char *err, char *host, char *ipbuf)
{
    struct sockaddr_in sa;

    sa.sin_family = AF_INET;

    if (inet_aton(host, &sa.sin_addr) == 0) {
        struct hostent *he;

        // struct hostent {
        // char  *h_name;            /* official name of host */
        // char **h_aliases;         /* alias list */
        // int    h_addrtype;        /* host address type */
        // int    h_length;          /* length of address */
        // char **h_addr_list;       /* list of addresses */
        // }   

        he = gethostbyname(host);
        if (he == NULL) {
            anetSetError(err, "can't resolve: %s\n", host);
            return ANET_ERR;
        }
        memcpy(&sa.sin_addr, he->h_addr, sizeof(struct in_addr));
    }
    strcpy(ipbuf,inet_ntoa(sa.sin_addr));
    return ANET_OK;
}

int anetNonBlock(char *err, int fd)
{
    int flags;

    /* Set the socket nonblocking.
     * Note that fcntl(2) for F_GETFL and F_SETFL can't be
     * interrupted by a signal. */
    if ((flags = fcntl(fd, F_GETFL)) == -1) {
        anetSetError(err, "fcntl(F_GETFL): %s\n", strerror(errno));
        return ANET_ERR;
    }
    if (fcntl(fd, F_SETFL, flags | O_NONBLOCK) == -1) {
        anetSetError(err, "fcntl(F_SETFL,O_NONBLOCK): %s\n", strerror(errno));
        return ANET_ERR;
    }
    return ANET_OK;
}

#define ANET_CONNECT_NONE 0
#define ANET_CONNECT_NONBLOCK 1
static int anetTcpGenericConnect(char *err, char *addr, int port, int flags)
{
    int s, on = 1;
    struct sockaddr_in sa;

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        anetSetError(err, "creating socket: %s\n", strerror(errno));
        return ANET_ERR;
    }
    /* Make sure connection-intensive things like the redis benckmark
     * will be able to close/open sockets a zillion of times */
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));  //SO_REUSRADDR 允许重用本地地址和端口

    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    if (inet_aton(addr, &sa.sin_addr) == 0) {
        struct hostent *he;

        he = gethostbyname(addr);
        if (he == NULL) {
            anetSetError(err, "can't resolve: %s\n", addr);
            close(s);
            return ANET_ERR;
        }
        memcpy(&sa.sin_addr, he->h_addr, sizeof(struct in_addr));
    }
    if (flags & ANET_CONNECT_NONBLOCK) {
        if (anetNonBlock(err,s) != ANET_OK)
            return ANET_ERR;
    }
    if (connect(s, (struct sockaddr*)&sa, sizeof(sa)) == -1) {
        if (errno == EINPROGRESS &&
            flags & ANET_CONNECT_NONBLOCK)
            return s;

        anetSetError(err, "connect: %s\n", strerror(errno));
        close(s);
        return ANET_ERR;
    }
    return s;
}


int anetTcpConnect(char *err, char *addr, int port)
{
    return anetTcpGenericConnect(err,addr,port,ANET_CONNECT_NONE);
}

int anetTcpNoDelay(char *err, int fd)
{
    int yes = 1;
    if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &yes, sizeof(yes)) == -1)
    {
        anetSetError(err, "setsockopt TCP_NODELAY: %s\n", strerror(errno));
        return ANET_ERR;
    }
    return ANET_OK;
}