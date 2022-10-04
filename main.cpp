#include <iostream>
#include "./header/menu.h"
#include "./header/MainFileManager.h"
#include "./header/OSFileCorrector.h"
#include "./header/RandomFileCreator.h"

int main()
{
	// Variable Creation //
	int buffer = 0;
	int x = -1;
	int permsLoaded = 0;
	int perms = 0;
	int dbAmount = 0;
	int dbd[MaxDBS];
	int randomCalls = 0;

	bool fullResult = false;
	bool advancedOptions = true;
	bool supressAnneal = false;
	// String Creation //
	string fileName;
	string bufferStart;
	string bufferEnd;
	string perName;
	string miValue;
	// Other Creation //
	danglingBonds *dba = new danglingBonds[MaxDBS];
	
	
	configurationFileRFC rfc;
	rfc.configFileName();
	rfc.changeWorkplace();

	for (int y = 0; y < MaxDBS; y++)
	{
		dbd[y] = 0;
	}

	while (x != 0)
	{
		menu(fullResult, advancedOptions, supressAnneal);
		cout << "> Option: \n>> ";
		cin >> x;

		switch(x)
		{
			case -2: //Supresses the SimAnneal prints with >Nul
				supressAnneal = !supressAnneal;
			break;

			case -1: //Deactivates/Activates de Advanced Menu.
				advancedOptions = !advancedOptions;
			break;

			case 1: //Converts SQD files in the SQD Folder to Simulation Files
				miValue = conversionText();											//Gets the wanted value of MI, default is 0.25.
				if(miValue != noConversion){
					buffer = convertSQDtoSim(miValue);
				}
			break;

			case 2: //Loads into memory the wanted Simulation file
				fileName = loadSimText();											//Gets the filename to load the wanted file;
				dbAmount = readSim(fileName, dba, bufferStart, bufferEnd);			//Reads the Simulation file, and inserts the corresponding DBs in memory.
			//dbAmount = readSim((dir_simulation + loadSimText() + ".xml"), dba, bufferStart, bufferEnd);
			break;

			case 3: //Loads a list of perturbers to be inserted into the loaded simulation file in memory. Sets its variables.
				if (dbAmount == 0) { 
					cout << "Invalid, load XML first. \n"; 
					break; 
				} 
				fileName = loadPerturberText();										//Gets the filename to load the wanted file;
				permsLoaded = readList(fileName, dba, dbAmount, dbd);				//Read the list of perturbers and set in memory.
			break;

			case 4:	// Makes permutations with the loaded file.
				perName = loadPermutationText();
				if (perName.compare("0") != 0){
					createPermutations(dba, bufferStart, bufferEnd, dbAmount, perName);
				}
			break;

			case 5: // Call the SimAnneal plugin to simulate all files.
				annealCallText();
				callAnneal(dbAmount, supressAnneal);
			break;

			case 6:	// Read a single result file.
				if (dbAmount == 0 || permsLoaded == 0){
					cout << "> Error! Please verify if a Problem File and a Perturber File are loaded in memory!\n";
				}
				else{
					fileName = singleResultsText();
					readResultFile(fileName, dba, dbAmount, fullResult, NULL);
				}
			break;

			case 7: // Read the entire result folder.
				if (dbAmount == 0 || permsLoaded == 0){
						cout << "> Error! Please verify if a Problem File and a Perturber File are loaded in memory!\n";
				}
				else
				{
					if(allResultsText()){
						printFullResult(dba, dbAmount, fullResult);
					}
				}
			break;

			case 8:	// Toggles the Full Result option.	
				fullResult = !fullResult;		
			break;

			case 9: // Prints the DB situation.
				for (int i = 0; i < dbAmount; i++){ 
				cout << "> " << dba[i].getN() << ' ' << dba[i].getM() << ' ' << dba[i].getL() << ' ' << dba[i].getX() << ' ' << dba[i].getY() << ' ' << dba[i].getActive() << ' ' << dba[i].getDisturber() << ' ' << dba[i].getObserved() << ' ' << dba[i].getState() << '\n';
				}
			break;

			case 11: //Batch for a single file, currently WIP.
				std::cout << "> Digit the filename for Batch! Make sure the results folder is empty!\n >> ";
				std::cin >> fileName;
				dbAmount = readSim((dir_simulation + fileName + ".xml"), dba, bufferStart, bufferEnd);
				if (dbAmount == 0) { cout << "Invalid, load XML first. \n"; break; }
				permsLoaded = readList((dir_operations + fileName + ".txt") , dba, dbAmount, dbd);
				if (dbAmount == 0 || permsLoaded == 0){	cout << "> Error! Please verify if a Problem File and a Perturber File are loaded in memory!\n"; break;	}
				printFullResult(dba, dbAmount, fullResult);
			break;
			case 12: //Batch to multiple files, currently not in progress ;-;
				
			break;
			case 13: //Configurate the Randomizer, currently WIP.
				rfc.changeWorkplace();
				srand(42);
			break;
			case 14: //Starts the Randomization, currently WIP.
				fileName = "./simulationFiles/Hexagon31.xml";
				dbAmount = readSim(fileName, dba, bufferStart, bufferEnd);
				rfc.makeRandomization(dba, dbAmount, &randomCalls);
				randomCalls = 0;
			break;
			case 15: //Set the RandomCalls for Randomization;
				std::cout << "> Digit how many random calls do you want to initiate.\n >> ";
				std::cin >> randomCalls;
			break;
		}
	}
}