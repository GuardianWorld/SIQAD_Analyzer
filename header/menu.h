#pragma once
#include <iostream>
#include <ios>
#include <limits>
#include "OSFileCorrector.h"
using namespace std;

#define noConversion "999"

void menu(bool resultOutput, bool advancedOptions, bool supressAnneal);
string conversionText();
string loadSimText();
string loadPerturberText();
string loadPermutationText();
void annealCallText();
string singleResultsText();
int allResultsText();