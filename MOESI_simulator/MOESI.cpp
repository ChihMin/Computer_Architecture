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
    O = 0,
    M,
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
};

Processor CPU[4];

bool isValidBlock(int tag, const Cache *cache) {
    if (!cache->isValidate)
        return false;

    if (cache->tag != tag)
        return false;
    
    return true;
}

bool isWriteMiss(int tag, const Cache * cache) {
    return cache->isValidate &&
                cache->tag != tag;
}

void write(int blockNum, int tag, int pid) {
    Processor * currentCPU = &CPU[pid];
    Cache *block = &CPU[pid].block[blockNum]; 
    if (!block->isValidate) 
        block->isValidate = true;
        
    bool findOwnBlock = false;

    /* Here is write miss */
    if (isWriteMiss(tag, block)) {
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
        if(state != I) {
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
    
    sort(inputData.begin(), inputData.end());
    //memset(CPU, 0, sizeof(CPU));

     
    
    return 0;
}

