#include "../header/MainFileManager.h"

void danglingBonds::findDotBuffer(){
	string dotBuffering[11];

	dotBuffering[0] = "            <dbdot>\n";
	dotBuffering[1] = "                <layer_id>2</layer_id>\n";
	dotBuffering[2] = "                <latcoord n=\"";
	dotBuffering[3] = "\" m=\"";
	dotBuffering[4] = "\" l=\"";
	dotBuffering[5] = "\"/>\n";
	dotBuffering[6] = "                <physloc x=\"";
	dotBuffering[7] = "\" y=\"";
	dotBuffering[8] = "\"/>\n";
	dotBuffering[9] = "                <color>#ffc8c8c8</color>\n";
	dotBuffering[10] = "            </dbdot>\n";

	this->dotBuffer = dotBuffering[0] + dotBuffering[1] +
	dotBuffering[2] + std::to_string(n) + dotBuffering[3] + std::to_string(m) +	dotBuffering[4] + std::to_string(l) + dotBuffering[5] + 
	dotBuffering[6] + std::to_string(X) + dotBuffering[7] + std::to_string(Y) + dotBuffering[8] + 
	dotBuffering[9] + dotBuffering[10];

}

void danglingBonds::findDBDot(string str, int mode)
{
	int x = 0, y = 0;
	char aux[20] = { 0 };
	bool found = false;

	isActive = false;
	disturber = false;
	observed = false;

	if(mode == 1){
		this->findXY();
		return;
	}

	for (std::string::size_type i = 0; i < str.size(); ++i){
		if (str[i] == doubleQuotes){
			found = !found; //Found becomes TRUE;
			x = 0;
			if (aux[0] != 0){
				if (mode == 0){
					if (y == 0)		 { n = atoi(aux); }
					else if (y == 1) { m = atoi(aux); }
					else if (y == 2) { l = atoi(aux); }
				}
				else{	
					/*I can substitute this method of getting the LINE and going trough hell with simply changing the MODE = 1 to call FINDXY, since 
					 * The formula is so easy now.
					*/
					//if (y == 0)		 { X = atof(aux); }
					//else if (y == 1) { Y = atof(aux); }
				}
				y++;
			}
			memset(aux, 0, sizeof(aux));
		}
		else if (found){
			aux[x] = str[i];
			x++;
		}
	}
}

void danglingBonds::findXY(){ 
	this->X = this->n * 3.84;
	this->Y = (this->m * 7.68) + (this->l * 2.25);
}

int convertSQDtoSim(string miValue) //Function that will convert the .SQD to a .XML simulation.
{
	//Variables
	int y = 0;
	char *fileBuffer = new char[20000];
    char *basicInfoBuffer = new char[20000];
	size_t found;
	std::stringstream baseFileBuffer;
	string baseFileAux;
    string filename;
    string finalFileName;
    string finalFileBuffer;

	//FILES
	std::ofstream finalFile;
	FILE *fptr;
    //FILE *baseFile;
	std::ifstream baseFile;
	
	//DIR
	DIR *d;
    struct dirent *dir;
    d = opendir(dir_input_sqd);

    if(d){
		baseFile.open(dir_basicInfoConfig);
		if(!baseFile) {
			cerr << "Error: File could not be opened\n";
			return -1;
		}
		baseFileBuffer << baseFile.rdbuf();
		baseFileAux = baseFileBuffer.str();
		found = baseFileAux.find("<muzm>");
		baseFileAux.replace(found + 6, 5, miValue);
		//std::cout << baseFileAux << '\n';
		baseFile.close();



        while((dir = readdir(d)) != NULL){       
	 	    if(dir->d_name[0] != '.'){
                filename = dir_input_sqd;
                filename.append(dir->d_name);
                finalFileName = dir_simulation;
                finalFileName.append(dir->d_name);
                finalFileName.pop_back();
                finalFileName.pop_back();
                finalFileName.pop_back();
                finalFileName.append("xml");
                finalFileBuffer = "";
                //std::cout << filename << endl;
				std::cout << finalFileName << endl;
                //Converting from SQD to XML
				finalFileBuffer.append(baseFileAux);
				fptr = fopen(filename.c_str(), "r");
				y = 0;
                while(fgets(fileBuffer, 20000, fptr) != NULL)
                {
                    if(y > 7)
                    {
						//cout <<fileBuffer << y << endl;
                        finalFileBuffer.append(fileBuffer);
                    }
                    y++;
                }
                fclose(fptr);
                finalFile.open(finalFileName);
				//cout <<finalFileBuffer << endl;
                finalFile << finalFileBuffer;
				finalFile.close();
            }
        }
        closedir(d);
        return 0;
    }

 return -1;
}

