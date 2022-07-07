#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <dirent.h>
#include "OSFileCorrector.h"

#define OSwindows 1
#define OSlinux 2
#define OSapple 3

#ifdef _WIN32
#include <Windows.h>
#define OS 1
//#include <WinBase.h>
//#include <winuser.h>
#elif __linux__
#include <cstring>
#include <cstdio>
#include <algorithm>
#define OS 2

#elif __APPLE__

#endif


using namespace std;

#define MaxDBS 300
#define INFINITY 9999999;

typedef struct elecDist {
	double energy = INFINITY;
	int count = 0;
	bool valid = 0;
	int state_count = 0;
	char coordinates[MaxDBS] = { 0 };
}elecDist;

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

		void findDBDot(string str, int mode)
		{
			int x = 0, y = 0;
			char aux[20] = { 0 };
			bool found = false;

			isActive = false;
			disturber = false;
			observed = false;

			for (std::string::size_type i = 0; i < str.size(); ++i)
			{
				if (str[i] == 34)
				{
					found = !found;
					x = 0;
					if (aux[0] != 0)
					{
						if (mode == 0)
						{
							if (y == 0)		 { n = atoi(aux); }
							else if (y == 1) { m = atoi(aux); }
							else if (y == 2) { l = atoi(aux); }
						}
						else
						{
							if (y == 0)		 { X = atof(aux); }
							else if (y == 1) { Y = atof(aux); }
						}
						y++;
					}
					memset(aux, 0, sizeof(aux));
				}
				else if (found)
				{
					aux[x] = str[i];
					x++;
				}
			}
		}
		int getN()	 { return n; }
		int getM()	 { return m; }
		int getL()	 { return l; }
		double getX() { return X; }
		double getY() { return Y; }


		int compare(int iN, int iM, int iL)
		{
			if (iN == n && iM == m && iL == l) return 1; 
			return 0;
		}

		void setActive() { isActive = !isActive; }
		int getActive() 
		{ 
			if (isActive) return 1;
			return 0;
		}
		void setDisturber() { disturber = !disturber; }
		int getDisturber() 
		{
			if (disturber) return 1;
			return 0;
		}

		void setObserver() { observed = !observed; }
		int getObserved() 
		{ 
			if (observed) return 1;
			return 0; 
		}

		void setState() { negative = !negative; }
		int getState()
		{
			if (negative) return 1;
			return 0;
		}
		void resetState()
		{
			negative = false;
		}

		void initialize()
		{
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

int convertSQDtoSim(float miValue);

int readSim(string fileName, danglingBonds dba[MaxDBS], string& bufferStart, string& bufferEnd);
int readList(string fileName, danglingBonds dba[], int dbAmount, int* disturberArray);
int createPermutations(danglingBonds dba[], string first, string second, int dbAmount);
void Combi(string a[], int reqLen, int s, int currLen, bool check[], int l, string first, string second, int* next);
void removeSpaces(string &str);

void readResultFile(string fileName, danglingBonds dba[], int dbAmount);
void printResult(danglingBonds dba[], int dbAmount);
void callAnneal(string sFolder, int dbAmount, int perms);
void printAllResults(danglingBonds dba[], int dbAmount, int perms);