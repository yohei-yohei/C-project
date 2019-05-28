//Author Yohei Sato

#include <stdio.h>
#include <stdlib.h>
#include "checkfrag.h"

//The method makes the partion table
Partition* makingPartionTable(int n, int partionSize){
    Partition* partition = malloc(sizeof(Partition)*500);
    int i;
     partition[0].size = n;
     partition[0].times = 0;
     partition[0].totalCapacity = n*partionSize;
     partition[0].queSize = 0;
     partition[0].processTableSize =0;
     partition[0].queSavedProcess = malloc(sizeof(int)*500);
    for(i = 0; i <n; i++) {
        partition[i].avail = 'Y';
        partition[i].frag = -1;
        partition[i].pid = -1;

    }
   // free(partition);
    //free(partition[0].queSavedProcess);
    return partition;
}

//The method is for saving wating process ones
//int* QueForSavedProcess(int* queSavedProcess, int queSize, int processNumber){
//    queSavedProcess[queSize] = processNumber;
//
//    return queSavedProcess;
//}

//The method is making initial process table
Process* makingProcessTable() {
    Process* process = malloc(sizeof(Process)*5000); // mallocates the process variable
   // process[0].tableSize = 0;
   //free(process);
    return process;
}

//The method would add new process into the table.
Process* addingProcessTable(Process* process, Partition* partition, int sizeOfProcess, int pid) {
    //int pid = partition[0].times;
    int length = partition[0].size;
    int tableSize = partition[0].processTableSize;
    process[tableSize-1].frames = malloc(1000);
    int i;
    int j = 0;
    for(i = 0; i <=length; i++) {
        if(partition[i].pid == pid) {
            process[tableSize-1].pid = pid;
            process[tableSize-1].size = sizeOfProcess;
            process[tableSize-1].frames[j] = i;
            j++; 
        }
    }
    process[tableSize-1].framesArraySize = j-1;
    //partition[0].processTableSize++;
    //free(process[tableSize-1].frames);
    return process;

}

//This method would add new process and change partion table
int addingProcess(Partition* partition,Process* process, int partionSize, int processSize, int pid) {
    int lengeth = partition[0].size;
    int i = 0;
    //int pid = partition[0].times;
    if(processSize<=partition[0].totalCapacity) {
    while((processSize!=0)|| (i<=lengeth)) {
        if(processSize >=partionSize) {
            if(partition[i].avail == 'Y') {
                partition[i].avail = 'N';
                partition[i].frag = 0;
                processSize = processSize - partionSize;
                partition[i].pid = pid;
                partition[0].totalCapacity = partition[0].totalCapacity - partionSize;
            }
        } 
        else {
            if(partition[i].avail == 'Y' && processSize!=0) {
                partition[i].avail = 'N';
                partition[i].frag = partionSize - processSize;
                processSize = 0;
                partition[i].pid = pid;
                partition[0].totalCapacity = partition[0].totalCapacity - partionSize;
            }
        }
        i++;
        
    }
    //addingProcessTable(process,partition,processSize);
      return 1;
    //printf("it's if and partition[0].totalCapacity is %d\n", partition[0].totalCapacity);
    } else {
     // printf("processSize is");
      return 0;
    }
}

//This function can delete the process and partition based on pid
void deleteProcess(Partition* partition, Process* process, int deleteId, int sizeOfPartitions) {
    int length = partition[0].size;
    int lengthProcess = partition[0].processTableSize;
    int i, j, l=0;
    for(i=0; i<=length ; i++) {
        if(partition[i].pid == deleteId) {
            partition[i].pid = -1;
            partition[i].avail = 'Y';
            partition[i].frag = -1;
            l++; // The number of process raws became avilable again.
        }

    }
    j=0; 
    for(j=0; j<=lengthProcess; j++) {
        if(process[j].pid == deleteId) {
            int k;
            for(k=j; k<=lengthProcess;k++) {
            process[k] = process[k+1];
            }

            partition[0].processTableSize--;
            
        }
    }
    //if current empty capcity in process is quall or bigger than the first wating process, it will be stored

    partition[0].totalCapacity = partition[0].totalCapacity+sizeOfPartitions*l;
     // while(partition[0].totalCapacity>=partition[0].queSavedProcess[0]&&(partition[0].queSize!=0)) {
      //    addingProcess(partition, process, sizeOfPartitions, partition[0].queSavedProcess[0]);
      //    addingProcessTable(process, partition, partition[0].queSavedProcess[0]);
       //   int i;
        //  for(i = 0; i<=partition[0].queSize; i++){
       //   partition[0].queSavedProcess[i] = partition[0].queSavedProcess[i+1];
        //  }
        //  printf("partition[0].queSavedProcess[0] is %d", partition[0].queSavedProcess[0]);
        //  partition[0].queSize--;
        //  partition[0].times++;
        //  partition[0].processTableSize++;
  //  }
}

//This method print a Partition table
void printPartionTable(Partition* p){

    printf("---------------------------------------------------------------------------\n");
    printf("Partition table::\n");
    printf("%-20s", "Partition number");
    printf("%-15s", "Process id");
    printf("%-10s", "Frag");
    printf("%-10s", "Availability");
    printf(" ");
    printf("\n");

    int lengeth = p[0].size;
    // printf("length is %d\n", lengeth);
    int i;
    for(i = 0; i <lengeth; i++) {
        printf("%-20d", i);
        if(p[i].pid==-1) {
            printf("%-15c", 63);
        }else {
            printf("%-15d", p[i].pid);
        }
        if(p[i].frag == -1){
        printf("%-10c", 63);
        } else{
            printf("%-10d", p[i].frag);
        }
        printf("%-10c\n", p[i].avail);
    }

    
}

//This method prints a process table
void printProcessTable(Process* p, Partition* partition) {
    int tableSize = partition[0].processTableSize;
    int i;
    int j;
    printf("Printing –\n");
    printf("---------------------------------------------------------------------------\n");
    printf("Process table:\n");
    printf("%-15s", "Process id");
    printf("%-10s", "Frames");
    printf(" ");
    printf("\n");
        for(i=0;i<tableSize; i++) {
            printf("%-15d",p[i].pid);
            //printf("%-10d",p[i].size);
            int framesArraySize = p[i].framesArraySize;
            for(j=0; j<=framesArraySize; j++){
                if(j!=framesArraySize) {
                 printf("%d, ",p[i].frames[j]);
                } else {
                    printf("%d",p[i].frames[j]);
                }
            }
            printf("\n");
    }

}