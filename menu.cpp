#include "menu.h"

using namespace std;

void menu(bool resultOutput)
{
	string rO;
	if (resultOutput) { rO = "(ON)  "; }
	else { rO = "(OFF) "; }
	cout << "  _________________________________________________ \n";
	cout << " |                       Menu                      |\n";
	cout << " |--------------------- Input ---------------------|\n";
	cout << " |  1) Convert SQD folder to Simulation files      |\n"; //OK
	cout << " |  2) Load into memory wanted simulation file     |\n"; //
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

string conversionText()
{
	string inputx;
	string valueMi;

	std::cout << "> The entire sqdInput folder will be converted into Simulation files. \n";
	std::cout << "> Do you want to convert the entire folder? (y/n) >> ";
	std::cin >> inputx;
	if(inputx.compare("y") == 0 || inputx.compare("Y") == 0);
	{
		std::cout << "> Please type the wanted value of Mi, or press enter to leave the default of -0.25 >> ";
		//getchar(); // Here just so it can take the floating \n from Cin
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(std::cin, valueMi);
		if(valueMi.empty())
		{
			valueMi = "-0.25";
		}

		return valueMi;
	}
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
	std::cout << "> Please type the file name\n> Attention: The .txt will be automatically added!!\n> Addendum: The file should be on the folder op, check reference file.\n >> ";
	std::cin >> fileName;
	return dir_operations + fileName + ".txt";
}