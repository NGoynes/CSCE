/****************************************
** File:  Country.cpp
** Project: CSCE 221 Project 0, Spring 2019
** Author: Nathan Goynes
** Date: 1/23/19
** E-mail: ngoynes@tamu.edu
**
**  This file contains the Country.cpp file for Project 0.
** This file contains the definitions for the functions we declared
** in the Country.h file.
**
**
****************************************/

#include "Country.h"
using namespace std;

Country::Country() {}

Country::Country(std::string nameIn, unsigned long popIn, float litRateIn, float femCompIn,
  float maleCompIn, float totCompIn, float edGDPIn, float YLRFIn, float YLRMIn) {//paramaterized constructor
  name = nameIn; population = popIn; literacyRate = litRateIn;
  primaryCompletionFemale = femCompIn; primaryCompletionMale = maleCompIn;
  primaryCompletionTotal = totCompIn; educationGDPSpent = edGDPIn;
  youthLitRateFem = YLRFIn; youthLitRateMale = YLRMIn;
}

void Country::setName(std::string nameSet) {
  name = nameSet;
}

void Country::setPop(unsigned long popSet) {
  population = popSet;
}

void Country::setLitRate(float litRate) {
  literacyRate = litRate;
}

void Country::setPrimCompFem(float primCompFem) {
  primaryCompletionFemale = primCompFem;
}

void Country::setPrimCompMale(float primCompMale) {
  primaryCompletionMale = primCompMale;
}

void Country::setPrimCompTot(float primCompTot) {
  primaryCompletionTotal = primCompTot;
}

void Country::setEdGDPSpent(float edGDP) {
  educationGDPSpent = edGDP;
}

void Country::setYouthLitRateFem(float setYLRF) {
  youthLitRateFem = setYLRF;
}

void Country::setYouthLitRateMale(float setYLRM) {
  youthLitRateMale = setYLRM;
}
