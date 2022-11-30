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
                case 10: interactions = std::stoi(aux); break;
                case 11: maxBatches = std::stoi(aux);
                        valid = true;
                        return; 
           }
           x++;
        }
    }
    valid = false;
    return;
}

void configurationFileRFC::printInfo(){
    std::cout << "mi: " << mi << endl;
    std::cout << "minN: " << minN << endl;
    std::cout << "maxN: " << maxN << endl;
    std::cout << "minM: " << minM << endl;
    std::cout << "maxM: " << maxM << endl;  
    std::cout << "maxDBs: "<< maxDBs << endl;
    std::cout << "divideX: "<< divideX << endl;
    std::cout << "divideY: "<< divideY << endl;
    //std::cout << valid << endl;
    std::cout << "maxInteractions: "<< interactions << endl;
}

void configurationFileRFC::makeRandomization(danglingBonds dba[], int dbAmount, int* randomCalls, int seed, string bs, string be, string fileName){    

    int N, M, L, x = 0, step = 1, extraDBs = 0, addToM, newL;
    int absOfN = maxN - minN;
    int absOfM = maxM - minM; 
    char toCanvas;
    ofstream LOG;
	
    this->printInfo();
	
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
	//ToDO: make a function that will initialize the seed, and a function that will initialize the CANVAS to lower the size of this func.
    for(int k = 0; k < *randomCalls; k += 3){
        N = (rand() % (absOfN + 1)) + minN; // -2 to 6
        M = (rand() % (absOfM + 1)) + minM;
        L = (rand() % 2);
    }

    std::cout << "\n";
    std::cout << "Progress Interactions: |";
    while(x < interactions){
        extraDBs = 0;

        while(extraDBs != maxDBs){//Make random calls, place DBs following certain rules.
            //Call NML positions randomly.
            N = (rand() % (absOfN + 1)) + minN; // -2 to 6
            M = (rand() % (absOfM + 1)) + minM;
            L = (rand() % 2);
            *randomCalls += 3;
            //Apply Rules:
            //Rule One: The current spot cannot be ocuppied.
            if(canvas[M + halfCanvasX][N + halfCanvasY][L] == '.')
            {
                //Apply DBs:          
                dba[dbAmount + extraDBs].setDB(N, M, L);
                dba[dbAmount + extraDBs].findDotBuffer();
                toCanvas = 'P';
                canvas[M + halfCanvasX][N + halfCanvasY][L] = toCanvas;
            
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

                extraDBs++;
            }            
        }
        if(x >= ((interactions/100) * step)){
            std::cout << "\u25A0" << std::flush;
            step++;
        }
        x++;

        //Save file after making one random one.
        saveFile(dba, dbAmount + extraDBs, randomCalls, seed, bs, be, fileName);

        // Print Canvas in a LOG File. //Place in its own function in PRINTAUX thingy;
        for(int column = 0; column < maxCanvasX; column++){
			for (int latice = 0; latice < maxCanvasLatice; latice++){
				for(int line = 0; line < maxCanvasY; line++){
					LOG << canvas[column][line][latice] << ' ';
				}
				LOG << '\n';
			}
			LOG << '\n';
        }
	    
        //Clear canvas, the quickest and most efficient method would be applying the rules in reverse, but i'm not in the mood for that...
	//Plus, this method only takes fractions of a second at the moment.
        for(int h = minM - 1; h <= maxM + 1; h++){
            for(int j = minN - 1; j <= maxN + 1; j++){
                for(int p = 0; p <= 1; p++){
                    canvas[h + halfCanvasX][j + halfCanvasY][p] = '.';
                }
            }        
        }  
    }
    std::cout << "\u25A0" << "| Done" << std::endl;
    LOG.close();
}

