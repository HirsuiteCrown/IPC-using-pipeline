#include<iostream>
#include<unistd.h>

void pipeline(const char* process1, const char* process2){
    int fd[2]; //filedescriptor 
    pipe(fd);  //fd[1] at write end and fd[0] at read end. pipe created
    int id = fork();
    if(id !=0){ //parent process
        close(fd[0]); //close the read end
        dup2(fd[1],STDOUT_FILENO); // redirect standard output to write end of pipe
        close(fd[1]);//close write end of pipe

        //when we do write close the read end and after writing close the write end

        //Execute process1
        execlp("/bin/cat" , "cat", "main.cpp", nullptr);  //   /bin/cat => we have to give path of cat command.   this will run [cat main.cpp] on this file
        std::cerr <<"Failed to execute"<<process1<<std::endl;
    }
    else{ //child process
        close(fd[1]); //close the write end
        dup2(fd[0],STDIN_FILENO); //redirect standard input to read end of pipe
        close(fd[0]); //close the read end

        //Execute process2
        execlp("/usr/bin/grep", "grep", "hello", nullptr);
        std::cerr<<"Failed to execute"<<process2<<std::endl;
    }

}

int main(){
    pipeline("cat main.cpp", "grep hello");
    return 0;
}
