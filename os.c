#include<stdlib.h>
#include<time.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/wait.h>
#include<stdio.h>

#define MIN_PID 100
#define MAX_PID 1000
#define NO_OF_P 100    

int pid[MAX_PID-MIN_PID]={0};
 
int allocate_pid()
{
int i=0;
int state=1;
while(i<(MAX_PID-MIN_PID))
{
if(pid[i]==0)
{
pid[i]=1;
state=0;
break;
}
i++;
}
if(state==1)
{
return -1;
}
else
{
return i;
}
}
void release_pid(int id){
    pid[id]=0;
}
void *map(void *var){
    int tid =  *(( int* )var);
    
    int id = allocate_pid();


    if(id==-1){
        printf("SORRY NO PID IS CAN BE ALLOCATED  NOW");
    }
     
     
    else{
        printf("Thread [%3d] with  PID [%3d] \n",tid,id+MIN_PID);     
        int stime=1+rand()%30;
        sleep(stime); //here you can check the output of the program by commenting the sleep and check the output
        printf("Thread [%3d] PID [%3d] Releasing this after  %d seconds\n",tid,id+MIN_PID,stime);
        release_pid(id);
    }
    pthread_exit(NULL);
}

int main(){
    
    pthread_t process[NO_OF_P];
    int i=0;
    
    srand(time(NULL));
    for(i=0; i<100; i++){
        if(pthread_create(&process[i],NULL,map,(void*)&i))
            return -1*printf("This thread Creation  %d cannot possible!!!\n",i);    
    }

    for(i=0; i<100; i++)
        pthread_join(process[i],NULL);
    wait(NULL); //you can also comment the wait and check the output
    return printf("\n****************COMPLETED***************\n");
}
