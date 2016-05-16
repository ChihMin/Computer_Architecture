#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>

#define TOTALSIZE (16 * (1<<10))
#define BLOCKSIZE 32
#define BLOCKNUM (TOTALSIZE/BLOCKSIZE)
#define READ 0
#define WRITE 1
#define PROCNUM 4

using namespace std;

enum State {
    M = 0,
    O,
    E,
    S,
    I
};


struct Cache {
    State state;
    uint32_t tag;
    bool isValidate;
};

struct Processor {
    Cache block[BLOCKNUM];
    int transfer[PROCNUM];
    int invalidation[5];
    int writeBack;
    Processor() {
        memset(block, 0, sizeof(block));
        memset(transfer, 0, sizeof(transfer));
        memset(invalidation, 0, sizeof(invalidation));
        writeBack = 0;
    }
};

struct InputFormat {
    int time, RW, addr, pid;
    
    InputFormat() {}  
    InputFormat(int _time, int _RW, int _addr, int _pid) {
        time = _time, RW = _RW, addr = _addr, pid = _pid;
    }

    bool operator<(const InputFormat &tar) const {
        if (this->time != tar.time)
           return this->time < tar.time;
        return this->pid < tar.pid;
    }

    void print() {
        printf("%d %d %d 0x%08x\n", this->time, this->RW, this->pid, this->addr);
    }
};

Processor CPU[4];

void printResult();

bool isValidBlock(int tag, const Cache *cache) {
    // Check if current block has been used
    if (!cache->isValidate)
        return false;

    // Check whether current block is same or not
    if (cache->tag != tag)
        return false;
    
    // tag point to same block 
    return true;
}

bool isMiss(int tag, const Cache * cache) {
    // The tage is different from cuurent block
    return cache->isValidate &&
                cache->tag != tag;
}

void read(int blockNum, int tag, int pid) {
    Processor * currentCPU = &CPU[pid];
    Cache *block = &CPU[pid].block[blockNum];
   
    /* If it happends read miss, */ 
    if (isMiss(tag, block)) {
        // This block will be swapped 
        State state = block->state;
        block->isValidate = false; 
        if (state == M || state == O) {
            // If current block is MODIFIED or OWN state,
            // then write back to memory
            currentCPU->writeBack++;
        }
    }

    /* Here is read hit */
    bool findOtherBlock = false;
    for (int i = 0; i < PROCNUM; ++i) {
        if (i == pid) 
            continue;
        
        Processor * otherCPU = &CPU[i];
        Cache *otherBlock = &otherCPU->block[blockNum];
        if (!isValidBlock(tag, otherBlock)) {
            // If there's no block in cache
            // or tag value is not the same,
            // then it will continue to find next CPU
            continue;
        }
        
        State state = otherBlock->state;
        // If current block is invalid(not used or just swapped)
        // then we discuss two cases:
        // (1) If other block is MODIFIED, then trans it to OWN
        // (2) If other block is OWN, just transfer data
        if (!block->isValidate || block->state == I) {
            if (state == M || state == O) {
                otherBlock->state = O;   
                otherCPU->transfer[pid]++;   
            }
        }
        // If we can find other block,
        // then we set current state as SHARED.
        // or we set it as EXCLUSIVE
        findOtherBlock = true;
        if (otherBlock->state == E)
            otherBlock->state = S;  
    }
    
    if (!findOtherBlock) 
        block->state = E;
    else
        block->state = S;
    block->tag = tag;
    block->isValidate = true;
}

