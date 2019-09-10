/****************************************
** File:  Continent.h
** Project: CSCE 221 Project 0, Spring 2019
** Author: Nathan Goynes
** Date: 1/23/19
** E-mail: ngoynes@tamu.edu
**
**  This file contains the Continent.h class for Project 0.
** This file contains the declarations for the functions and variables
** of the Continent class.
**
**
****************************************/

#ifndef CONTINENT_H
#define CONTINENT_H

#include <iostream>
#include <sstream>
#include <vector>
#include "Country.h"

class Continent : public Country {
public:
  Continent();
  Continent(std::string, unsigned long);
  std::vector<Country> getCountriesIC() { return countriesInContinent; }
  Country getHighestPop() const { return highestPopulation; }
  Country getHighestGDPSpent() const { return highestGDPSpent; }
  Country getHighestLitRate() const { return highestLiteracyRate; }
  void setCountriesIC(Country);
  void setHighestPop(Continent);
  void setHighestGDPSpent(Continent);
  void setHighestLitRate(Continent);

private:
  std::vector<Country> countriesInContinent;
  Country highestPopulation;
  Country highestGDPSpent;
  Country highestLiteracyRate;

};

std::ostream& operator<<(std::ostream& os, const Continent& cont);

#endif
