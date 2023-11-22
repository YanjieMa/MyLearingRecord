# 0 "add.c"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "add.c"


int myadd(int x, int y)
{
 static int tmp = 0x10;
 tmp = tmp + x + y;
 return tmp;
}
