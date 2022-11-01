#pragma once
#include <iostream>
#include <ios>
#include <limits>
#include "OSFileCorrector.h"
using namespace std;
		
/**
* This file simply has the menu functions for all the interactions, think of it as a "View" setup equivalent of MVC.
* //TODO: Documentation of each functions.
*/

#define noConversion "999"

void menu(bool resultOutput, bool advancedOptions, bool supressAnneal);
string conversionText();
string loadSimText();
string loadPerturberText();
string loadPermutationText(string folderName);
void annealCallText();
string singleResultsText();
int allResultsText();
string loadPermutationRandom(string folderName);
