#include<stdio.h> 
#include<fcntl.h> 
#include<unistd.h> 
#include<dirent.h> 
#include<stdlib.h> 
#include<sys/types.h> 
#include<sys/stat.h> 
#include<string.h>

int checkFileExists(const char *filename);

#define BUFSIZE 100 
int fd, n;

int main(){
	int choice, choice2; 
	while(1){
	printf("\n\n\n\n----MENU-----\n\n\n"); 
	printf("1:Read Content from the file read()\n2:Write Content into the file write()\n3:Using lseek lseek()\n4:Exit\n");
	printf("\n"); 
	printf("Enter your choice: ");
	scanf("%d", &choice); 
	switch(choice){
		case 1:{
			char fname[100];
			DIR *d;
			struct dirent *dir; 
			d = opendir(".");
			printf("-------AVAILABLE FILES----------\n"); 
			if(d){
				while((dir = readdir(d)) != NULL){ 
					printf("%s\n", dir->d_name);
				}
				closedir(d);
			}
			printf("------END OF FILE LIST------\n\n"); 
			printf("Enter File Name to read: ");
			scanf("%s", fname); 

			if(checkFileExists(fname)){
				printf("\n-------------Content of the file is-----------\n");
				char buff[BUFSIZE]; 
				int bytesread, fd, retval;
				fd = open(fname, O_RDONLY); 
				if(fd < 0)
					perror("Failed to open the file"); 

				bytesread = read(fd, buff, sizeof(buff)); 

				if(bytesread < 0)
					perror("Failed to read from the file");
	
				retval = write(STDOUT_FILENO, buff, bytesread);
 
				if(bytesread < 0)
					perror("Failed to Failed to write into the output");
			
				printf("\n\n\n"); 
				break;

			}else{
				printf("Incorrect File Name!\n");
 
				break;
			}
		}

		case 2:{
			char fname[100]; 
			int fd1;
			printf("Enter file name to Write: "); 
			scanf("%s", fname);
			char sen[500]; 
			
			if(checkFileExists(fname)){
				fd1 = open(fname, O_RDWR|O_APPEND); 
				if(fd1 == -1){
					perror(fname);
				}
			
			printf("Enter the file content: \n"); 
			scanf("\n");

			fgets(sen, 500, stdin); 
			write(fd1, sen, strlen(sen)); 
			
			close(fd1);
		
			printf("\n---------------Written Successfully-----------\n\n");
			}
			else{
				printf("\n\n"); 
				printf("New File created Successfully\n");
				fd1 = open(fname, O_RDWR|O_CREAT|O_APPEND, 0777);
				printf("Enter the file content: \n"); 
				scanf("\n");
				fgets(sen, 500, stdin); 
				write(fd1, sen, strlen(sen)); 
				close(fd1);
				printf("\n---------------Written Successfully------------\n\n");
			}

			break;

		}

		case 3:{
			//lseek system call is used to change file offset to a different value 
			FILE *fp;
			long int size = 0; 
			char fname[100];
			printf("Enter file name to perform lseek operation: "); 
			scanf("%s", fname);
			
			if(checkFileExists(fname)){ 
				int choice3;
				int fd;
				int count = 0;

				fp = fopen(fname, "r"); 
				fseek(fp, 0, SEEK_END);
				
				//get the current position of the file pointer 
				size = ftell(fp);
				if(size != -1)
					printf("Total Bytes on the file is: %ld\n",size);
				else
					printf("There is some ERROR!\n");
				fclose(fp);
				printf("\n------MENU------\n"); 
				printf("\n1.From Beginning\n2.From End\n3.At Middle of specified range\n");
				printf("\n\n"); 
				printf("Enter your Choice: ");
				scanf("%d", &choice3); 
				
				if(choice3 == 1){
					int n, fd, fd1; 
					char buf[size];
					printf("Enter how many bytes to set the pointer from beginning: ");
					scanf("%d", &n); 
					if(n < size){
						fd = open(fname, O_RDWR);
						fd1 = lseek(fd, n, SEEK_SET);
						read(fd, buf, size-n); 
						printf("Pointer is at: %d\n", fd1); 
						printf("The content is\n");
						write(STDOUT_FILENO, buf, size); 
						close(fd);
						printf("\n\n\n");
					}
					else{ 	
						printf("The length is not valid!!\n");
					}
				}

				else if(choice3 == 2){
					int n, fd, fd3, fd4; 
					char ch;
					printf("Enter how many bytes to set the pointer from End:");
					scanf("%d", &n); 
					if(n < size){
						fd = open(fname, O_RDWR);
						fd3 = lseek(fd, -n, SEEK_END);
						char buf[fd3];
						fd4 = lseek(fd, 0, SEEK_SET); 
						read(fd, buf, size-n);
						printf("Pointer is at: %d\n", fd3); 
						printf("The content is\n"); 
						write(STDOUT_FILENO, buf, fd3);
						printf("\n\n\n");	 
						close(fd);
					}
					else
						printf("The length is invalid!!\n");
				}
				else if(choice3 == 3){ 
					int f1, f2;
					int n, fd, fd3, fd4;
					printf("Enter first position and last position: "); 
					scanf("%d %d", &f1, &f2);
					if(f1 < size && f2 <= size && f1 < f2){ 
						fd = open(fname, O_RDWR);
						fd3 = lseek(fd, -(size-f2), SEEK_END);
						char buf[fd3];
						fd4 = lseek(fd, f1, SEEK_SET); 
						read(fd, buf, f2-f1);
						printf("Pointer is at: %d\n", fd3); 
						printf("The content is\n"); 
						write(STDOUT_FILENO, buf, f2-f1);
						printf("\n\n\n");
						close(fd);
					}
					else{
						printf("Invalid Inputs!!\n\n");
					}
				}
				else{	
					printf("Invalid choice!\n");
				}

			}

			else{
				printf("File does not exist!\n"); 
				break;
			}

		case 4:{
			printf("\n\n\n\n\n------THANK YOU------\n\n\n\n\n\n\n");
			exit(0);
			}
		}
	}

	}

	return 0;
}


int checkFileExists(const char* filename){ 
	struct stat buffer;
	int exist = stat(filename, &buffer); 
	if(exist == 0)
		return 1; 
	else
		return 0;
}









		





