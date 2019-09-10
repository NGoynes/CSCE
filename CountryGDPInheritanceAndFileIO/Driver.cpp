/****************************************
** File:  Driver.cpp
** Project: CSCE 221 Project 0, Spring 2019
** Author: Nathan Goynes
** Date: 1/23/19
** E-mail: ngoynes@tamu.edu
**
**  This file contains the Driver.cpp file for Project 0.
** This file contains the main() and readFromFiles() functions
** that make up the core of our program. Given two text
** files, this program will read data from both of them
** combine it and output the results.
**
**
****************************************/

#include "Continent.h"
#include <fstream>
using namespace std;

//---------------------------------
// Name: readFromFiles
// PreCondition: Two compatible text files with data and an empty vector
// PostCondition: Fills a vector of vectors with supplied data
//---------------------------------
void readFromFiles(string inFile1, string inFile2, vector<Continent>& world) {
  //open the files
  ifstream file1;
  file1.open(inFile1, ios_base::in);
  if(file1.fail()) {
    cout << "File1 was not successfully opened." << endl;
    exit(1);
  }
  ifstream file2;
  file2.open(inFile2, ios_base::in);
  if(file2.fail()) {
    cout << "File2 was not successfully opened." << endl;
    exit(1);
  }

  vector<Country> vec;
  vector<Continent> temp;
  //read values from file2
  string in2;
  //incrementer for assigning countries to continent
  int j = -1;
  while(getline(file2, in2)) {
    //initialize values
    stringstream line2(in2);
    string name;
    //read line
    line2 >> name;
    //get a test char
    char c = name[1];

    //determine if continent or country
    if (isupper(c)) {
      //if we found a continent, add it to our vector of continents
      Continent continentAlpha(name, 0);
      world.push_back(continentAlpha);
      //we'll use a temporary vector of continents to populate the real vector
      temp.push_back(continentAlpha);
      j++;
    }
    else {
      //if we found a country, add it to our temporary vector of continents and countries
      Country countryAlpha(name, 0, -1, -1, -1, -1, -1, -1, -1);
      temp.at(j).setCountriesIC(countryAlpha);
      vec.push_back(countryAlpha);
    }
  }

  //read values from file1
  string in;
  //ignore first line
  getline(file1, in);
  while(getline(file1, in)) {
    stringstream line(in);

    //declare variables
    string name; unsigned long population; string sLiteracyRate;
    string sPrimaryCompletionFemale; string sPrimaryCompletionMale; string sPrimaryCompletionTotal;
    string sEducationGDPSpent; string sYouthLitRateFem; string sYouthLitRateMale;

    //read line by line
    line >> name >> population >> sLiteracyRate >> sPrimaryCompletionFemale >> sPrimaryCompletionMale
    >> sPrimaryCompletionTotal >> sEducationGDPSpent >> sYouthLitRateFem >> sYouthLitRateMale;

    //store values as -1 instead of 0 if we have any
    if (sLiteracyRate == "N/A") {
      sLiteracyRate = "-1";
    }
    if (sPrimaryCompletionFemale == "N/A") {
      sPrimaryCompletionFemale = "-1";
    }
    if (sPrimaryCompletionMale == "N/A") {
      sPrimaryCompletionMale = "-1";
    }
    if (sPrimaryCompletionTotal == "N/A") {
      sPrimaryCompletionTotal = "-1";
    }
    if (sEducationGDPSpent == "N/A") {
      sEducationGDPSpent = "-1";
    }
    if (sYouthLitRateFem == "N/A") {
      sYouthLitRateFem = "-1";
    }
    if (sYouthLitRateMale == "N/A") {
      sYouthLitRateMale = "-1";
    }

    //push data into vector of all countries
    for (int i = 0; i < vec.size(); ++i) {
      if (vec.at(i).getName() == name) {
        vec.at(i).setPop(population);
        vec.at(i).setLitRate(stof(sLiteracyRate));
        vec.at(i).setPrimCompFem(stof(sPrimaryCompletionFemale));
        vec.at(i).setPrimCompMale(stof(sPrimaryCompletionMale));
        vec.at(i).setPrimCompTot(stof(sPrimaryCompletionTotal));
        vec.at(i).setEdGDPSpent(stof(sEducationGDPSpent));
        vec.at(i).setYouthLitRateFem(stof(sYouthLitRateFem));
        vec.at(i).setYouthLitRateMale(stof(sYouthLitRateMale));
      }
    }
  }

  //iterate through both vectors finding the countries that belong and adding those to our world vector
  for (int i = 0; i < temp.size(); ++i) {
    for (int k = 0; k < temp.at(i).getCountriesIC().size(); ++k) {
      for (int m = 0; m < vec.size(); ++m) {
        if (temp.at(i).getCountriesIC().at(k).getName() == vec.at(m).getName()) {
          world.at(i).setCountriesIC(vec.at(m));
        }
      }
    }
  }

  return;
}

int main() {
  vector<Continent> world;

  readFromFiles("2013WorldBankEducationCensusData.txt", "CountriesContinents.txt", world);

  //output everything
  for (int i = 0; i < world.size(); ++i) {
    world.at(i).setHighestLitRate(world.at(i));
    world.at(i).setHighestGDPSpent(world.at(i));
    world.at(i).setHighestPop(world.at(i));
    cout << world.at(i) << endl;
  }

  return 0;
}