int readSim(string fileName, danglingBonds dba[MaxDBS], string& bufferStart, string& bufferEnd)
{
	//Initialization Stage
	bufferStart.clear();
	bufferEnd.clear();
	
	for (int y = 0; y < MaxDBS; y++) {dba[y].cleanDBs();}

	int count;
	int db = 0;
	bool anyfoundDB = false; // Verifies if ANY DB was found, for the first half of the text;
	bool endOfText = false;
	bool dbFound = false; // Gets each found DB
	string line;
	string lineAux;
	ifstream SQDFile;

	SQDFile.open(fileName);

	if (SQDFile.is_open()){
		while (getline(SQDFile, line)){
			lineAux = line;
			removeSpaces(line);
			if (line.compare("<dbdot>") == 0){
				anyfoundDB = true;
				dbFound = true;
				count = 0;
			}
			else if (line.compare("</dbdot>") == 0){ 
				dbFound = false; 	
				dba[db].dotBuffer = dba[db].dotBuffer + lineAux + '\n';
				db++;
			}

			if (!anyfoundDB) { bufferStart += lineAux + '\n'; }
			else if (line.compare("</layer>") == 0) { endOfText = true; }

			if (dbFound){
				dba[db].dotBuffer = dba[db].dotBuffer + lineAux + '\n';
				if (count == 2) { dba[db].findDBDot(line, 0); } // Currently on LATCOORD
				else if (count == 3){ dba[db].findDBDot(line, 1); } // Currently on PHYSLOC
				count++;
			}
			if (endOfText)	{ bufferEnd += lineAux + '\n'; }
		}
		SQDFile.close();
	}
	else{
		std::cout << "> error! Invalid File \n";
		return 0;
	}
	//std::cout << "> Done!\n";
	return db;
}

int readList(string fileName, danglingBonds dba[], int dbamount, int *disturberArray)
{
	
	string line;
	ifstream listFile;
	listFile.open(fileName);
	int n = 0, m = 0, l = 0, output = 0, fileLine = 1;
	int count = 0, compare = 0, dist = 0;
	string word;

	if (listFile.is_open())
	{
		while (getline(listFile, line)){
			if (count == 0) { output = stoi(line); 	count++;}
			else{
				stringstream sstream(line);
				while (getline(sstream, word, ' ')){
					if (count == 1) n = stoi(word);
					else if (count == 2) m = stoi(word);
					else if (count == 3) l = stoi(word);
					if (count == 3){
						for (int x = 0; x < dbamount; x++){
							compare = dba[x].compare(n, m, l);
							if (compare){
								if (fileLine == output) { dba[x].setObserver();}
								else{
									dba[x].setDisturber();
									disturberArray[dist] = x;
									dist++;
								}
								break;
							}
						}
						fileLine++;
						count = 1;
						break;
					}
					count++;
				}
			}
		}
		//std::cout << "> Done!\n";
	}
	else{
		std::cout << "> Error! Invalid File!\n";
		return -1;
	}
	return output;
}

void removeSpaces(string &str)
{
	auto noSpace = std::remove(str.begin(), str.end(), ' ');
	str.erase(noSpace, str.end());
}

