//Author Yohei Sato

//The structure for partition table
typedef struct partition_tag{
    int pid;
    int frag;  
    char avail; //avaievility Y is avilable, N is not avilable
    int size;  //The Partion table size
    int times;  //how many times the user added process
    int totalCapacity; // size of remaining capacity of Partition  table
    int totalAmount;
    int processTableSize; //size of process table
    int* queSavedProcess; //The que for saving Process which can't be saved in the current partition
    int queSize;
    
}Partition;


//The structure for process table
typedef struct process_tag{
    int pid;
    int size;
    int framesArraySize; //size of frames array
    int* frames;
    
}Process;

//The que for saving wating process for the extra credit.
typedef struct queue_tag {
  int pid;
  int size;
  struct queue_tag * next;
} QueueNode;

// typedef struct queSaved_tag{
//     int 
//     int
// }

Partition* makingPartionTable(int n, int partionSize);
Process* makingProcessTable();
Process* addingProcessTable(Process* process, Partition* partition, int sizeOfProcess, int pid);
void printPartionTable(Partition* partition);
void printProcessTable(Process* p, Partition* partition);
int addingProcess(Partition* partition,Process* process, int partionSize, int processSize, int pid);
void deleteProcess(Partition* partition, Process* process, int deleteId, int sizeOfPartitions);
int* QueForSavedProcess(int* queSavedProcess, int queSize, int processNumber);