#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
int toplam;
int main(){
int fd1;
int x,y,z;
char list[10];
    char * myfifo = "/tmp/myfifo";
    mkfifo(myfifo, 0666);
    int a;
        fd1 = open(myfifo,O_RDONLY);
        read(fd1, list, 10);
		toplam=list[0]+list[1]+list[2];
		printf("%d\n",toplam);
        close(fd1);
    return 0;
}