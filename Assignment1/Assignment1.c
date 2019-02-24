//
//  Assignment1.c
//  
//
//  Created by Abhiram Santhosh on 2/23/19.
//

#include "Assignment1.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/types.h>



int main (){
    
    struct shared_matrix {
        
        int M[3][3]; //first matrix
        int N[3][3]; //second matrix
        int Q[3][3]; //result matrix
    
        int written; //a flag - if 0 means not written, else it has been written on
        char test;
    };
    
    
    //part 1
    /**
     * Create a structure that saves the index I, J and K
     * when multiplying M[i,j] and N[j,k]
     *
     * Going to do it one row at a time, then pass on the shared structure
     * which will hold the i, j and k needed to access the next row from
     * each respective matrix
     **/
    
    int running = 1;
    void *shared_memory = (void *)0;
    struct shared_matrix *shared_stuff;
    int shmid;
    pid_t pid;

    
    srand((unsigned int)getpid());
    
    shmid = shmget((key_t)1233, sizeof(struct shared_matrix), 0666 | IPC_CREAT);
    
    if (shmid == -1){
        fprintf(stderr, "shmget failed \n");
        exit(EXIT_FAILURE);
    }
    
    
    shared_memory = shmat(shmid, (void *)0, 0);
    
    if (shared_memory == (void *)-1){
        fprintf(stderr, "shmat failed \n");
        exit(EXIT_FAILURE);
    }
    
    printf("memory attached at %X\n",(int)shared_memory);
    
    //Solving FIRST ROW
    
    printf("Fork starting \n");
    
    
    pid = fork();
    
    shared_stuff = (struct shared_matrix *)shared_memory;
    //switch
    switch(pid){
       
        case -1:
            
            perror("Fork failed \n");
            exit(1);
            
        case 0:
            
            //child process - go through the given row and calculate it
            //store into matrix after
            //each row will do this, until we are done (for part 1)
            printf("This is the child \n");
            
            
            
            shared_stuff->test = 'T'; //to test
            printf("%c \n", shared_stuff->test);
            
            
            break;
        default:
            //parent
            printf("This is the parent \n");
      /**      while(running) {
                
                if(shared_stuff->written) {
                    //flag is raised, done this row
                    printf("The first row is: \n");
                    for(int i = 0; i < 4; i++){
                        //go through row
                        printf("%i" shared_stuff->i);
                        sleep( rand() % 4);
                    }
       
                    shared_stuff->written = 0 //close flag
                }
                
                
                
            } **/ //going to add this part after - will cause a crash rn
            
            
            
            
            break;
            
    }
    
    
    if (shmdt(shared_memory) == -1){
        fprintf(stderr, "shmdt failed \n");
        exit(EXIT_FAILURE);
    }
    
    if (shmctl(shmid, IPC_RMID, 0) == -1){
        fprintf(stderr, "shmctl failed \n");
        exit(EXIT_FAILURE);
    }
    
   
    
    exit(EXIT_SUCCESS);
    
    
    
}
