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

void configurationFileRFC::makeRandomization(danglingBonds dba[], int dbAmount, int* randomCalls){    
    std::cout << mi << endl;
    std::cout << minN << endl;
    std::cout << maxN << endl;
    std::cout << minM << endl;
    std::cout << maxM << endl;  
    std::cout << maxDBs << endl;
    std::cout << divideX << endl;
    std::cout << divideY << endl;
    std::cout << valid << endl;
    std::cout << interactions << endl;

    int N, M, L;
    int absOfN = maxN - minN;
    int absOfM = maxM - minM; 
    int x = 0;
    int randomNumber = 0;
    char toCanvas;
    int extraDBs = 0;
    int addToM;
    int newL;

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
	for(int k = 0; k < dbAmount; k++){			
		/*if(dba[x].getActive()){
			toCanvas = 'A';
		}
		else{toCanvas = 'O';}*/
        toCanvas = 'O';
		canvas[dba[k].getM() + halfCanvasX][dba[k].getN() + halfCanvasY][dba[k].getL()] = toCanvas;
    }

    //Initialize Seed.
    for(int k = 0; k < *randomCalls; k += 3){
        N = (rand() % (absOfN + 1)) + minN; // -2 to 6
        M = (rand() % (absOfM + 1)) + minM;
        L = (rand() % 2);
    }

    //Make While loop for randomization
    
    /*canvas[minM + halfCanvasX][minN + halfCanvasY][latticeMin] = 'B';
    canvas[minM + halfCanvasX][maxN + halfCanvasY][latticeMin] = 'B';
    canvas[maxM + halfCanvasX][minN + halfCanvasY][latticeMax] = 'B';
    canvas[maxM + halfCanvasX][maxN + halfCanvasY][latticeMax] = 'B';*/
    std::cout << x << "\n" <<interactions << "\n";
    while(x < interactions){
        extraDBs = 0;
        while(extraDBs != maxDBs){//Make random calls, place DBs following certain rules.
            //Call NML positions randomly.
            N = (rand() % (absOfN + 1)) + minN; // -2 to 6
            M = (rand() % (absOfM + 1)) + minM;
            L = (rand() % 2);
            //Apply Rules:
            //Rule One: The current spot cannot be ocuppied.
            if(canvas[M + halfCanvasX][N + halfCanvasY][L] == '.')
            {
                //Apply DBs:
                //std::cout << "Int: " << x <<"/" << interactions << " N: " << N << " M: " << M << " L: " << L << '\n';           
                dba[dbAmount + extraDBs].setDB(N, M, L);
                toCanvas = 'P';
                canvas[M + halfCanvasX][N + halfCanvasY][L] = toCanvas;
                //canvas[dba[dbAmount + extraDBs].getM() + halfCanvasX][dba[dbAmount + extraDBs].getN() + halfCanvasY][dba[dbAmount + extraDBs].getL()] = toCanvas;
                //Rule Two: A 3x3 area is interdicted.
                if(L == 0){ //Can only fill his own Lattice 1, and the upper neighbor Lattice 1;
                    newL = 1;
                    addToM = -1;
                }
                else{ // Can only fill his own lattice 0, and the lower neighbor Lattic 0;
                    newL = 0;
                    addToM = 1;                 
                }
                //Applying rule Two:
                canvas[M + halfCanvasX][N + 1 + halfCanvasY][L] = 'x';
                canvas[M + halfCanvasX][N - 1 + halfCanvasY][L] = 'x'; 
                canvas[M + halfCanvasX][N + halfCanvasY][newL] = 'x'; //Own lattice
                canvas[M + halfCanvasX][N + 1 + halfCanvasY][newL] = 'x'; //Own lattice
                canvas[M + halfCanvasX][N - 1 + halfCanvasY][newL] = 'x'; //Own lattice
                canvas[M + addToM + halfCanvasX][N + 1 + halfCanvasY][newL] = 'x'; //Neighbor lattice.
                canvas[M + addToM + halfCanvasX][N - 1 + halfCanvasY][newL] = 'x'; //Neighbor Lattice.
                canvas[M + addToM + halfCanvasX][N + halfCanvasY][newL] = 'x'; //Neighbor lattice.

                /*canvas[dba[dbAmount + extraDBs].getM() + halfCanvasX][dba[dbAmount + extraDBs].getN() + halfCanvasY][dba[dbAmount + extraDBs].getL()] = 'x';
                canvas[dba[dbAmount + extraDBs].getM() + halfCanvasX][dba[dbAmount + extraDBs].getN() + halfCanvasY][dba[dbAmount + extraDBs].getL()] = 'x';
                canvas[dba[dbAmount + extraDBs].getM() + halfCanvasX][dba[dbAmount + extraDBs].getN() + halfCanvasY][dba[dbAmount + extraDBs].getL()] = 'x';
                canvas[dba[dbAmount + extraDBs].getM() + halfCanvasX][dba[dbAmount + extraDBs].getN() + halfCanvasY][dba[dbAmount + extraDBs].getL()] = 'x';
                canvas[dba[dbAmount + extraDBs].getM() + halfCanvasX][dba[dbAmount + extraDBs].getN() + halfCanvasY][dba[dbAmount + extraDBs].getL()] = 'x';
                canvas[dba[dbAmount + extraDBs].getM() + halfCanvasX][dba[dbAmount + extraDBs].getN() + halfCanvasY][dba[dbAmount + extraDBs].getL()] = 'x';
                canvas[dba[dbAmount + extraDBs].getM() + halfCanvasX][dba[dbAmount + extraDBs].getN() + halfCanvasY][dba[dbAmount + extraDBs].getL()] = 'x';*/
                extraDBs++;
            }
    
        }
        //std::cout << "Test ---\n";

       
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

        x++;
        //Clear canvas, the quickest and most efficient method would be applying the rules in reverse, but i'm not in the mood for that...
        for(int h = minM - 1; h <= maxM + 1; h++){
            for(int j = minN - 1; j <= maxN + 1; j++){
                for(int p = 0; p <= 1; p++){
                    canvas[h + halfCanvasX][j + halfCanvasY][p] = '.';
                }
            }
                
        }
        
    }

    // Print Canvas.
    
    LOG.close();
    
}