#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

//fork()와 wait()함수 사용한 예제 코드.

int main(int argc, char *argv[]){

	printf("\nIm the main program, (pid : %d)\n", (int) getpid());
	int a = fork();
	wait(NULL);

	if (a<0) {
		fprintf(stderr, "fork failed\n");
		exit(1);
	}

	else if (a==0) {

		printf("\nI am child2 (pid : %d)\n", (int) getpid());
		printf("my parent is : (pid : %d)\n\n", (int) getppid());

		int b = fork();
		
		if (b<0) {
			fprintf(stderr, "fork failed\n");
			exit(1);
		}
		else if (b==0) {
			printf("I am child3 (pid : %d)\n", (int) getpid());
			printf("my parent is : (pid : %d)\n\n", (int) getppid());
		}

		else {
			int c = fork();
			if (c<0) {
				fprintf(stderr, "fork failed\n");
				exit(1);
			}
			else if (c==0){
				printf("I am child4 (pid : %d)\n", (int) getpid());
				printf("my parent is : (pid : %d)\n\n",(int) getppid());
				
			}
			else {
				int d = fork();
				if (d<0) {
					fprintf(stderr, "fork failed\n");
					exit(1);
				}
				else if (d==0) {
					printf("I am child 5 (pid : %d)\n", (int) getpid());
					printf("my parent is : (pid: %d)\n\n\n\n", (int) getppid());
				}
			}
			wait(NULL);
			
		}
		wait(NULL);

	}
	else {
		int child6 = fork();
		wait(NULL);
	
		if (child6<0) {
			fprintf(stderr,"fork failed\n");
			exit(1);
		}
		else if (child6 == 0 ){
			printf("I am child 6 (pid: %d)\n", (int) getpid());
			printf("my parent is : (pid: %d)\n\n", (int) getppid());	

			int child7 = fork();
			
			if (child7 < 0){
				fprintf(stderr, "fork failed\n");
				exit(1);
			}
			else if (child7 == 0){
				printf("I am child 7 (pid : %d)\n", (int) getpid());
				printf("my parent is : (pid: %d)\n\n", (int) getppid());
			}
			else {
				int child8 = fork();
				
				if (child8 < 0) {
					fprintf(stderr, "fork failed\n");
					exit(1);
				}
				else if (child8 == 0 ){
					printf("I am child 8 (pid: %d)\n", (int) getpid());
					printf("my parent is : (pid: %d)\n\n", (int) getppid());	
				}
				else {
					int child9 = fork();
			
					if (child9 < 0){
						fprintf(stderr, "fork failed\n");
						exit(1);
					}
					else if (child9 == 0){
						printf("I am child 9 (pid : %d)\n", (int) getpid());
						printf("my parent is : (pid: %d)\n\n", (int) getppid());
					}
					
				}
				wait(NULL);
			}
			wait(NULL);	
		}
		wait(NULL);
	}
}


















			