void write(int blockNum, int tag, int pid) {
    Processor * currentCPU = &CPU[pid];
    Cache *block = &CPU[pid].block[blockNum]; 
    
    /* Here is write miss */
    if (isMiss(tag, block)) {
        // This block will be swapped 
        State state = block->state;
        block->isValidate = false; 
        if (state == M || state == O) {
            // If current block is MODIFIED or OWN,
            // then write back to memory
            currentCPU->writeBack++;
        }
    }


    /* Here is write hit */
    for (int i = 0; i < PROCNUM; ++i) {
        if (i == pid)   
            continue;
        
        Processor * otherCPU = &CPU[i];
        Cache *otherBlock = &otherCPU->block[blockNum];
        if (!isValidBlock(tag, otherBlock)) {
            // If there's no block in cache
            // or tag value is not the same,
            // then it will continue to find next CPU
            continue;
        }
        
        State state = otherBlock->state;
        // If other block is in MODIFIED or OWN STATE
        // and current block is first access or just swapped, 
        // then transfer data to current CPU.
        if (!block->isValidate || block->state == I) {
            if (state == M || state == O) 
                otherCPU->transfer[pid]++;
        }
        
        // If block is not on INVALID state 
        if (state != I) {
            otherBlock->state = I;  //Set other block INVALID
            otherCPU->invalidation[state]++; // count invalidation
        }
    }
    
    block->isValidate = true;
    block->state = M;
    block->tag = tag;
}


void run(const vector<InputFormat>&inputData) {
    for (auto inData: inputData) {
        int time = inData.time;
        int RW = inData.RW;
        uint32_t addr = (uint32_t)inData.addr;
        int pid = inData.pid;
        uint32_t tag = addr / BLOCKNUM;
        uint32_t blockIndex = addr % BLOCKNUM;   
        /* Above is directed map from memory to cache */
        
        switch(RW) {
        case READ:
            read(blockIndex, tag, pid);
            break;

        case WRITE:
            write(blockIndex, tag, pid);
            break;
        }
    }

    // Write back all the dirty lines
    for (int i = 0; i < PROCNUM; ++i) {
        for (int j = 0; j < BLOCKNUM; ++j) {
            State state = CPU[i].block[j].state;
            if (!CPU[i].block[j].isValidate) 
                continue;

            if (state == M || state == O) {
                // If state is MODIFIED or OWN,
                // then writeBack to memory 'cause
                // they are dirty blocks.
                CPU[i].writeBack++;
            }
        }
    }
}

int main(int argc, char **argv) {
    
    if (argc < 2) {
        printf("Please enter correct format: ./MOESI INPUT_FILE_PATH\n");
        return -1;
    }
    
    string inputPath = argv[1]; 
    string inputName[4];
    inputName[0] = inputPath + "/p0.tr";
    inputName[1] = inputPath + "/p1.tr";
    inputName[2] = inputPath + "/p2.tr";
    inputName[3] = inputPath + "/p3.tr";
    
    uint32_t time, RW, addr;
    vector <InputFormat>  inputData;
    inputData.clear(); 
    for (int i = 0; i < PROCNUM; ++i) { 
        FILE *R = fopen(inputName[i].c_str(), "r");
        while (~fscanf(R, "%d %d %x", &time, &RW, &addr)) {
            inputData.push_back(InputFormat(time, RW, addr, i));
        }
    }
    
    /* First sort timestamp, secondary sort processor ID */ 
    sort(inputData.begin(), inputData.end());
    
    /* Start Simulation */ 
    run(inputData);

    /* Output result */
    printResult();
    
    return 0;
}

void printResult() {
    for (int i = 0; i < PROCNUM; ++i) {
        printf("P%d cache transfers: ", i);
        for (int j = 0; j < PROCNUM; ++j)
            printf("%7d", CPU[i].transfer[j]);
        printf("\n");
    }
    
    printf("\n");
    
    for (int i = 0; i < PROCNUM; ++i) {
        int *inv = CPU[i].invalidation;
        printf("P%d Invalidation: m=%d o=%d e=%d s=%d\n", 
                    i, inv[0], inv[1], inv[2], inv[3]);
    }
    printf("\n");
    
    for (int i = 0; i < PROCNUM; ++i) {
        printf("P%d WriteBack Number: %d\n", i, CPU[i].writeBack);
    } 
    printf("\n");

    for (int i = 0; i < PROCNUM; ++i) {
        Cache *block = CPU[i].block;
        int statistic[6];
        memset(statistic, 0, sizeof(statistic));
        for (int j = 0; j < BLOCKNUM; ++j) {
            if (block[j].isValidate){
                State state = block[j].state;
                statistic[state]++;
            }
        }
         
        int *inv = statistic;
        printf("P%d statistic: M=%d O=%d E=%d S=%d I=%d\n", 
                    i, inv[0], inv[1], inv[2], inv[3], inv[4]);
    }
    printf("\n");
}
