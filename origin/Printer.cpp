#include "../header/MainFileManager.h"
#include "../header/RandomFileCreator.h"

void printResult(danglingBonds dba[], int dbAmount, double *X, double *Y, bool fullResult, ofstream *LOG, string filename)
{
	int x = 0;
	int m;
	int n;
	int l;
	int y = 0;
	char toCanvas;
	bool alreadyPrinted = false;
	char canvas[maxCanvasX][maxCanvasY][maxCanvasLatice];
	std::cout << "> File: " << filename << '\n';
	*LOG << "File: " << filename << '\n';

	//Canvas making
	for(int column = 0; column < maxCanvasX; column++){			
		for (int line = 0; line < maxCanvasY; line++){
			for(int latice = 0; latice < maxCanvasLatice; latice++)
			{ canvas[column][line][latice] = '.'; }
		}
	}
	for(x = 0; x < dbAmount; x++){			
		if(dba[x].getActive()){
			if(!dba[x].getObserved()){
				if(dba[x].getState()){toCanvas = 'N';}
				else{toCanvas = 'O';}
				/*else{toCanvas = 'P';}*/
			}
			else{
				if(dba[x].getState()){toCanvas = 'M';}
					else{toCanvas = '0';}
				/*else{toCanvas = 'P';}*/
			}
		}
		else{toCanvas = '-';}
		canvas[dba[x].getM() + (maxCanvasX/2)][dba[x].getN() + (maxCanvasY/2)][dba[x].getL()] = toCanvas;
	}
	printDBResult(dba, dbAmount);
	//Canvas printing
	if(fullResult)
	{
		for(int column = 0; column < maxCanvasX; column++){
			for (int latice = 0; latice < maxCanvasLatice; latice++){
				for(int line = 0; line < maxCanvasY; line++){
					std::cout << canvas[column][line][latice] << ' ';
					*LOG << canvas[column][line][latice] << ' ';
				}
				std::cout << "\n";
				*LOG << '\n';
			}
			std:: cout << "\n";
			*LOG << '\n';
		}
		std::cout << '\n';
	}
	else
	{
		for(int column = 0; column < maxCanvasX; column++){
			for (int latice = 0; latice < maxCanvasLatice; latice++){
				for(int line = 0; line < maxCanvasY; line++){
					*LOG << canvas[column][line][latice] << ' ';
				}
				*LOG << '\n';
			}
			*LOG << '\n';
		}
	}
}

void printFullResult(danglingBonds dba[], int dbAmount, bool fullResult)
{
	ofstream LOG;
	LOG.open("log.txt");
	DIR *d;
    struct dirent *dir;
    d = opendir(dir_output_xml);
    string command;
    string filename;
    string purefileName;
    if(d){       
		while((dir = readdir(d)) != NULL){
            if(dir->d_name[0] != '.'){
                purefileName = dir->d_name;
				filename = dir_output_xml + purefileName;
				readResultFile(filename, dba, dbAmount, fullResult, &LOG);
            }
			LOG << "\n";
        }
    }
	LOG.close();

}

void printDBResult(danglingBonds dba[], int dbAmount){
	for (int x = 0; x < dbAmount; x++){
		if (dba[x].getObserved() == 1){
			if (dba[x].getState() == 0){
				std::cout << "The observed DB is Neutral (Transparent)\n";
			}
			else{
				std::cout << "The observed DB is Negative (Blue)\n";
			}
		}
	}
}

void printRandomizer(danglingBonds dba[], int dbAmount, double *X, double *Y, bool fullResult, ofstream *LOG, string filename, char canvas[maxCanvasX][maxCanvasY][maxCanvasY]){
	
	int x = 0;
	int m;
	int n;
	int l;
	int y = 0;
	char toCanvas;
	bool alreadyPrinted = false;
	std::cout << "> File: " << filename << '\n';
	*LOG << "File: " << filename << '\n';

	//Canvas making
	for(int column = 0; column < maxCanvasX; column++){			
		for (int line = 0; line < maxCanvasY; line++){
			for(int latice = 0; latice < maxCanvasLatice; latice++)
			{ canvas[column][line][latice] = '.'; }
		}
	}
	for(x = 0; x < dbAmount; x++){			
		if(dba[x].getActive()){
			if(!dba[x].getObserved()){
				if(dba[x].getState()){toCanvas = 'N';}
				else{toCanvas = 'O';}
				/*else{toCanvas = 'P';}*/
			}
			else{
				if(dba[x].getState()){toCanvas = 'M';}
					else{toCanvas = '0';}
				/*else{toCanvas = 'P';}*/
			}
		}
		else{toCanvas = '-';}
		canvas[dba[x].getM() + (maxCanvasX/2)][dba[x].getN() + (maxCanvasY/2)][dba[x].getL()] = toCanvas;
	}
	//Canvas printing
	if(fullResult)
	{
		for(int column = 0; column < maxCanvasX; column++){
			for (int latice = 0; latice < maxCanvasLatice; latice++){
				for(int line = 0; line < maxCanvasY; line++){
					std::cout << canvas[column][line][latice] << ' ';
					*LOG << canvas[column][line][latice] << ' ';
				}
				std::cout << "\n";
				*LOG << '\n';
			}
			std:: cout << "\n";
			*LOG << '\n';
		}
		std::cout << '\n';
	}
	else
	{
		for(int column = 0; column < maxCanvasX; column++){
			for (int latice = 0; latice < maxCanvasLatice; latice++){
				for(int line = 0; line < maxCanvasY; line++){
					*LOG << canvas[column][line][latice] << ' ';
				}
				*LOG << '\n';
			}
			*LOG << '\n';
		}
	}
}