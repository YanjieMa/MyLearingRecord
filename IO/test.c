#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h> 

#define STD 0


int main(int argc, char ** argv)
{
	printf(" has begin\n");
#if STD
	char read_buf[1024];
	int fd = open(argv[1],O_RDWR|O_CREAT);
	
	int size;
	while((size = read(fd,read_buf,sizeof(read_buf))) > 0){
		printf("read:\n%s",read_buf);
		bzero(read_buf,sizeof(read_buf));
	}
	

	char write_buf[1024];
	bzero(write_buf,sizeof(write_buf));
	snprintf(write_buf,sizeof(write_buf),"next line %d\n",100);
	write(fd,write_buf,strlen(write_buf));
	write(fd,write_buf,strlen(write_buf));

	int file_size = lseek(fd,0,SEEK_END);
	printf("file size is %d\n",file_size);
	close(fd);
#else
	FILE *fp;
	fp = fopen(argv[1],"r+");
	int ret;
	char read_buf[1024];
	while(ret = fread(read_buf,sizeof(char),sizeof(read_buf),fp)){
		printf("read:\n%s",read_buf);
		bzero(read_buf,sizeof(read_buf));
	}


	char write_buf[1024];
	bzero(write_buf,sizeof(write_buf));
	sprintf(write_buf,"fopen func %d\n",1);
	fwrite(write_buf,sizeof(char),strlen(write_buf),fp);
	
	int ch;

	fseek(fp,0,SEEK_SET);
	while((ch = fgetc(fp)) != EOF){
		printf("%c",ch);
	}
	write(STDOUT_FILENO,"-----------------------\n",40);
	char str[1024];
	fseek(fp,0,SEEK_SET);
	while(fgets(str,sizeof(str),fp) != NULL){
		printf("%s",str);
	}


	fclose(fp);	
#endif


	return 0;

}
