

#ifndef __MSDS_H__
#define __MSDS_H__

typedef char * sds;

struct sdshdr {
    long len;
    long free;
    char buf[];
};

sds sdscatlen(sds s, void *t, size_t len);
sds sdsnewlen(const void *init, size_t initlen);
sds sdsempty(void);

#endif /* __MSDS_H__ */