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
            * minN;
            * maxN;
            * latticeMin
            * minM;
            * maxM;
            * latticeMax
            * maxDBs;
            * divideX;
            * divideY;
            */
           switch (x){
                case 0: mi = std::stof(aux);        break;
                case 1: minN = std::stoi(aux);      break;
                case 2: maxN = std::stoi(aux);      break;
                case 3: latticeMin = std::stoi(aux);  break;
                case 4: minM = std::stoi(aux);      break;
                case 5: maxM = std::stoi(aux);      break;
                case 6: latticeMax = std::stoi(aux);  break;
                case 7: maxDBs = std::stoi(aux);    break;
                case 8: divideX = std::stoi(aux);   break;
                case 9: divideY = std::stoi(aux); break;
                case 10: interactions = std::stoi(aux);
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
    cout << minN << endl;
    cout << maxN << endl;
    cout << minM << endl;
    cout << maxM << endl;  
    cout << maxDBs << endl;
    cout << divideX << endl;
    cout << divideY << endl;
    cout << valid << endl;
    cout << interactions << endl;

    int N, M, L;
    int absOfN = maxN - minN;
    int absOfM = maxM - minM; 
    int x;
    int randomNumber = 0;
    char toCanvas;
    int extraDBs = 0;


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
    //Initialize Canvas.
	for(int x = 0; x < dbAmount; x++){			
		/*if(dba[x].getActive()){
			toCanvas = 'A';
		}
		else{toCanvas = 'O';}*/
        toCanvas = 'O';
		canvas[dba[x].getM() + (maxCanvasX/2)][dba[x].getN() + (maxCanvasY/2)][dba[x].getL()] = toCanvas;
    }

    //Make While loop for randomization
    
    canvas[minM + (maxCanvasX/2)][minN + (maxCanvasY/2)][latticeMin] = 'B';
    canvas[minM + (maxCanvasX/2)][maxN + (maxCanvasY/2)][latticeMin] = 'B';
    canvas[maxM + (maxCanvasX/2)][minN + (maxCanvasY/2)][latticeMax] = 'B';
    canvas[maxM + (maxCanvasX/2)][maxN + (maxCanvasY/2)][latticeMax] = 'B';
    while(x < interactions){
        extraDBs = 0;
        while(extraDBs != maxDBs){//Make random calls, place DBs following certain rules.
            N = (rand() % absOfN) + minN; // -2 to 6
            M = (rand() % absOfM) + minM;
            L = (rand() % 2);
            cout << "N: " << N << '\n' << "M: " << M << '\n' << "L: " << L << '\n';

            /*dba[dbAmount].setDB(N, M, L);
            toCanvas = 'P';
            canvas[dba[dbAmount + extraDBs].getM() + (maxCanvasX/2)][dba[dbAmount + extraDBs].getN() + (maxCanvasY/2)][dba[dbAmount + extraDBs].getL()] = toCanvas;*/
            extraDBs++;
        }
        
        /*for(int column = 0; column < maxCanvasX; column++){
			for (int latice = 0; latice < maxCanvasLatice; latice++){
				for(int line = 0; line < maxCanvasY; line++){
					LOG << canvas[column][line][latice] << ' ';
				}
				LOG << '\n';
			}
			LOG << '\n';
        }*/
        x++;
    }

    // Print Canvas.
    for(int column = 0; column < maxCanvasX; column++){
			for (int latice = 0; latice < maxCanvasLatice; latice++){
				for(int line = 0; line < maxCanvasY; line++){
					LOG << canvas[column][line][latice] << ' ';
				}
				LOG << '\n';
			}
			LOG << '\n';
    }
    
}