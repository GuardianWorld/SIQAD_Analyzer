#include "MainFileManager.h"

int convertSQDtoSim(float miValue)
{
	ofstream finalFile;


	DIR *d;
    struct dirent *dir;
    d = opendir(dir_input_sqd);
    FILE *fptr;
    FILE *baseFile;
    //FILE *finalFile;
    string filename;
    string finalFileName;
    char *fileBuffer = new char[20000];
    char *basicInfoBuffer = new char[20000];
    string finalFileBuffer;
    int y = 0;
    if(d)
    {
        while((dir = readdir(d)) != NULL)
        {
            if(dir->d_name[0] != '.')
            {
                filename = dir_input_sqd;
                filename.append(dir->d_name);
                finalFileName = dir_simulation;
                finalFileName.append(dir->d_name);
                finalFileName.pop_back();
                finalFileName.pop_back();
                finalFileName.pop_back();
                finalFileName.append("xml");
                finalFileBuffer = "";
                y = 0;
                cout << filename << endl;
                cout << finalFileName << endl;
                //Converting from SQD to XML
                baseFile = fopen(dir_basicInfoConfig, "r");
                while(fgets(fileBuffer, 20000, baseFile) != NULL)
                {
                    finalFileBuffer.append(fileBuffer);
                }
                //cout << finalFileBuffer << endl;
                fclose(baseFile);
                fptr = fopen(filename.c_str(), "r");
                while(fgets(fileBuffer, 20000, fptr) != NULL)
                {
                    if(y > 7)
                    {
                        finalFileBuffer.append(fileBuffer);
                    }
                    y++;
                }
                fclose(fptr);
                finalFile.open(finalFileName);
                finalFile << finalFileBuffer;
				finalFile.close();

                    //cout << finalFileBuffer << endl;


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
	
	for (int y = 0; y < MaxDBS; y++)
	{
		dba[y].initialize();
	}

	int count;
	int db = 0;
	bool anyfoundDB = false; // Verifies if ANY DB was found, for the first half of the text;
	bool endOfText = false;
	bool dbFound = false; // Gets each found DB
	string line;
	string lineAux;
	ifstream SQDFile;
	SQDFile.open(fileName);

	if (SQDFile.is_open())
	{
		while (getline(SQDFile, line))
		{
			lineAux = line;
			removeSpaces(line);

			if (line.compare("<dbdot>") == 0)
			{
				anyfoundDB = true;
				dbFound = true;
				count = 0;
			}
			else if (line.compare("</dbdot>") == 0)
			{ 
				dbFound = false; 	
				dba[db].dotBuffer = dba[db].dotBuffer + lineAux + '\n';
				db++;
			}

			if (!anyfoundDB) { bufferStart += lineAux + '\n'; }
			else if (line.compare("</layer>") == 0) { endOfText = true; }

			if (dbFound)
			{
				dba[db].dotBuffer = dba[db].dotBuffer + lineAux + '\n';
				if (count == 2) { dba[db].findDBDot(line, 0); } // Currently on LATCOORD
				else if (count == 3) // Currently on PHYSLOC
				{
					dba[db].findDBDot(line, 1);
					dba[db].setActive();
				}
				count++;
			}

			if (endOfText)
			{
				bufferEnd += lineAux + '\n';
			}
		}
		//cout << bufferStart << '\n' << bufferEnd;
		SQDFile.close();
	}
	else
	{
		cout << "> error! Invalid File \n";
		return 0;
	}
	cout << "> Done!\n";
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
		while (getline(listFile, line))
		{
			if (count == 0) { output = stoi(line); 	count++;}
			else
			{
				stringstream sstream(line);
				while (getline(sstream, word, ' '))
				{
					if (count == 1) n = stoi(word);
					else if (count == 2) m = stoi(word);
					else if (count == 3) l = stoi(word);
					if (count == 3)
					{
						for (int x = 0; x < dbamount; x++)
						{
							compare = dba[x].compare(n, m, l);
							if (compare)
							{
								if (fileLine == output) { dba[x].setObserver();}
								else
								{
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
	}
	cout << "> Done!\n";
	return output;
}

void removeSpaces(string &str)
{
	auto noSpace = std::remove(str.begin(), str.end(), ' ');
	str.erase(noSpace, str.end());
}

int createPermutations(danglingBonds dba[], string first, string second, int dbAmount)
{
	ofstream SQDFile;
	string filename;
	string str;
	int next = 1;
	int lenght = 0;

	bool check[5];
	for (int x = 0; x < MaxDBS; x++)
	{
		if (dba[x].getDisturber() == 1)
		{
			lenght++;
		}
	}

	string * combin = new string[5];
	int h = 0;
	for (int x = 0; x < dbAmount; x++)
	{
		if (dba[x].getDisturber())
		{
			combin[h] = dba[x].dotBuffer;
			h++;
		}
	}

	string output = firstOutput;
	SQDFile.open(output);
	for (int x = 0; x < dbAmount; x++)
	{
		if (dba[x].getActive() && !dba[x].getDisturber())
		{
			first = first + dba[x].dotBuffer;
		}
	}
	SQDFile << first;
	SQDFile << second;
	//cout << second << '\n';
	SQDFile.close();


	for (int i = 1; i <= lenght; i++) {
		//cout << "\nThe all possible combination of length " << i << " for the given array set:\n";
		Combi(combin, i, 0, 0, check, lenght, first, second, &next);
	}
	cout << "> Done!\n";
	return 0;

}
void Combi(string a[], int reqLen, int s, int currLen, bool check[], int l, string first, string second, int* next)
{
	ofstream SQDFile;
	if (currLen > reqLen)
		return;
	else if (currLen == reqLen) {
		//cout << "\t";
		string output;
		output = dir_input_anneal_xml + std::to_string(*next) + ".xml";
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
	Combi(a, reqLen, s + 1, currLen + 1, check, l, first, second, next);
	check[s] = false;
	Combi(a, reqLen, s + 1, currLen, check, l, first, second, next);
}

void readResultFile(string fileName, danglingBonds dba[], int dbAmount)
{
	string line;
	double *X = new double[dbAmount];
	double *Y = new double[dbAmount];
	char aux[300] = { 0 };
	bool dbsFound = false;
	bool elecFound = false;

	elecDist distribution;
	elecDist dAux;

	for (int x = 0; x < MaxDBS; x++)
	{
		dba[x].resetState();
	}
	for (int x = 0; x < dbAmount; x++)
	{
		X[x] = 0;
		Y[x] = 0;
	}
	bool found = false;
	int x,y;
	int count = 0;
	ifstream ResultFile;
	ResultFile.open(fileName);
	if (ResultFile.is_open() && X != NULL && Y != NULL)
	{
		while (getline(ResultFile, line))
		{
			removeSpaces(line);
			x = 0;
			y = 0;
			found = false;
			if (line.compare("</physloc>") == 0)
			{
				dbsFound = false;
			}
			if (dbsFound)
			{
				//printf("What");
				for (std::string::size_type i = 0; i < line.size(); ++i)
				{
					if (line[i] == 34)
					{
						found = !found;
						x = 0;
						if (aux[0] != 0)
						{
							if (y == 0) { X[count] = atof(aux); }
							else if (y == 1) 
							{
								Y[count] = atof(aux); 
								count++;
							}
							y++;
						}
						memset(aux, 0, sizeof(aux));
					}
					else if (found)
					{
						aux[x] = line[i];
						x++;
					}
				}
			}	
			if (line.compare("<physloc>") == 0)
			{
				dbsFound = true;

			}


			if (line.compare("</elec_dist>") == 0)
			{
				elecFound = false;
			}
			if (elecFound)
			{
				int validRun = 1;
				X[count] = 0;
				Y[count] = 0;
				for (std::string::size_type i = 0; i < line.size(); ++i)
				{
					if (line[i] == '>' && validRun)
					{
						validRun = 0;
						for (int h = 0; h <= dbAmount+1; h++)
						{
							if (line[i + h +1] == '<')
							{
								break;
							}
							dAux.coordinates[h] = line[i + h + 1];
						}

						//cout << "Energy: " << dAux.energy << " count: " << dAux.count << " valid:" << dAux.valid << " state: " << dAux.state_count << " coords: " << dAux.coordinates << '\n';

						if (dAux.valid && dAux.energy < distribution.energy)
						{
							distribution.energy = dAux.energy;
							distribution.count = dAux.count;
							distribution.valid = dAux.valid;
							distribution.state_count = dAux.state_count;
							strcpy(distribution.coordinates, dAux.coordinates);
						}

						//cout << "distribution Energy: " << distribution.energy << " distribution count: " << distribution.count << " distribution valid:" << distribution.valid << " distribution state: " << distribution.state_count << " distribution coords: " << distribution.coordinates << '\n';
					}
					if (line[i] == 34)
					{
						//cout << line << '\n';
						found = !found;
						x = 0;
						if (aux[0] != 0)
						{
							if (y == 0)
							{
								dAux.energy = atof(aux);
							}
							else if (y == 1) { dAux.count = atoi(aux); }
							else if (y == 2) { dAux.valid = atoi(aux); }
							else if (y == 3) { dAux.state_count = atoi(aux); }
							y++;
						}
						memset(aux, 0, sizeof(aux));
					}
					else if (found)
					{
						aux[x] = line[i];
						x++;
					}
				}
			}
			if (line.compare("<elec_dist>") == 0)
			{
				elecFound = true;
			}
		}

		//Now that all the values are saved, time to shove them into the DBs.
		if (distribution.coordinates[0] != 0)
		{
			for (x = 0; x < dbAmount; x++)
			{
				for (int h = 0; h < dbAmount; h++)
				{
					if (dba[x].getX() == X[h] && dba[x].getY() == Y[h])
					{
						if (distribution.coordinates[h] == '-')
						{
							dba[x].setState();
						}
					}
				}
			}
		}
		else
		{
			cout << " error! Invalid Configuration \n";
		}

		//cout << dba[0].getX() << ' ' << dba[0].getState() << '\n';
		//cout << dba[1].getX() << ' ' << dba[1].getState() << '\n';
		//cout << dba[2].getX() << ' ' << dba[2].getState() << '\n';
		//cout << bufferStart << '\n' << bufferEnd;
		cout << "distribution Energy: " << distribution.energy << " distribution count: " << distribution.count << " distribution valid:" << distribution.valid << " distribution state: " << distribution.state_count << " distribution coords: " << distribution.coordinates << '\n';
		ResultFile.close();
		
	}
	else
	{
		cout << "> error! Invalid File \n";
	}
	delete[] X;
	delete[] Y;
	return;
}

void printResult(danglingBonds dba[], int dbAmount)
{
	for (int x = 0; x < dbAmount; x++)
	{
		if (dba[x].getObserved() == 1)
		{
			if (dba[x].getState() == 0)
			{
				cout << "The observed DB is Neutral (Transparent)\n";
			}
			else
			{
				cout << "The observed DB is Negative (Blue)\n";
			}
		}
	}
}

void printAllResults(danglingBonds dba[], int dbAmount, int perms)
{
	for (int x = 0; x < perms; x++)
	{
		for (int y = 0; x < dbAmount; x++)
		{
			if (dba[x].getObserved() == 1)
			{
				if (dba[x].getState() == 0)
				{
					cout << "The observed DB is Neutral (Transparent)\n";
				}
				else
				{
					cout << "The observed DB is Negative (Blue)\n";
				}
			}
		}
	}
}

void printFullResult(danglingBonds dba[], int dbAmount)
{

}

void callAnneal(string sFolder, int dbAmount, int perms)
{
	string outputFolder = { 0 };
	string result = { 0 };
	string command = { 0 };
	string AnnealInput;
	int valueR = 0;
	for (int x = 0; x < perms; x++)
	{
		AnnealInput = dir_input_anneal_xml + std::to_string(x) + ".xml";
		//cout << output << '\n';
		result = dir_output_xml + std::to_string(x) + ".xml";
		//cout << result << '\n';
		command = '(' + sFolder + ' ' + AnnealInput + ' ' + result + ')';
		cout << "> Attempting to call command: " << command.c_str() << '\n';
		system(command.c_str());
		//system("./simanneal/simanneal");
		//valueR = WinExec(command.c_str(), SW_HIDE);
		/*if (valueR >= 31)
		{
			cout << "> Done! \n";
		}
		else
		{
			cout << "> Error! \n";
		}*/
	}
}