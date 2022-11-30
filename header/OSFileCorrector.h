#pragma once
#include <iostream>
using namespace std;


#ifdef _WIN32
#define OS 1
#define dir_anneal "\"simanneal\\simanneal.exe\"\0"
#define dir_input_sqd 2
#define dir_input_anneal_xml "\"annealInput\\"
#define dir_output_anneal_xml "\"results\\"
#define dir_operations "\"op\\"

#define firstOutput "\"annealInput\\work0.xml"
#elif __linux__
#define OS 2
#define dir_anneal "./simanneal/simanneal"
#define dir_input_sqd "./sqdInput/"
#define dir_input_anneal_xml "./annealInput/"
#define dir_output_xml "./results/"
#define dir_operations "./op/"
#define dir_basicInfoConfig "./default/basicInfo.txt"
#define dir_simulation "./simulationFiles/"

#define firstOutput "./annealInput/"
#define randomOutput "./randomGen/"
#define randomOutputAnneal "./annealRandom/"
#define randomAnnealOutput_xml "./resultsRandom/"
#define wantedResults "./wantedResults/"

//Defines for Config file for Part 2;
#define dir_configFile "./default/"
#define dir_randomfileCreator "./RandomFileCreatorFolder/"
#define dir_randomFileFoundResults "./RandomFileCreatorFolder/FoundResults/"
#define dir_AND "./RandomFileCreatorFolder/FoundResults/AND/"
#define dir_NAND "./RandomFileCreatorFolder/FoundResults/NAND/"
#define dir_NOR "./RandomFileCreatorFolder/FoundResults/NOR/"
#define dir_OR "./RandomFileCreatorFolder/FoundResults/OR/"
#define dir_XAND "./RandomFileCreatorFolder/FoundResults/XAND/"
#define dir_XNAND "./RandomFileCreatorFolder/FoundResults/XNAND/"
#define dir_XNOR "./RandomFileCreatorFolder/FoundResults/XNOR/"
#define dir_XOR "./RandomFileCreatorFolder/FoundResults/XOR/"
#define dir_INV "./RandomFileCreatorFolder/FoundResults/INV/"
#define dir_MUX001 "./RandomFileCreatorFolder/FoundResults/MUX001/"
#define dir_MUX010 "./RandomFileCreatorFolder/FoundResults/MUX010/"
#define dir_MUX100 "./RandomFileCreatorFolder/FoundResults/MUX100/"
#endif