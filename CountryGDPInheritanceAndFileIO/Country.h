/****************************************
** File:  Country.h
** Project: CSCE 221 Project 0, Spring 2019
** Author: Nathan Goynes
** Date: 1/23/19
** E-mail: ngoynes@tamu.edu
**
**  This file contains the Country.h file for Project 0.
** This file contains the declarations for the functions
** and variables of the Country class.
**
**
****************************************/

#ifndef COUNTRY_H
#define COUNTRY_H

#include <string>

class Country {
public:
  Country();
  Country(std::string, unsigned long, float, float, float, float, float, float, float);
  std::string getName() const { return name; }
  unsigned long getPop() const { return population; }
  float getLitRate() const { return literacyRate; }
  float getPrimCompFem() const { return primaryCompletionFemale; }
  float getPrimCompMale() const { return primaryCompletionMale; }
  float getPrimCompTot() const { return primaryCompletionTotal; }
  float getEdGDPSpent() const { return educationGDPSpent; }
  float getYouthLitRateFem() const { return youthLitRateFem; }
  float getYouthLitRateMale() const { return youthLitRateMale; }
  void setName(std::string);
  void setPop(unsigned long);
  void setLitRate(float);
  void setPrimCompFem(float);
  void setPrimCompMale(float);
  void setPrimCompTot(float);
  void setEdGDPSpent(float);
  void setYouthLitRateFem(float);
  void setYouthLitRateMale(float);

private:
  std::string name;
  unsigned long population;
  float literacyRate;
  float primaryCompletionFemale;
  float primaryCompletionMale;
  float primaryCompletionTotal;
  float educationGDPSpent;
  float youthLitRateFem;
  float youthLitRateMale;

};

#endif
