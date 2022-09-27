#include "../header/RandomFileCreator.h"



void configurationFileRFC::configFileName(){
    std::ifstream configFile;
    string aux;
    aux.append(dir_configFile);
    aux.append("mainConfig.txt");
    configFile.open(aux);
    std::getline(configFile, workingFileName);
    configFile.close();
}

void configurationFileRFC::changeWorkplace(){
    string aux;
    int x = 0;
    std::ifstream workingFile;
    workingFile.open(workingFileName);
    if(workingFile){
        while(std::getline(workingFile, aux)){
            /* File Format:
            * mi;
            * minX
            * maxX;
            * minY;
            * maxY;
            * maxDBs;
            * divideX;
            * divideY;
            */
           switch (x){
                case 0: mi = std::stof(aux);    break;
                case 1: minX = std::stoi(aux);    break;
                case 2: maxX = std::stoi(aux);    break;
                case 3: minY = std::stoi(aux);    break;
                case 4: maxY = std::stoi(aux);    break;
                case 5: maxDBs = std::stoi(aux);    break;
                case 6: divideX = std::stoi(aux);    break;
                case 7: divideY = std::stoi(aux); 
                        valid = true;
                        return; 
           }
           x++;
        }
    }
    valid = false;
    return;
}

void configurationFileRFC::makeRandomization(danglingBonds dba[], int dbAmount){
    cout << mi << endl;
    cout << minX << endl;
    cout << maxX << endl;
    cout << minY << endl;
    cout << maxY << endl;  
    cout << maxDBs << endl;
    cout << divideX << endl;
    cout << divideY << endl;
    cout << valid << endl;
    char toCanvas;

    ofstream LOG;
	LOG.open("hexTest.txt");
    //Place . on Canvas;
    char canvas[maxCanvasX][maxCanvasY][maxCanvasLatice];
    for(int column = 0; column < maxCanvasX; column++){			
		for (int line = 0; line < maxCanvasY; line++){
			for(int latice = 0; latice < maxCanvasLatice; latice++)
			{ canvas[column][line][latice] = '.'; }
		}
	}

	for(int x = 0; x < dbAmount; x++){			
		if(dba[x].getActive()){
			toCanvas = 'A';
		}
		else{toCanvas = 'O';}
		canvas[dba[x].getM() + (maxCanvasX/2)][dba[x].getN() + (maxCanvasY/2)][dba[x].getL()] = toCanvas;
    }
    for(int column = 0; column < maxCanvasX; column++){
			for (int latice = 0; latice < maxCanvasLatice; latice++){
				for(int line = 0; line < maxCanvasY; line++){
					LOG << canvas[column][line][latice] << ' ';
				}
				LOG << '\n';
			}
			LOG << '\n';
    }
    for(int x = 0; x < dbAmount; x++){
        dba[x].findXY();
    }
}
