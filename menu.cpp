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

float conversionText()
{
	string inputx;
	float valueMi = -0.25;

	cout << "> The entire sqdInput folder will be converted into Simulation files. \n";
	cout << "> Do you want to convert the entire folder? (y/n) >> ";
	cin >> inputx;
	if(inputx.compare("y") == 0 || inputx.compare("Y") == 0);
	{
		cout << "> Please type the wanted value of Mi, or press enter to leave the default of -0.25 >> ";
		cin >> valueMi;

		return valueMi;
	}
	return noConversion;

}

void loadSimText()
{
	cout << "> Please type the file name\n";
	cout << "> Attention: The .XML will be automatically added!!\n";
	cout << "> Addendum: The file should be on the folder simulationFiles\n";
	cout << "> Addendum2: The XML file can obtained by converting the .SQD file with the option 1) >> ";
}