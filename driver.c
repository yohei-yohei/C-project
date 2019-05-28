//I made the que which can save wating processes for the extra credit
//The process can't go to the partition table because it's full, they will be saved in the que.
//After deliting tables and then if ther is enough space, the wating processes going to the table.

//We can run program "make" then "./pr1.out" these command allow you to run the program

//Author Yohei Sato

#include <stdio.h>
#include <stdlib.h>
#include "checkfrag.h"
//This is the main method for running the program
int main(void) {
    int numOfPartitions = 0;
    int sizeOfPartitions = 0;
    int sizeOfProcess = 0;
    int  deleteId = 0;
    int choice = 0;

    printf("Enter the number of partitions: ");
    scanf("%d", &numOfPartitions);
    printf("Enter the size of each partition:" );
    scanf("%d", &sizeOfPartitions);
    Partition* partion =  makingPartionTable(numOfPartitions, sizeOfPartitions);
    Process* process = makingProcessTable();
    QueueNode* queue=NULL; //The queue is saving wating process which can't be going to the current partion
    while(choice!=4) {
    printf("Do you want to:\n");
    printf("Add a process? Enter 1\n");
    printf("Delete a process? Enter 2\n");
    printf("Print values? Enter 3\n");
    printf("Quit? Enter 4\n");
    scanf("%d", &choice);
      


  //Switch statement for users choises
   switch(choice) {
      case 1 :
         printf("Adding - enter process size:");
         scanf("%d", &sizeOfProcess);
         partion[0].times++;
        
         if(addingProcess(partion, process,sizeOfPartitions, sizeOfProcess, partion[0].times))
         {
            partion[0].processTableSize++;//if process is adding to the table size is increasing
            addingProcessTable(process, partion, sizeOfProcess, partion[0].times);
         }
         else
         {
           // add it to the queue if there is no enough avilable spaces.
           QueueNode* newNode=malloc(sizeof(QueueNode));
           newNode->pid=partion[0].times;
           newNode->size=sizeOfProcess;
           newNode->next=queue;
           queue=newNode;
         }
         break;
      case 2 :
         printf("Deleting - enter process id: ");
         scanf("%d", &deleteId);
         deleteProcess(partion, process, deleteId, sizeOfPartitions);
         QueueNode* node=queue; // These node and prev are making arraylink for the que
         QueueNode* prev=NULL; 
         while(node!=NULL)
         {
           //If the table current avilable sizes are bigger than the process in the que
           if(addingProcess(partion, process, sizeOfPartitions, node->size, node->pid))
           {
             // delete it from the queue
             partion[0].processTableSize++;
             addingProcessTable(process, partion, sizeOfProcess, node->pid);
             if(prev!=NULL)
             {
                 prev->next=node->next; 
                 
             }
             else
             {
               queue=node->next;
               
             }
           }
           else
           {
           prev=node;
           }
           node=node->next;
         }
         break;
      case 3 :
        printProcessTable(process, partion);
        printPartionTable(partion);
         break;
      case 4 :
         break;
      default :
         printf("\n" );
    }
    }
    

    // scanf("%d", &sizeOfPartitions);
    
   
    
    //printPartionTable(part);
    
    
    


}
