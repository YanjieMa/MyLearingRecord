

int myadd(int x, int y)
{
	static int tmp = 0x10;
	tmp = tmp + x + y;
	return tmp;
}
