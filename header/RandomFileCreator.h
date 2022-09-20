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
    int minX;
    int maxX;
    int minY;
    int maxY;
    int maxDBs;
    float mi;
    int divideX;
    int divideY;
    bool valid;



    public:
    void configFileName();
    void changeWorkplace();
    void makeRandomization(danglingBonds dba[]);

};

void printRandomizer(danglingBonds dba[], int dbAmount, double *X, double *Y, bool fullResult, ofstream *LOG, string filename, char canvas[maxCanvasX][maxCanvasY][maxCanvasY]);