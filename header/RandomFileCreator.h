#pragma once
#include <iostream>
#include <fstream>
//#include <string>
#include <sstream>
#include <iostream>
#include <dirent.h>
#include "OSFileCorrector.h"
#include "MainFileManager.h"

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



    public:
    void configFileName();
    void changeWorkplace();
    void makeRandomization(danglingBonds dba[], int dbAmount);

};

void printRandomizer(danglingBonds dba[], int dbAmount, double *X, double *Y, bool fullResult, ofstream *LOG, string filename, char canvas[maxCanvasX][maxCanvasY][maxCanvasY]);