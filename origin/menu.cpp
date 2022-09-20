#include "../header/menu.h"

using namespace std;

void menu(bool resultOutput, bool advancedOptions, bool supressAnneal)
{
	string rO;
	string r1;
	if (resultOutput) { rO = "(ON)  "; }
	else { rO = "(OFF) "; }

	if (supressAnneal) { r1 = "(ON)  "; }
	else { r1 = "(OFF) "; }

	if(!advancedOptions){
		cout << "  _________________________________________________ \n";
		cout << " |                       Menu                      |\n";
		cout << " | -1) Advanced Menu                               |\n";
		cout << " |--------------------- Input ---------------------|\n";
		cout << " |  1) Convert SQD folder to Simulation files      |\n"; 
		cout << " |  2) Load into memory wanted simulation file     |\n"; 
		cout << " |  3) Load list of perturbers for simulation file |\n";
		cout << " |-------------------- Runtime --------------------|\n";
		cout << " |  4) Make permutations of the loaded file        |\n";
		cout << " |  5) Call Simanneal on all annealInput files     |\n";
		cout << " |-------------------- Results --------------------|\n";
		cout << " |  6) Read single result file                     |\n";
		cout << " |  7) Read entire result folder                   |\n";
		cout << " |  8) Print full result "+rO+"                    |\n";
		cout << " |  9) Print DB situation                          |\n";
		cout << " |  0) Quit                                        |\n";
		cout << " |_________________________________________________|\n";
	}
	else{
		cout << "  _________________________________________________ _________________________________________________\n";
		cout << " |                       Menu                      |                    Adv. Menu                    |\n";
		cout << " |--------------------- Input ---------------------|--------------------- Batch ---------------------|\n";
		cout << " |  1) Convert SQD folder to Simulation files      | 11) Batch mode for a single file                |\n"; 
		cout << " |  2) Load into memory wanted simulation file     | 12) Batch mode for all files!  (WIP)            |\n"; 
		cout << " |  3) Load list of perturbers for simulation file | 13) Configurate Randomizer                      |\n";                                            
		cout << " |-------------------- Runtime --------------------| 14) Start Randomization                         |\n";
		cout << " |  4) Make permutations of the loaded file        |                                                 |\n";
		cout << " |  5) Call Simanneal on all annealInput files     |                                                 |\n";
		cout << " |-------------------- Results --------------------|                                                 |\n";
		cout << " |  6) Read single result file                     |                                                 |\n";
		cout << " |  7) Read entire result folder                   |                                                 |\n";
		cout << " |  8) Print full result "+rO+"                    |                                                 |\n";
		cout << " |  9) Print DB situation                          | -1) Normal Menu                                 |\n";
		cout << " |  0) Quit                                        | -2) Supress Anneal  "+r1+"                      |\n";
		cout << " |_________________________________________________|_________________________________________________|\n";
	}
}

string conversionText()
{
	string inputx;
	string valueMi;

	std::cout << "> The entire sqdInput folder will be converted into Simulation files. \n";
	std::cout << "> Do you want to convert the entire folder? (y/n) >> ";
	std::cin >> inputx;
	if(inputx.compare("y") == 0 || inputx.compare("Y") == 0)
	{
		std::cout << "> Please type the wanted value of Mi, or press enter to leave the default of -0.25 >> ";
		//getchar(); // Here just so it can take the floating \n from Cin
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, valueMi);
		if(valueMi.empty())	{ valueMi = "-0.25"; }

		return valueMi;
	}
	std::cout << "> Operation aborted\n";
	return noConversion;

}

string loadSimText()
{
	string fileName;
	std::cout << "> Please type the file name\n";
	std::cout << "> Attention: The .XML will be automatically added!!\n";
	std::cout << "> Addendum: The file should be on the folder simulationFiles\n";
	std::cout << "> Addendum2: The XML file can obtained by converting the .SQD file with the option 1)\n >> ";
	cin >> fileName;
	return dir_simulation + fileName + ".xml";
}

string loadPerturberText()
{
	string fileName;
	std::cout << "> Please type the file name\n";
	std::cout << "> Attention: The .txt will be automatically added!!\n";
	std::cout << "> Addendum: The file should be on the folder op, check reference file.\n >> ";
	std::cin >> fileName;
	return dir_operations + fileName + ".txt";
}

string loadPermutationText()
{
	string y;
	std::cout << "> Are you sure you wanna execute the program?\n";
	std::cout << "> This will make several file variations on the folder annealInput, make sure its empty!\n";
	std::cout << "> [y/n]: ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin >> y;

	if(y.compare("y") == 0 || y.compare("Y") == 0){
		std::cout << "> What is the name for the permutation files?\n >> ";
		std::cin >> y;
		return y;
	}
	return "0";
}

void annealCallText()
{
	std::cout << "> Calling SimAnneal for all files in the annealInput folder\n";
}

string singleResultsText()
{
	string fileName;
	cout << "> Please type the file name\n> Attention: The file must exist in the results folder, must be a result file\n >> ";
	cin >> fileName;
	return dir_output_xml + fileName + ".xml";
}

int allResultsText()
{
	string y;
	std::cout << "> This will read all results from the result folder.\n";
	std::cout << "> Make sure it's only from the current problem! Are you sure?\n";
	std::cout << "> [y/n]: ";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::cin >> y;
	if(y.compare("y") == 0 || y.compare("Y")){
		return 1;
	}
	return 0;
}