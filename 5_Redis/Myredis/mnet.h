

#ifndef __MNET_H__
#define __MNET_H__

#define ANET_OK 0
#define ANET_ERR -1
#define ANET_ERR_LEN 256

int anetResolve(char *err, char *host, char *ipbuf);


#endif /* __MNET_H__ */