int RandomBatch(danglingBonds dba[], configurationFileRFC rfc, string filenamePert, int seed, int *randomCalls){
	string fileName = "./simulationFiles/Hexagon31.xml";
    string bufferStart;
    string bufferEnd;
	int dbAmount = 0;
    int batchAmount = 0;
    //step 2;
    DIR *d;
    struct dirent *dir;
    string command;
    string fileName2;
    //step 3;
    int dbd[MaxDBS];
    //step 4:
    string fileName3;
    int x;
    int perm;
    int step = 0;
    int inv = rfc.getInteractions();
    
    //Step 8:
    string temp;
    temp = randomOutput;
    string deletionCommand1 = "perl -e 'for(<" + temp + "*>){((stat)[9]<(unlink))}'";
    temp = randomOutputAnneal;
    string deletionCommand2 = "perl -e 'for(<" + temp + "*>){((stat)[9]<(unlink))}'";
    temp = randomAnnealOutput_xml;
    string deletionCommand3 = "perl -e 'for(<" + temp + "*>){((stat)[9]<(unlink))}'";
    //string outputname;

    //Objectives:
    while(batchAmount < rfc.getBatches()){
        //Load the file for the batch.
        fileName = "./simulationFiles/Hexagon31.xml";
        dbAmount = readSim(fileName, dba, bufferStart, bufferEnd);
        //Make the Loading bar variable for permutations:
        perm = readList(filenamePert, dba, dbAmount, dbd);
	    rfc.makeRandomization(dba, dbAmount, randomCalls, seed, bufferStart, bufferEnd, "Hexagon31");
        //Load into memory one of the simulation files
        d = opendir(randomOutput);
        x = 0;
        if(d){
            std::cout << "Progress Permutation:  |";
            while((dir = readdir(d)) != NULL){
                if(dir->d_name[0] != '.'){
                    fileName2 = randomOutput;
                    fileName2.append(dir->d_name);
                    dbAmount = readSim(fileName2, dba, bufferStart, bufferEnd);
                    //cout << "Open File: " << fileName2 << endl;
                    //Load OP File (Perturber file)
                    if (dbAmount != 0) { 								
				        perm = readList(filenamePert, dba, dbAmount, dbd);				//Read the list of perturbers and set in memory.
                        if(perm == -1){
                            system(deletionCommand1.c_str());
                            system(deletionCommand2.c_str());
                            system(deletionCommand3.c_str());
                            return -1;
                        }
                        //Make permutations
                        fileName3 = dir->d_name;
                        fileName3.pop_back();
                        fileName3.pop_back();
                        fileName3.pop_back();
                        fileName3.pop_back();
                        createPermutations(dba, bufferStart, bufferEnd, dbAmount, (fileName3 + "_"), randomOutputAnneal);
                        if(x >= ((inv/100) * step)){
                            std::cout << "\u25A0" << std::flush;
                            step++;
                        }
                        x++;
                        //Call Anneal on them.
                        callAnneal(dbAmount, true, randomOutputAnneal, randomAnnealOutput_xml);
                        //Check results.
                        //If results are favorable with wanted results, send the file to another folder
                        organizeResults(dba, dbAmount, fileName2);       
                        //system(deletionCommand1.c_str());
                        system(deletionCommand2.c_str());
                        system(deletionCommand3.c_str());
				    } 
                }
            }
        }
        //Delete Files in Folders.
        std::cout << "| Done\n";
        //std::cout << "Deleting files for next Batch!\n";
        system(deletionCommand1.c_str());
        //system(deletionCommand2.c_str());
        //system(deletionCommand3.c_str());
        batchAmount++;
        //Go to next Batch.
    }
    //callAnneal(dbAmount, true, randomOutputAnneal);
    return 0;
}

bool checkBTables(bool mainTable[], bool checkTable[], int size){
    if(size == 8){
         for(int x = 0; x < 8; x++){
            if(mainTable[x] != checkTable[x]){
                return false;
            }
         }
    }
    return true;
}

