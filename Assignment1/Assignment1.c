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



int main (){
    
    struct shared_matrix {
        
        int M[3][3]; //first matrix
        int N[3][3]; //second matrix
        int Q[3][3]; //result matrix
    
        int written; //a flag - if 0 means not written, else it has been written on
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
    
    srand((unsigned int)getpid());
    
    shmid = shmget((key_t)1234, sizeof(struct shared_matrix), 0666 | IPC_CREAT);
    
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
    
    
    
    
    
    
}
