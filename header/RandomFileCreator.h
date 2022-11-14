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
//#include <filesystem>

		/**
		 * Main class for the RandomFileCreator, it saves information about the file names, the wanted mi, the minimum values, the workable area, the max dbs, the division of area and all the interactions and batches wanted.
		 * 
		 */

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
    int currentlyRandomCall;



    public:
    
    	/**
		* @brief Opens the mainConfig.txt file, and gets the file that will be worked on during the execution of the program.
		* 
		*/
    void configFileName();
    
     	/**
		* @brief Opens the workingFileName, obtained in the configFileName() function, and obtains the necessary information. It places said information inside a class.
		* 
		*/
    void changeWorkplace();
    
      	/**
		* @brief Makes random files, using the configuration obtained from the configurationFile class.
		* 
		* @param dba the danglingBound array having the loaded file;
		* @param dbAmount the amount of DBs currently in the system;
		* @param randomCalls the POINTER to the randomCalls existent on the system. (USE CURRENTLY RANDOM CALL VARIABLE PLEASE);
		* @param seed only used to be saved on the file name. Seed used for the srand call;
		* @param bs Buffer Start variable, used to save on the file.
		* @param be Buffer End variable, used to save on the file.
		* @param fileName currently used filename, is used to save things as well;
		*/
    void makeRandomization(danglingBonds dba[], int dbAmount, int* randomCalls, int seed, string bs, string be, string fileName);
    
        /**
		* @brief Just prints information pertaining to this class.
		* 
		*/
    void printInfo();
    
    int getBatches(){
        return maxBatches;
    }
    int getInteractions(){
        return interactions;
    }
    
};

void printRandomizer(danglingBonds dba[], int dbAmount, double *X, double *Y, bool fullResult, ofstream *LOG, string filename, char canvas[maxCanvasX][maxCanvasY][maxCanvasY]);

    /**
		* @brief Makes a Batch of randomFiles, using all the variables. Is the main usage of this class.
		* 
		*/
int RandomBatch(danglingBonds dba[], configurationFileRFC rfc, string filenamePert, int seed, int *randomCalls);

bool checkBTables(bool mainTable[], bool checkTable[], int size);
void printRandomAnnealFullResults(danglingBonds dba[], int dbAmount);
void organizeResults(string fileName, danglingBonds dba[], int dbAmount);
void checkRandomAnnealFullResults(danglingBonds dba[], int dbAmount);