void organizeResults(danglingBonds dba[], int dbAmount, string originalFile)
{

    string mixAux;

    bool _and = true, _nand = true, _xand = true, _xnand = true,
     _or = true, _xor = true, _nor = true, _xnor = true, _mux001 = true,
     _mux010 = true, _mux100 = true;
    bool AND8[8]    = {0,0,0,0,0,0,0,1};
    bool NAND8[8]   = {1,1,1,1,1,1,1,0};
    bool XAND8[8]   = {1,0,0,0,0,0,0,1};
    bool XNAND8[8]  = {0,1,1,1,1,1,1,0};
    bool OR8[8]     = {0,1,1,1,1,1,1,1};
    bool XOR8[8]    = {0,1,1,0,1,0,0,1};
    bool NOR8[8]    = {1,0,0,0,0,0,0,0};
    bool XNOR8[8]   = {1,0,0,1,0,1,1,0};
    bool MUX001[8]  = {0,0,1,0,0,1,1,1};
    bool MUX010[8]  = {0,0,0,1,1,1,0,1};
    bool MUX100[8]  = {0,0,1,1,0,1,0,1};
    bool invalid[8] = {1,1,1,1,1,1,1,1};

    bool currentTable[8] = {};
   
    DIR *d;
    struct dirent *dir;
    d = opendir(randomAnnealOutput_xml);
    string command;
    string filename;
    string purefileName;
    if(d){       
		while((dir = readdir(d)) != NULL){
            if(dir->d_name[0] != '.'){
                purefileName = dir->d_name;
				filename = randomAnnealOutput_xml + purefileName;
                readResultFileHelper(dba, dbAmount, filename, currentTable);
            }
        }
    }

    //Now that all the values are saved, time to analyze them.
    //Here, we check if the DBA checks true with ANY of the arrays inserted.

    _and    = checkBTables(currentTable, AND8, 8);
    _nand   = checkBTables(currentTable, NAND8, 8);
    _xand   = checkBTables(currentTable, XAND8, 8);
    _xnand  = checkBTables(currentTable, XNAND8, 8);
    _or     = checkBTables(currentTable, OR8, 8);
    _xor    = checkBTables(currentTable, XOR8, 8);
    _nor    = checkBTables(currentTable, XNOR8, 8);
    _xnor   = checkBTables(currentTable, XNOR8, 8);
    _mux001 = checkBTables(currentTable, MUX001, 8);
    _mux010 = checkBTables(currentTable, MUX010, 8);
    _mux100 = checkBTables(currentTable, MUX100, 8);

    //cout << currentTable;
    //Now, we check if any of them was true;
    if(_and || _nand || _xand || _xnand || _or || _xor || _nor || _xnor || _mux001 || _mux010 || _mux100){

        //cp ./randomGen/Hexagon31_42_12.xml ./RandomFileCreatorFolder/FoundResults/AND/


        if(_and)   { mixAux = "cp " + originalFile + " " + dir_AND;    }
        if(_nand)  { mixAux = "cp " + originalFile + " " + dir_NAND;   }
        if(_xand)  { mixAux = "cp " + originalFile + " " + dir_XAND;   }
        if(_xnand) { mixAux = "cp " + originalFile + " " + dir_XNAND;  }
        if(_or)    { mixAux = "cp " + originalFile + " " + dir_OR;     }
        if(_xor)   { mixAux = "cp " + originalFile + " " + dir_XOR;    }
        if(_nor)   { mixAux = "cp " + originalFile + " " + dir_NOR;    }
        if(_xnor)  { mixAux = "cp " + originalFile + " " + dir_XNOR;   }
        if(_mux001){ mixAux = "cp " + originalFile + " " + dir_MUX001; }
        if(_mux010){ mixAux = "cp " + originalFile + " " + dir_MUX010; }
        if(_mux100){ mixAux = "cp " + originalFile + " " + dir_MUX100; }
    }
    else
    {
        mixAux = "cp " + originalFile + " " + dir_INV;  
    }
    
	system(mixAux.c_str());
    return;
}

