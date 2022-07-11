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
	bool resultOutput = false;
	int permsLoaded = 0;
	int perms = 0;
	int dbAmount = 0;
	int dbd[MaxDBS];
	// String Creation //
	string fileName;
	string bufferStart;
	string bufferEnd;
	string SimFolder = dir_anneal;
	// Other Creation //
	danglingBonds *dba = new danglingBonds[MaxDBS];

	for (int y = 0; y < MaxDBS; y++)
	{
		dbd[y] = 0;
	}

	while (x != 0)
	{
		menu(resultOutput);
		cout << "> Option: \n>> ";
		cin >> x;

		switch(x)
		{
			case 1:
				miValue = conversionText();
				buffer = convertSQDtoSim(miValue);
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
			
			break;

			case 5:

			break;

			case 6:
			
			break;

			case 7:
			
			break;
		}
		/*switch (x)
		{
		case 2: // Load Perturbers;
			if (dbAmount == 0) { cout << "Invalid, load XML first. \n"; break; }
			cout << "> Please type the file name\n> Attention: The .txt will be automatically added!!\n> Addendum: The file should be on the folder op, check reference file.\n >> ";
			cin >> fileName;
			fileName = "op\\" + fileName + ".txt";
			permsLoaded = readList(fileName, dba, dbAmount, dbd);
		break;
		case 3:
			cout << "> Are you sure you wanna execute the program?\n> This will make several file variations on the folder annealInput, make sure its empty!\n";
			cout << "> type 1 to run, type 0 to return: ";
			cin >> x;
			if (x == 1)
			{
				createPermutations(dba, bufferStart, bufferEnd, dbAmount);
				//execute;
			}
		break;
		case 4:
			cout << "> Calling Anneal! Check the results in the Results folder after completion!\n";
			cout << "> Please type the amount of permutations that you want to test (Files should be in Output):\n >> ";
			cin >> perms;
			callAnneal(SimFolder, dbAmount, perms);
		break;
		case 5: 
			if (dbAmount == 0 || permsLoaded == 0)
			{
				cout << "> Error! Please verify if a Problem File and a Perturber File are loaded in memory!\n";
			}
			else
			{
				cout << "> Please type the file name\n> Attention: The file must exist in the results folder, must be a result file\n >> ";
				cin >> fileName;
				fileName = "results\\" + fileName + ".xml";
				readResultFile(fileName, dba, dbAmount);
				printResult(dba, dbAmount);
			}
		break;
		case 6:
			if (dbAmount == 0 || permsLoaded == 0)
			{
				cout << "> Error! Please verify if a Problem File and a Perturber File are loaded in memory!\n";
			}
			else
			{
				cout << "> Are you sure you wanna execute the program?\n> This will read all the results from the results folder, make sure it's only from the current problem!\n";
				cout << "> type the number of files to run, type 0 to return: ";
				cin >> perms;
				if (x > 0)
				{

					//execute;
				}
			}
		break;
		case 8:
			for (int i = 0; i < dbAmount; i++)
			{
				cout << "> " << dba[i].getN() << ' ' << dba[i].getM() << ' ' << dba[i].getL() << ' ' << dba[i].getX() << ' ' << dba[i].getY() << ' ' << dba[i].getActive() << ' ' << dba[i].getDisturber() << ' ' << dba[i].getObserved() << ' ' << dba[i].getState() << '\n';
			}
		break;
		default:
			continue;
		break;
		}*/

		/*for (int i = 0; i < dbAmount; i++)
		{
			cout << dba[i].getN() << ' ' << dba[i].getM() << ' ' << dba[i].getL() << ' ' << dba[i].getX() << ' ' << dba[i].getY() << ' ' << dba[i].getActive() << ' ' << dba[i].getDisturber() << ' ' << dba[i].getObserved() << ' ' << dba[i].getState() << '\n';
		}*/
		//cout << bufferStart << '\n' << bufferEnd;
	}
}