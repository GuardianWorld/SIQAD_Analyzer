#include <iostream>
#include "menu.h"
#include "MainFileManager.h"
#include "OSFileCorrector.h"

int main()
{
	// Variable Creation //
	int buffer = 0;
	int x = -1;
	string miValue;
	bool fullResult = false;
	int permsLoaded = 0;
	int perms = 0;
	int dbAmount = 0;
	int dbd[MaxDBS];
	// String Creation //
	string fileName;
	string bufferStart;
	string bufferEnd;
	string perName;
	// Other Creation //
	danglingBonds *dba = new danglingBonds[MaxDBS];

	for (int y = 0; y < MaxDBS; y++)
	{
		dbd[y] = 0;
	}

	while (x != 0)
	{
		menu(fullResult);
		cout << "> Option: \n>> ";
		cin >> x;

		switch(x)
		{
			case -1:
				dbAmount = readSim(("./simulationFiles/AND.xml"), dba, bufferStart, bufferEnd);
				permsLoaded = readList("./op/AND.txt", dba, dbAmount, dbd);
				fullResult = true;
				//readResultFile("./results/AND1.xml", dba, dbAmount, fullResult);

			break;
			case 1:
				miValue = conversionText();
				if(!noConversion)
				{
					buffer = convertSQDtoSim(miValue);
				}
			break;

			case 2:
				fileName = loadSimText();
				dbAmount = readSim(fileName, dba, bufferStart, bufferEnd);
			//dbAmount = readSim((dir_simulation + loadSimText() + ".xml"), dba, bufferStart, bufferEnd);
			break;

			case 3:
				if (dbAmount == 0) { cout << "Invalid, load XML first. \n"; break; }
				fileName = loadPerturberText();
				permsLoaded = readList(fileName, dba, dbAmount, dbd);
			break;

			case 4:
				perName = loadPermutationText();
				if (perName.compare("0") != 0)
				{
					createPermutations(dba, bufferStart, bufferEnd, dbAmount, perName);
				}
			break;

			case 5:
				annealCallText();
				callAnneal(dbAmount);
			break;

			case 6:
				if (dbAmount == 0 || permsLoaded == 0)
				{
					cout << "> Error! Please verify if a Problem File and a Perturber File are loaded in memory!\n";
				}
				else
				{
					fileName = singleResultsText();
					readResultFile(fileName, dba, dbAmount, fullResult);
				}
			break;

			case 7:
				if (dbAmount == 0 || permsLoaded == 0)
				{
						cout << "> Error! Please verify if a Problem File and a Perturber File are loaded in memory!\n";
				}
				else
				{
					if(allResultsText())
					{
						printFullResult(dba, dbAmount, fullResult);
					}
				}
			break;
			case 8:
				{
					fullResult = !fullResult;
				}
			break;
			case 9:
				for (int i = 0; i < dbAmount; i++)
				{
				cout << "> " << dba[i].getN() << ' ' << dba[i].getM() << ' ' << dba[i].getL() << ' ' << dba[i].getX() << ' ' << dba[i].getY() << ' ' << dba[i].getActive() << ' ' << dba[i].getDisturber() << ' ' << dba[i].getObserved() << ' ' << dba[i].getState() << '\n';
				}
			break;
		}
	}
}