#ifndef STATEDEMOG_H
#define STATEDEMOG_H

#include <string>
#include <iostream>
#include "demogData.h"
#include <vector>
#include <memory>

using namespace std;

/*
  class to represent state demographic data
  from CORGIS
*/
class stateDemog {
  public:
    stateDemog(string n) {
      name = n;
      popOver65 = 0;
      popUnder18 = 0;
      popUnder5 = 0;
      percentUndergraduate = -1;
      percentHighSchool = -1;
      totalPop = 0;
    }

    stateDemog(string n, shared_ptr<demogData> county) {
      name = n;
      popOver65 = 0;
      popUnder18 = 0;
      popUnder5 = 0;
      percentUndergraduate = -1;
      percentHighSchool = -1;
      totalPop = 0;
      addCounty(county);
    }   

    string getName() { return name; }

    double getBAup() { return percentUndergraduate; }

    double getHSup() { return percentHighSchool; }

    //string getState() { return state; }

    double getpopOver65() { return popOver65; }

    double getpopUnder18() { return popUnder18; }

    double getpopUnder5() { return popUnder5; }

    friend std::ostream& operator<<(std::ostream &out, const stateDemog &DD);

    void addCounty(shared_ptr<demogData> county){
      counties.push_back(county);
    }

    double getTotalPop() {
      return totalPop;
    }

    void calculate(){
      double totalUG = 0;
      double totalHS = 0;
      for(shared_ptr<demogData> county : counties){
        popOver65 += county->getpopOver65();
        popUnder18 += county->getpopUnder18();
        popUnder5 += county->getpopUnder5();
        totalUG += county->getBAup() * county->getTotalPop();
        totalHS += county->getHSup() * county->getTotalPop();
        totalPop += county->getTotalPop();
      }
      percentUndergraduate = totalUG/totalPop;
      percentHighSchool = totalHS/totalPop;
    }

private:
    string name;
    //const string state;
    double popOver65;
    double popUnder18;
    double popUnder5;
    double percentUndergraduate;
    double percentHighSchool;
    double totalPop;
    vector<shared_ptr<demogData>> counties;
};
#endif
  
