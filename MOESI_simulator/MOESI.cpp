#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#include <string>

#define TOTALSIZE 16 * (1<<10)
#define CACHESIZE 32
#define BLOCKNUM (TOTALSIZE)/(CACHESIZE)
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
    int writeBack;
    Processor() {
        memset(block, 0, sizeof(block));
        memset(transfer, 0, sizeof(transfer));
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
    memset(CPU, 0, sizeof(CPU));

     
    
    return 0;
}

