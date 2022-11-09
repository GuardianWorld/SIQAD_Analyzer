#pragma once
#include <iostream>
#include <fstream>
//#include <string>
#include <sstream>
#include <dirent.h>
#include "OSFileCorrector.h"

#define OSwindows 1
#define OSlinux 2
#define OSapple 3

#ifdef _WIN32
#include <Windows.h>
#define OS 1
#include <string>
//#include <WinBase.h>
//#include <winuser.h>
#elif __linux__
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cstdlib>
#define OS 2

#endif


//using namespace std;

#define doubleQuotes '\"'

#define MaxDBS 300
#define ForbiddenInfinity -0.99999
#define INFINITY 9999999;

#define maxCanvasX 30
#define maxCanvasY 95
#define halfCanvasX (maxCanvasX/2)
#define halfCanvasY (maxCanvasY/2)
#define maxCanvasLatice 2


typedef struct elecDist {
	double energy = INFINITY;
	int count = 0;
	bool valid = 0;
	int state_count = 0;
	char coordinates[MaxDBS] = { 0 };
}elecDist;

/** Main class for Dangling Bonds
 * Stores the N M L and X Y positions of a dangling bond, as well as some values.
 * Has the main GET and SET functions, as well as the main FINDDBDOT function.
 * 
 */
class danglingBonds {
	private:
		int n = 0;
		int m = 0;
		int l = 0;
		double X = 0;
		double Y = 0;
		bool isActive = true;
		bool disturber = false;
		bool observed = false;
		bool negative = false;
	public:
		string dotBuffer;
		danglingBonds(){
			n = 0;
			m = 0;
			l = 0;
			X = 0;
			Y = 0;
			isActive = false;
			disturber = false;
			observed = false;
			negative = false;
			dotBuffer.clear();
		}
		/**
		 * @brief Reads a line, acquired from another function, and assigns values to a DB. Should not be called by itself.
		 * 
		 * @param str line obtained from another function. 
		 * @param mode Assigned 0 for when finding N M L positions from a file, and 1 for assigning the X Y position from a formula.
		 */
		void findDBDot(string str, int mode);
	
		/**
		 * @brief Makes a String with the default and necessary information to save in the SQD simulation file; Uses the mnl and xy positions inside the class to generate the correct inputs.
		 * 
		 * @return Return a string containing the necessary information to be used and placed inside the file.
		 */
		string findDotBuffer();

		int getN()	  { return n; }
		int getM()	  { return m; }
		int getL()	  { return l; }
		double getX() { return X; }
		double getY() { return Y; }

		 /**
		 * @brief Verifies if the N,M and L position inside the class matches the iN,iM,iL inputs that it receives.
		 * 
		 * @return Returns true if it matches, returns false if it does not match.
		 */
		int compare(int iN, int iM, int iL)
		{
			if (iN == n && iM == m && iL == l) return 1; 
			return 0;
		}

		void enableActive() { isActive = true; }
		void disableActive(){ isActive = false;}
		bool getActive()	{ return isActive;	}
		void setDisturber() { disturber = !disturber; }
		bool getDisturber() { return disturber;		  }

		void setObserver() { observed = !observed; }
		bool getObserved() { return observed;      }

		void setState()  { negative = !negative; }
		bool getState()	 { return negative;		}
		void resetState(){	negative = false;	}
	
		/**
		 * @brief Sets manually the N,M,L. Should not be used by hand most of the times, since it gets the INT value instead of the string from the file. Has uses in the Randomizer section or manually setting things to help create DB circuits. 
		 * 
		 * @param N receives a value of N;
		 * @param M receives a value of M;
		 * @param L receives a value of L;
		 */
		void setDB(int N, int M, int L){
			cleanDBs();
			n = N;
			m = M;
			l = L;
			findXY();
			isActive = true;
		}
	
		/**
		 * @brief Finds the X and Y position of DBs. Its used when inputting DBs values manually only.
		 * 
		 */
		void findXY();

	
		/**
		 * @brief Resets all the DBs to a clean state. (Like a initialization, but places zero in all values).
		 * 
		 */
		void cleanDBs(){
			n = 0;
			m = 0;
			l = 0;
			X = 0;
			Y = 0;
			isActive = false;
			disturber = false;
			observed = false;
			negative = false;
			dotBuffer.clear();
		}
};

/**
* @brief Converts a SQD save file to a XML Simulation file, changing the value of Mi if wanted;
* 
* @param miValue Receives a string containing a paramter to mi. if its NULL it sets mi to -0.25, otherwise sets the value to the wanted one;
*
* @return Returns 0 if the reading of a folder containing files was successfull, or returns -1 if a folder was not read successfully.
*/
int convertSQDtoSim(string miValue);

int readSim(string fileName, danglingBonds dba[MaxDBS], string& bufferStart, string& bufferEnd);
int readList(string fileName, danglingBonds dba[], int dbAmount, int* disturberArray);
int createPermutations(danglingBonds dba[], string first, string second, int dbAmount, string fileName, string outputPath);
void Combi(string a[], int reqLen, int s, int currLen, bool check[], int l, string first, string second, int* next, string fileName, string outputPath);
void removeSpaces(string &str);

void readResultFileHelper(danglingBonds dba[], int dbAmount,string fileName, bool situation[]);
void readResultFile(string fileName, danglingBonds dba[], int dbAmount, bool fullResult, ofstream *LOG);
void printResult(danglingBonds dba[], int dbAmount, double *X, double *Y, bool fullResult, ofstream *LOG, string filename);
void callAnneal (int dbAmount, bool supressAnneal, string dirAnneal, string outAnneal);
void printFullResult(danglingBonds dba[], int dbAmount, bool fullResult);
void printDBResult(danglingBonds dba[], int dbAmount);
int saveFile(danglingBonds dba[], int dbAmountExtra, int* randomCalls, int seed, string first, string second, string fileName);