int createPermutations(danglingBonds dba[], string first, string second, int dbAmount, string fileName, string outputPath)
{
	ofstream SQDFile;
	string output = outputPath + fileName + "0.xml";
	//cout << output << endl;
	string * combin = new string[5];

	int next = 1;
	int lenght = 0;

	bool check[5];
	for (int x = 0; x < MaxDBS; x++){
		if (dba[x].getDisturber() == 1){lenght++;}
	}

	int h = 0;
	for (int x = 0; x < dbAmount; x++){
		if (dba[x].getDisturber()){
			combin[h] = dba[x].dotBuffer;
			h++;
		}
	}

	SQDFile.open(output);
	for (int x = 0; x < dbAmount; x++){
		if (!dba[x].getDisturber()){
			first = first + dba[x].dotBuffer;
		}
	
	}
	SQDFile << first;
	SQDFile << second;
	//cout << first << '\n';
	//cout << second << '\n';
	SQDFile.close();


	for (int i = 1; i <= lenght; i++) {
		Combi(combin, i, 0, 0, check, lenght, first, second, &next, fileName, outputPath);
	}
	//std::cout << "> Done!\n";
	return 0;

}
void Combi(string a[], int reqLen, int s, int currLen, bool check[], int l, string first, string second, int* next, string fileName, string outputPath)
{
	ofstream SQDFile;
	if (currLen > reqLen)
		return;
	else if (currLen == reqLen) {
		//cout << "\t";
		string output;
		output = outputPath + fileName + std::to_string(*next) + ".xml";
		SQDFile.open(output);
		SQDFile << first;
		for (int i = 0; i < l; i++) {
			if (check[i] == true) {
				//cout << a[i] << " ";
				SQDFile << a[i];
			}
		}
		*next = *next + 1;
		SQDFile << second;
		SQDFile.close();
		//cout << "\n";
		return;
	}
	if (s == l) {
		return;
	}
	check[s] = true;
	Combi(a, reqLen, s + 1, currLen + 1, check, l, first, second, next, fileName, outputPath);
	check[s] = false;
	Combi(a, reqLen, s + 1, currLen, check, l, first, second, next, fileName, outputPath);
}

