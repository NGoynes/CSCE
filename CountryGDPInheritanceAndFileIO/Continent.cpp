/****************************************
** File:  Continent.cpp
** Project: CSCE 221 Project 0, Spring 2019
** Author: Nathan Goynes
** Date: 1/23/19
** E-mail: ngoynes@tamu.edu
**
**  This file contains the Continent.cpp file for Project 0.
** This file contains the definitions for the functions we declared
** in the Continent.h file.
**
**
****************************************/

#include "Continent.h"
using namespace std;

Continent::Continent() {}

Continent::Continent(std::string nameIn, unsigned long popIn) {
  this->setName(nameIn);
  this->setPop(popIn);
}

void Continent::setCountriesIC(Country countryIn) {
  countriesInContinent.push_back(countryIn);
  setPop(getPop() + countryIn.getPop());
}

void Continent::setHighestPop(Continent contHighPop) {
  unsigned long numPop = 0;

  for (int i = 0; i < contHighPop.countriesInContinent.size(); ++i) {
    if (contHighPop.countriesInContinent.at(i).getPop() > numPop) {
      numPop = contHighPop.countriesInContinent.at(i).getPop();
      highestPopulation = contHighPop.countriesInContinent.at(i);
    }
  }
}

void Continent::setHighestGDPSpent(Continent contHighGDP) {
  float numGDP = contHighGDP.countriesInContinent.at(0).getEdGDPSpent();

  for (int i = 0; i < contHighGDP.countriesInContinent.size(); ++i) {
    if (contHighGDP.countriesInContinent.at(i).getEdGDPSpent() >= numGDP) {
      numGDP = contHighGDP.countriesInContinent.at(i).getEdGDPSpent();
      highestGDPSpent = contHighGDP.countriesInContinent.at(i);
    }
  }
}

void Continent::setHighestLitRate(Continent contHighLitRate) {
  float numLitRate = 0;

  for (int i = 0; i < contHighLitRate.countriesInContinent.size(); ++i) {
    if (contHighLitRate.countriesInContinent.at(i).getLitRate() > numLitRate) {
      numLitRate = contHighLitRate.countriesInContinent.at(i).getLitRate();
      highestLiteracyRate = contHighLitRate.countriesInContinent.at(i);
    }
  }
}

ostream& operator<<(ostream& os, const Continent& cont) {
    os << cont.getName() << endl;
    os << " Population: " << cont.getPop() << endl;
    os << " Country with highest literacy rate: " << cont.getHighestLitRate().getName() <<
    " with a population of " << cont.getHighestLitRate().getPop() <<
    " and a literacy rate of " << cont.getHighestLitRate().getLitRate() << endl;
    os << " Country with highest GDP spendature on education: " << cont.getHighestGDPSpent().getName() <<
    " with a population of " << cont.getHighestGDPSpent().getPop() <<
    " and a literacy rate of " << cont.getHighestGDPSpent().getLitRate() << endl;
    os << " Country with highest population: " << cont.getHighestPop().getName() <<
    " with a population of " << cont.getHighestPop().getPop() << " and a literacy rate of " <<
    cont.getHighestPop().getLitRate();

    return os;
}
