#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>


int main (int argc, char *argv[]){

	int pid;    //for the identification of the child process
	int i;  //for the iteration
	char str[20];   //string for the system command

	pid = fork ();  //creation and identificantion of the child process

	if ( pid < 0 ){ //if the fork isn't working
		perror ("Error"); 
		exit (-1);  //end the program with the code error -1 
	}
	else if( pid > 0 ){ //parent process run it 
		for(i=0;i<10;i++){
			sleep(1);   //wait 1 second during the iteration
			sprintf(str,"ps -p %d -o %%cpu,sz",pid);    //formating the string for the command
			system(str); 

		}	
		kill(pid,SIGKILL);	//function to kill the child process
	}

	else{	//child process run it 
		
		if (strcmp (argv[1], "cpu") == 0)   //if the argument indicated is cpu
		for(;;){}	//code for intense usage of cpu
		
		else if (strcmp (argv[1], "cpu-mem") == 0)  //if the argument indicated is cpu-mem
		for(;;){malloc(100000);}	//code for intense usage of cpu and memory
		}

exit(0) ; //end the program with the sucess code 0

}