void readResultFile(string fileName, danglingBonds dba[], int dbAmount, bool fullResult, ofstream *LOG)
{
	ofstream fileLOG;
	bool openedHere = false;
	string line;
	double *X = new double[dbAmount];
	double *Y = new double[dbAmount];
	char aux[300] = { 0 };
	bool dbsFound = false;
	bool elecFound = false;

	elecDist distribution;
	elecDist dAux;

	for (int x = 0; x < MaxDBS; x++){
		dba[x].resetState();
		dba[x].disableActive();
	}
	for (int x = 0; x < dbAmount; x++){
		X[x] = ForbiddenInfinity;
		Y[x] = ForbiddenInfinity;
	}
	bool found = false;
	int x,y;
	int count = 0;
	ifstream ResultFile;
	ResultFile.open(fileName);
	if (ResultFile.is_open() && X != NULL && Y != NULL){
		if(LOG == NULL){
			fileLOG.open("log.txt");
			if(fileLOG.is_open()){
				LOG = &fileLOG;
				openedHere = true;
			}
			else{
				cout << "> Error! Log file cannot be open!\n";
				return;
			}
		}
		while (getline(ResultFile, line))
		{
			removeSpaces(line);
			x = 0;
			y = 0;
			found = false;
			if (line.compare("</physloc>") == 0){dbsFound = false;}
			if (dbsFound){
				for (std::string::size_type i = 0; i < line.size(); ++i){
					if (line[i] == doubleQuotes){
						found = !found;
						x = 0;
						if (aux[0] != 0){
							if (y == 0) { X[count] = atof(aux); }
							else if (y == 1){
								Y[count] = atof(aux); 
								count++;
							}
							y++;
						}
						memset(aux, 0, sizeof(aux));
					}
					else if (found){
						aux[x] = line[i];
						x++;
					}
				}
			}	
			if (line.compare("<physloc>") == 0){dbsFound = true;}
			if (line.compare("</elec_dist>") == 0){	elecFound = false; }
			if (elecFound){
				int validRun = 1;
				for (std::string::size_type i = 0; i < line.size(); ++i){
					if (line[i] == '>' && validRun){
						validRun = 0;
						for (int h = 0; h <= dbAmount+1; h++){
							if (line[i + h +1] == '<'){break;}
							dAux.coordinates[h] = line[i + h + 1];
						}
						if (dAux.valid && dAux.energy < distribution.energy){
							distribution.energy = dAux.energy;
							distribution.count = dAux.count;
							distribution.valid = dAux.valid;
							distribution.state_count = dAux.state_count;
							strcpy(distribution.coordinates, dAux.coordinates);
						}
					}
					if (line[i] == doubleQuotes){
						found = !found;
						x = 0;
						if (aux[0] != 0){
							if (y == 0){ dAux.energy = atof(aux); }
							else if (y == 1) { dAux.count = atoi(aux); }
							else if (y == 2) { dAux.valid = atoi(aux); }
							else if (y == 3) { dAux.state_count = atoi(aux); }
							y++;
						}
						memset(aux, 0, sizeof(aux));
					}
					else if (found){
						aux[x] = line[i];
						x++;
					}
				}
			}
				if (line.compare("<elec_dist>") == 0){ elecFound = true; }
		}

		//Now that all the values are saved, time to shove them into the DBs.
		if (distribution.coordinates[0] != 0){
			for (x = 0; x < dbAmount; x++){
				for (int h = 0; h < dbAmount; h++){
					if (dba[x].getX() == X[h] && dba[x].getY() == Y[h]){
						if (distribution.coordinates[h] == '-'){ dba[x].setState(); }
						dba[x].enableActive();
					}
				}
			}
		}
		else{ std::cout << " error! Invalid Configuration \n"; }

		//cout << "distribution Energy: " << distribution.energy << " distribution count: " << distribution.count << " distribution valid:" << distribution.valid << " distribution state: " << distribution.state_count << " distribution coords: " << distribution.coordinates << '\n';
		ResultFile.close();

		// Basic Printing Process
		printResult(dba, dbAmount, X, Y, fullResult, LOG, fileName);
	}
	else{ std::cout << "> error! Invalid File \n"; }
	if(openedHere) { fileLOG.close(); }
	delete[] X;
	delete[] Y;
	return;
}

void callAnneal(int dbAmount, bool supressAnneal, string dirAnneal, string outAnneal)
{
	DIR *d;
    struct dirent *dir;
    d = opendir(dirAnneal.c_str());
    string command;
    string filename;
    string outputname;
    if(d){
        while((dir = readdir(d)) != NULL){
            if(dir->d_name[0] != '.'){
                filename = dirAnneal;
                outputname = outAnneal;
                command = dir_anneal;
                filename.append(dir->d_name);
                outputname.append(dir->d_name);
				command.append(" ");
                command.append(filename);
                command.append(" ");
                command.append(outputname);
				if(supressAnneal){
					command.append(" ");
					command.append(">nul");
				}
				std::cout << "> Attempting to call command: " << command.c_str() << '\n';
                std::system(command.c_str());
				std::cout << "> Done!\n";
            }
        }
    }
}

int saveFile(danglingBonds dba[], int dbAmountExtra, int* randomCalls, int seed, string first, string second, string fileName){
	ofstream SQDFile;
	string dotFinal;
	auto s = std::to_string(seed);
	auto k = std::to_string(*randomCalls);
	string output = randomOutput + fileName + "_" + s + "_" + k + ".xml";
	//cout << output << endl;
	int next = 1;
	int lenght = 0;

	dotFinal = first;
	SQDFile.open(output);
	for (int x = 0; x < dbAmountExtra; x++){
		dotFinal += dba[x].dotBuffer;
	}
	SQDFile << dotFinal;		
	SQDFile << second;
	SQDFile.close();
	return 0;

}

