#pragma once
#include <iostream>
#include <fstream>
//#include <string>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <dirent.h>
#include "OSFileCorrector.h"
#include "MainFileManager.h"
#include <filesystem>

class configurationFileRFC{
    private:
    string workingFileName;
    float mi;
    int minN;
    int maxN;
    int latticeMin;
    int minM;
    int maxM;
    int latticeMax;
    int maxDBs;
    int divideX;
    int divideY;
    bool valid;
    int interactions;
    int maxBatches;



    public:
    void configFileName();
    void changeWorkplace();
    void makeRandomization(danglingBonds dba[], int dbAmount, int* randomCalls, int seed, string bs, string be, string fileName);

    int getBatches(){
        return maxBatches;
    }
    int getInteractions(){
        return interactions;
    }
};

void printRandomizer(danglingBonds dba[], int dbAmount, double *X, double *Y, bool fullResult, ofstream *LOG, string filename, char canvas[maxCanvasX][maxCanvasY][maxCanvasY]);
int RandomBatch(danglingBonds dba[], configurationFileRFC rfc, string filenamePert, int seed, int *randomCalls);