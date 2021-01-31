#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
pthread_mutex_t lockx;
pthread_mutex_t locky;
pthread_mutex_t lockz;

char str[20];
char str2[20];
char list[10];
char numbers[10];
int counter=0;
int sayi=0;
int temp=0;
int i=0;
int npipefd;
FILE * fpointer;
char * myfifo="/tmp/myfifo";
void *x(){
	
	pthread_mutex_lock(&lockx);
	if(counter<sayi){
	fgets(numbers,10,fpointer);
	temp=atoi(numbers);
	printf("%d. x=%d\n",counter+1,temp);
	list[0]=temp;
	counter++;
	
	
	pthread_mutex_unlock(&locky);
	}
}
void *y(){
	
	pthread_mutex_lock(&locky);
	if(counter<sayi){
	fgets(numbers,10,fpointer);
	temp=atoi(numbers);
	printf("%d. y=%d\n",counter+1,temp);
	list[1]=temp;
	counter++;
	pthread_mutex_unlock(&lockz);
	}
}
void *z(){
	pthread_mutex_lock(&lockz);
	if(counter<sayi){
	fgets(numbers,10,fpointer);
	temp=atoi(numbers);
	printf("%d. z=%d\n",counter+1,temp);
	list[2]=temp;
	counter++;
	pthread_mutex_unlock(&lockx);
	}
}
int main(){
	fpointer = fopen("numbers.txt","r");
	puts("satir sayisi giriniz:");
    gets(str);
	sayi=atoi(str);
	//-------------------------------------------------
	pthread_mutex_init(&lockx, NULL);
	pthread_mutex_init(&lockz, NULL);
	pthread_mutex_init(&locky, NULL);
	pthread_mutex_lock(&locky);
	pthread_mutex_lock(&lockz);
	pthread_t xthread;
	pthread_t zthread;
	pthread_t ythread;
	void* status;
	for(i=0;i<(sayi/3);i++){
    pthread_create(&xthread,NULL,x,NULL);
    pthread_create(&zthread,NULL,z,NULL);
    pthread_create(&ythread,NULL,y,NULL);
	sleep(1);
	mkfifo(myfifo,0666);
	npipefd=open(myfifo, O_WRONLY);
	write(npipefd,list,10);
	close(npipefd);
	}
	pthread_join(xthread,&status);
	pthread_join(zthread,&status);
	pthread_join(ythread,&status);
	fclose(fpointer);
	return 0;
}