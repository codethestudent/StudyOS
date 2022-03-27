#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

//Making processes end in order of 3 5 4 2 7 8 9 6 1.

int main(int argc, char *argv[]){
	int fd1[2], fd2[2], fd3[2], fd4[2], rc = 0;
	char str[] = "finish!";
	char buf1[10], buf2[10], buf3[10], buf4[10];
	
	if ((rc = pipe(fd1)) < 0) {
		printf("pipe error!\n");
	}
	else if ((rc = pipe(fd2)) < 0) {
		printf("pipe error!\n");
	}
	else if ((rc = pipe(fd3)) < 0) {
		printf("pipe error!\n");
	}
	else if ((rc = pipe(fd4)) < 0) {
		printf("pipe error!\n");
	}
	
	printf("\nIm the main program, (pid : %d)\n", (int) getpid());
	int a = fork();
	wait(NULL);

	if (a<0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	}

	else if (a==0) { //2번 프로세스 생성

		printf("\nI am child2 (pid : %d)\n", (int) getpid());
		printf("my parent is : (pid : %d)\n\n", (int) getppid());

		int b = fork(); //3번 프로세스 생성
		
		if (b<0) {
			fprintf(stderr, "fork failed\n");
			exit(1);
		}
		else if (b==0) { //3번 프로세스
			printf("\nI am child3 (pid : %d)\n", (int) getpid());
			printf("my parent is : (pid : %d)\n\n", (int) getppid());
			
			close(fd1[0]);
			write(fd1[1], str, sizeof(str));
			printf("child 3 end\n");
			return 0;
		}

		else {
			int c = fork(); //4번 프로세스 생성
			if (c<0) {
				fprintf(stderr, "fork failed\n");
				exit(1);
			}
			else if (c==0){ // 4번 프로세스
				printf("\nI am child4 (pid : %d)\n", (int) getpid());
				printf("my parent is : (pid : %d)\n\n",(int) getppid());
				
				close(fd2[1]);
				while(strcmp(buf2, str) != 0)
					read(fd2[0], buf2, 10);
				printf("child 4 end\n");
				return 0;
				
			}
			else { //2번 프로세스
				int d = fork(); //5번 프로세스 생성
				if (d<0) {
					fprintf(stderr, "fork failed\n");
					exit(1);
				}
				else if (d==0) { //5번 프로세스
					printf("\nI am child 5 (pid : %d)\n", (int) getpid());
					printf("my parent is : (pid: %d)\n\n\n\n", (int) getppid());
					close(fd2[0]);	
					while(strcmp (buf1, str) != 0)
						read(fd1[0], buf1, 10);
					close(fd1[0]);
					write(fd2[1], str, sizeof(str));
					printf("child 5 end\n");
					return 0;
				}
				else { //2번 프로세스
					wait(NULL);
					wait(NULL);
					wait(NULL);
					printf("child 2 end\n");
					return 0;
				}
			}
			
		}

	}
	else {
		int child6 = fork();
		wait(NULL);
	
		if (child6<0) {
			fprintf(stderr,"fork failed\n");
			exit(1);
		}
		else if (child6 == 0 ){
			printf("\nI am child 6 (pid: %d)\n", (int) getpid());
			printf("my parent is : (pid: %d)\n\n", (int) getppid());	

			int child7 = fork();
			
			if (child7 < 0){
				fprintf(stderr, "fork failed\n");
				exit(1);
			}
			else if (child7 == 0){
				printf("\nI am child 7 (pid : %d)\n", (int) getpid());
				printf("my parent is : (pid: %d)\n\n", (int) getppid());
				close(fd3[0]);
				write(fd3[1], str, sizeof(str));
				printf("child 7 end\n");
				return 0;

			}
			else {
				int child8 = fork();
				
				if (child8 < 0) {
					fprintf(stderr, "fork failed\n");
					exit(1);
				}
				else if (child8 == 0 ){
					printf("\nI am child 8 (pid: %d)\n", (int) getpid());
					printf("my parent is : (pid: %d)\n\n", (int) getppid());	
					close(fd3[1]);
					while(strcmp(buf3, str) !=0)
						read(fd3[0], buf3, 10);
					write(fd4[1], str, sizeof(str));
					printf("child 8 end.\n");
					return 0;
				}
				else {
					int child9 = fork();
			
					if (child9 < 0){
						fprintf(stderr, "fork failed\n");
						exit(1);
					}
					else if (child9 == 0){
						printf("\nI am child 9 (pid : %d)\n", (int) getpid());
						printf("my parent is : (pid: %d)\n\n", (int) getppid());
						close(fd4[1]);
						while(strcmp(buf4, str) !=0)
							read(fd4[0], buf4, 10);
						printf("child 9 end\n");
						return 0;
					}
					else {
						wait(NULL);
						wait(NULL);
						wait(NULL);
						printf("child 6 end\n");
						return 0;
					}
					
				}
			}
		}
		else {
			wait(NULL);
			wait(NULL);
			printf("main process end\n");
			return 0;
		}
	}
}
